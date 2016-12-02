/*!
 * This file is PART of plcdn_log_analysis
 * parse logs and print results, currently support: nginx, srs logfiles
 * @author hongjun.liao <docici@126.com>
 * @date 2016/11
 * @NOTES:
 * 1.merge srs results  to nginx results currently, see append_flow_table, @date 2016/11/14
 */

#include <stdio.h>
#include "bd_test.h"			/*test_srs_log_stats_main*/
#include "test_options.h" 		/*sla_options*/

#include <stdio.h>
#include <string.h> 	/*strncpy*/
#include <sys/sysinfo.h>	/*get_nprocs*/
#include <sys/stat.h>	/*fstat*/
#include <sys/mman.h>	/*mmap*/
//#include <locale.h> 	/*setlocale*/
#include <pthread.h> 	/*pthread_create*/
#include <unordered_map> 	/*std::unordered_map*/
#include <map>				/*std::map*/
//#include <thread>		/*std::thread*/
//#include <atomic>		/*std::atomic*/
#include "bd_test.h"		/*test_nginx_log_stats_main*/
#include "test_options.h"	/*nla_options**/
#include "nginx_log_analysis.h"	/*log_stats, ...*/
#include "srs_log_analysis.h"	/*srs_log_context*/
#include "string_util.h"	/*md5sum*/
#include "net_util.h"	/*get_if_addrs, ...*/
#include <algorithm>	/*std::min*/

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*for nginx log*/

/*tests, @see nginx_log_analysis/test.cpp*/
extern int test_nginx_log_analysis_main(int argc, char ** argv);

/*split_log.cpp*/
extern int split_nginx_log(std::unordered_map<std::string, nginx_domain_stat> const& stats,
		char const * folder, char const * fmt);
/*!
 * parse ' ' splitted nginx log
 * @NOTE:
 * 1.current nginx_log format:
 * $host $remote_addr $request_time_msec $cache_status [$time_local] "$request_method \
 * $request_uri $server_protocol" $status $bytes_sent \
 * "$http_referer" "$remote_user" "$http_cookie" "$http_user_agent" \
 * $scheme $request_length $upstream_response_time', total fields == 18
 *
 * nginx_log sample:
 * flv.pptmao.com 183.240.128.180 14927 HIT [07/Oct/2016:23:43:38 +0800] \
 * "GET /2016-09-05/cbc1578a77edf84be8d70b97ba82457a.mp4 HTTP/1.1" 200 4350240 "http://www.pptmao.com/ppt/9000.html" \
 * "-" "-" "Mozilla/5.0 (compatible; MSIE 6.0; Windows NT 5.0)" http 234 - CN4406 0E

 * TODO:make it customizable
 * */
static int do_parse_nginx_log_item(char ** fields, char *& szitem, char delim = '\0');
/*parse nginx_log buffer @apram ct, and output results*/
static int parse_nginx_log_item_buf(parse_context& ct);
/* split file @param f into parts, use pthread to parallel parse*/
static int parallel_parse_nginx_log(char * start_p, struct stat const & logfile_stat,
		std::unordered_map<std::string, nginx_domain_stat> & stats);

/* parse nginx_log $request_uri field, return url, @param cache_status: MISS/MISS0/HIT,...
 * @param mode:
 * mode 0, url endwith ' ', reserve all, e.g. "POST /zzz.asp;.jpg HTTP/1.1", return "/zzz.asp;.jpg"
 * mode 1, url endwith '?'(if no '?', then endwith ' '), ignore parameters, e.g. "GET /V3/?page_id=1004&cid=1443 HTTP/1.1", return "/V3/"
 * mode 2, custom, @param cache_status required
 * */
static char * parse_nginx_log_request_uri_url(char * request_uri, int * len, char const * cache_status, int mode = 2);
/*do log statistics with time interval*/
static int do_nginx_log_stats(log_item const& item, std::unordered_map<std::string, nginx_domain_stat> & logstats);

/*load devicelist, @param devicelist map<ip, device_id>*/
static int load_devicelist(char const* file, std::unordered_map<std::string, int>& devicelist);

/*get device_id by ip*/
static int get_device_id(std::unordered_map<std::string, int> const& devicelist);

/* url manage:
 * if @param str NOT exist, then add as new, else return exist
 * this funtions currently NOT used because of poor speedup, @date: 2016/10/27
 */
static char const * str_find(char const *str, int len = -1);

/*plcdn_log_analysis/print_table.cpp*/
extern int print_plcdn_log_stats(std::unordered_map<std::string, nginx_domain_stat> const& logstats);
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*for srs log*/
static int extract_and_parse_srs_log(char * start_p, struct stat const & logfile_stat,
		std::unordered_map<std::string, srs_domain_stat> & logstats);
/*srs_log_analysis/print_table.cpp*/
extern void fprint_srs_log_stats(FILE * stream, std::unordered_map<std::string, srs_domain_stat> const& srs_stats);
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*GLOBAL vars*/
/*plcdn_log_analysis/option.cpp*/
extern struct plcdn_la_options plcdn_la_opt;
/*map<ip_addr : device_id>*/
static std::unordered_map<std::string, int> g_devicelist;
/*map<domain, site_info>*/
std::unordered_map<std::string, site_info> g_sitelist;
static size_t g_line_count = 0;
time_t g_plcdn_la_start_time = 0;
int g_plcdn_la_device_id = 0;

///////////////////////////////////////////////////////////////////////////////////////////////
static char * parse_nginx_log_request_uri_url(char * request_uri, int * len, char const * cache_status, int mode/* = 2*/)
{
	auto url = strchr(request_uri, '/'); /*"GET /abc?param1=abc"*/
	if(!url) return NULL;
	auto pos = strchr(url, ' ');
	auto m = plcdn_la_opt.parse_url_mode;
	if(m == 1){
		auto p = strchr(url, '?');
		if(p) pos = p;
	}
	else if(m == 2){
		auto miss0 = strrchr(cache_status, '0');
		auto pos1 = strchr(url, '?'), pos2 = strchr(url, ';');
		if(miss0 && (pos1 || pos2)){
			if(pos1 && pos2)
				pos = std::min(pos1, pos2);
			else{
				pos = (pos1? pos1 : pos2);
			}
		}
	}
	auto length = pos - url;
	url[length] = '\0';
	if(len)
		*len = length;
	return url;
}

static int parse_log_item(log_item & item, char *& logitem, char delim /*= '\0'*/)
{
	memset(&item, 0, sizeof(log_item));
	item.beg = logitem;
	char *items[18];
	int result = do_parse_nginx_log_item(items, logitem, delim);
	if(result != 0){
		return 1;
	}
	item.end = logitem;

	item.domain = items[0];
//	item.client_ip_2 = items[1];
	item.client_ip = netutil_get_ip_from_str(items[1]);
	if(item.client_ip == 0)
		return 1;

	char * end;
	item.request_time = strtoul(items[2], &end, 10);
	/*format: [17/Sep/2016:00:26:08 +0800]*/
	tm my_tm;
	if(!strptime(items[4] + 1, "%d/%b/%Y:%H:%M:%S" , &my_tm))
		return -1;
	my_tm.tm_isdst = 0;
	item.time_local = mktime(&my_tm);

	auto url = parse_nginx_log_request_uri_url(items[6], NULL, items[3]);
	if(!url) return -1;
	item.request_url = url;

	char const * p = items[8];
	item.bytes_sent = strtoul(p, &end, 10);
	item.status = atoi(items[7]);
	item.is_hit = (strcmp(items[3],"HIT") == 0);
	return 0;
}

static int do_nginx_log_stats(log_item const& item, std::unordered_map<std::string, nginx_domain_stat> & logstats)
{
	auto & dstat = logstats[item.domain];
	if(dstat._site_id == 0)
		find_site_id(g_sitelist, item.domain, dstat._site_id, &dstat._user_id);

	auto & logsstat = dstat._stats[item.time_local];
	if(!item.is_hit){
		logsstat._bytes_m += item.bytes_sent;
		++logsstat._access_m;
	}

	/*if NOT required, we needn't statistics it*/
	if(plcdn_la_opt.output_file_flow || plcdn_la_opt.output_file_url_popular || plcdn_la_opt.output_file_http_stats){
		//FIXME: test me! @date 2016/11
		auto len = strlen(item.request_url);
		char buff[64];
		sha1sum_r(item.request_url, len, buff);
		url_stat& urlstat = logsstat._url_stats[buff];
		++urlstat._status[item.status];
		urlstat._bytes[item.status] += item.bytes_sent;
	}

	if(plcdn_la_opt.output_file_ip_popular || plcdn_la_opt.output_file_ip_slowfast){
		ip_stat& ipstat =logsstat._ip_stats[item.client_ip];
		ipstat.bytes += item.bytes_sent;
		ipstat.sec += item.request_time;
		++ipstat.access;

	}
	if(plcdn_la_opt.output_file_cutip_slowfast){
		auto & cutipstat = logsstat._cuitip_stats[item.client_ip];
		cutipstat.bytes += item.bytes_sent;
		cutipstat.sec += item.request_time;
	}
	if(plcdn_la_opt.output_file_ip_source){
		/*FIXME, @date 2016/11/11*/
//		if(plcdn_la_opt.enable_devicelist_filter &&  g_devicelist[item.client_ip_2] != 0)
//			return 0;
		locisp_stat& listat = logsstat._locisp_stats[item.client_ip];
		listat.bytes += item.bytes_sent;
		++listat.access;
		if(!item.is_hit){
			listat.bytes_m += item.bytes_sent;
			++listat.access_m;
		}
	}

	if(item.beg && item.end)
		logsstat._logs.push_back(std::make_pair<>(item.beg, item.end));
	return 0;
}

int load_devicelist(char const* file, std::unordered_map<std::string, int>& devicelist)
{
	if(!file) return -1;
	FILE * f = fopen(file, "r");
	if(!f) {
		fprintf(stderr, "%s: fopen file %s failed\n", __FUNCTION__, file);
		return 1;
	}
	char data[1024] = "";
	while(fgets(data, sizeof(data), f)){
		if(data[0] == '\n') continue;
		data[strlen(data) - 1] = '\0';
		char const * token = strtok(data, " ");
		int id = atoi(token);
		token = strtok(NULL, " ");
		devicelist[token] = id;
	}
//	for(auto const& item : devicelist){
//		fprintf(stdout, "[%s]--[%d]\n", item.first.c_str(), item.second);
//	}
	return 0;
}

static int get_device_id(std::unordered_map<std::string, int> const & devicelist)
{
	char ips[64][16];
	int count = 64;
	int result  = get_if_addrs(ips[0], count, 16);
	if(result != 0)
		return -1;
	//std::find_first_of();
	for(int i = 0; i < count; ++i){
		for(auto const& item : devicelist){
			if(item.first.compare(ips[i])  == 0)
				return item.second;
		}
	}
	return 0;
}

int do_parse_nginx_log_item(char** fields, char*& szitem, char delim/* = '\0'*/)
{
//	for(char * ch = szitem; ; ++ch) { fprintf(stdout, "%c", *ch); if(*ch == delim) break; }
	auto arg_start = false;
	int field_count = 0;

	auto q = szitem;
	for(auto p = szitem; ; ++q){
		if(*q == '"'){
			if(!arg_start) {
				arg_start = true;
				p = q + 1;
			}
			else{
				arg_start = false;
				if(!(*(q + 1) == ' ' || *(q + 1) == delim)){
//					fprintf(stderr, "%s: parse error at %s\n", __FUNCTION__, q);
					goto error_return;
				}
				*q = '\0';
				fields[field_count++] = p;
				++q;
				if(*q == delim)
					break;
				p = q + 1;
			}
			continue;
		}
		if(arg_start && *q == delim){
//			fprintf(stderr, "%s: parse error\n", __FUNCTION__);
			goto error_return;
		}
		if(!arg_start && (*q == ' ' || *q == delim)){
			fields[field_count++] = p;
			auto c = *q;
			*q = '\0';
			if(c == delim){
				break;
			}
			p = q + 1;
		}
	}
	szitem = q;
//	for(int i  = 0; i < field_count; ++i){
//		fprintf(stdout, "%s: argv[%02d]: %s\n", __FUNCTION__, i, fields[i]);
//	}

	return 0;
error_return:
	fields[0] = '\0';
	return -1;
}

/*for str_find()*/
static int str_find_realloc(char *& p, size_t & total, size_t step_len)
{
	for(size_t i = 1; i < step_len; i *= 2){
		size_t new_sz = step_len / i;
		void * p2  = realloc(p, total + new_sz);
		if(p2) {
			p = (char * )p2;
			total += new_sz;
			if(plcdn_la_opt.verbose)
				fprintf(stdout, "%s: total=%s\n", __FUNCTION__, byte_to_mb_kb_str(total, "%-.0f %cB"));
			return 0;
		}
	}
	return -1;
}

static char const * str_find(char const *str, int len)
{
	if(!str || !str[0])
		return NULL;
	/*FIXME: dangerous in multi-threaded!!! use __thread/thread_local?*/
	static /*thread_local*/ std::unordered_map<std::string, char *> urls;
	static size_t step = 10 * 1024, total = 1024 * 64;	/*KB*/
	auto start_p = (char *)malloc(total);
	static size_t offset_len = 0;
	if(len == -2){
		free(start_p);
		return 0;
	}
	len = (len != -1? len : strlen(str));
	char md5buff[33];
	md5sum_r(str, len, md5buff);
	auto &s = urls[md5buff];
	if(!s){
		if(offset_len + len + 1> total){
			if(str_find_realloc(start_p, total, step) != 0)
				return NULL;
		}
		s = start_p + offset_len;
		strncpy(s, str, len);
		s[len] = '\0';
		offset_len += (len + 1);
	}
	return s;
}

int parse_nginx_log_item_buf(parse_context& ct)
{
	auto & buf = ct.buf;
	auto & len = ct.len;
	auto & logstats = ct.logstats;
	auto & total_lines = ct.total_lines = 0;

	log_item item;
	for(char * p = buf; p != buf + len; ++p){
//		printf(">_____");
//		for(auto p1 = buf; p1 != buf + len; ++p1){
//			printf("%c", *p1);
//		}
//		printf("_____|\n");

		int result = parse_log_item(item, p, '\n');

		if(result == 0){
			do_nginx_log_stats(item, logstats);
		}
		else {
			//current line failed, move to next line
			while(p != buf + len && !(*p == '\0' || *p == '\n')) { ++p; }
		}
		++total_lines;
	}
	return 0;
}

static void * parallel_parse_thread_func(void * varg)
{
	if(!varg) return varg;
	auto & arg = *(parse_context*)varg;
	/*arg->buf, arg->len, arg->logstats, arg->total_lines, arg->failed_lines*/
	parse_nginx_log_item_buf(arg);

	return varg;
}

/*FIXME: nginx_domain_stat._logs*/
static int log_stats_append(std::unordered_map<std::string, nginx_domain_stat> & a,
		std::unordered_map<std::string, nginx_domain_stat> const& b)
{
	for(auto const& item : b){
		for(auto const &stat : item.second._stats)
			a[item.first]._stats[stat.first] += stat.second;
	}
	return 0;
}

static int parallel_parse_nginx_log(char * start_p, struct stat const & logfile_stat,
		std::unordered_map<std::string, nginx_domain_stat> & stats)
{
	int parallel_count = get_nprocs() - 1;			/*parallel count, exclude main_thread, maybe 0*/
	size_t min_bytes = 1024 * 1024 * 64; 	/*min 64MB*/
	for(size_t c = logfile_stat.st_size / min_bytes; c < (size_t)parallel_count; --parallel_count){ /*empty*/ }
	/*!
	 * FIXME:
	 * 1. be aware of local static vars when in multi-thread
	 * 2. disabled by default, because of little speedup
	 */
	if(!plcdn_la_opt.enable_multi_thread)
		parallel_count = 0;
	if(plcdn_la_opt.verbose)
		fprintf(stdout, "%s: logfile_size = %ld/%s, para_count=%d\n", __FUNCTION__
				, logfile_stat.st_size, byte_to_mb_kb_str(logfile_stat.st_size, "%-.2f %cB"), parallel_count);

	pthread_t threads[parallel_count];
	parse_context parse_args[parallel_count + 1];	/*include main_thread*/
	off_t offset_p = 0;
	for(int i = 0; i < parallel_count; ++i){
		static size_t len = logfile_stat.st_size / (parallel_count + 1);
		size_t nlen = (strchr(start_p  + offset_p + len - 1024 * 8, '\n') + 1 - start_p) - offset_p;

		auto& arg = parse_args[i];
		arg.buf = (char *)start_p + offset_p;
		arg.len = nlen;
		arg.total_lines = 0;
		pthread_t tid;
		int result = pthread_create(&tid, NULL, parallel_parse_thread_func, &arg);
		if(result != 0){
			fprintf(stderr, "%s: pthread_create() failed, parallel index=%d\n", __FUNCTION__, i);
			return 1;
		}
		if(plcdn_la_opt.verbose){
			char buff[64];
			printf("%s: worker_thread=%zu, process size=%zu/%s, percent=%.1f%%\n", __FUNCTION__,
					tid, nlen, byte_to_mb_kb_str_r(nlen, "%-.2f %cB", buff), (double)nlen * 100/ logfile_stat.st_size);
		}

		threads[i] = tid;
		offset_p += nlen;
	}
	size_t left_len = logfile_stat.st_size - offset_p;
	if(plcdn_la_opt.verbose){
		char buff[64];
		printf("%s: main_thread process size=%zu/%s, percent=%.1f%%\n", __FUNCTION__,
				left_len, byte_to_mb_kb_str_r(left_len, "%-.2f %cB", buff), (double)left_len * 100/ logfile_stat.st_size);
	}
	auto & arg = parse_args[parallel_count];
	arg.buf = start_p + offset_p;
	arg.len = left_len;
	arg.total_lines = 0;
	parse_nginx_log_item_buf(arg);

	for(auto & item : threads){
		void * tret;
		pthread_join(item, &tret);
		if(plcdn_la_opt.verbose)
			fprintf(stdout, "%s: thread=%zu exited\n", __FUNCTION__, item);
		auto & ct = *(parse_context * )tret;
		log_stats_append(stats, ct.logstats);
		g_line_count += ct.total_lines;
	}
	if(parallel_count == 0){
		/*FIXME: NOT needed? just for speed*/
		stats = parse_args[parallel_count].logstats;
	}
	else{
		log_stats_append(stats, parse_args[parallel_count].logstats);
	}
	g_line_count += parse_args[parallel_count].total_lines;
	if(plcdn_la_opt.verbose)
		fprintf(stdout, "%s: processed, total_line: %-8zu\n", __FUNCTION__, g_line_count);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//for srs log analysis

srs_sid::srs_sid(int sid)
:	_sid(sid)
, _site_id(0)
, _ip(0)
, _bytes(0)
{
	//none
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
static std::unordered_map<srs_sid, std::vector<srs_raw_log_t>>
	split_srs_log_by_sid(char * start_p, struct stat const & logfile_stat)
{
	std::unordered_map<srs_sid, std::vector<srs_raw_log_t>> slogs;

	srs_raw_log_t rlog;
	for(char * p = start_p, * q = p; q != start_p + logfile_stat.st_size; ++q){
		if(*q == '\n'){
			rlog.first = p;
			rlog.second = q;
			auto sid = parse_srs_log_header_sid(p);
			if(sid < 0)
				continue;

			srs_sid k(sid);
			srs_connect_ip ip;
			srs_connect_url url;
			int t = 0;
			auto ret = parse_srs_log_item_conn(rlog.first, rlog.second, ip, url, t);
			if(ret == 0){
				if(t == 1) k._ip == ip.ip;
				else if(t == 2) {
					char domain[128];
					auto r = parse_domain_from_url(url.url, domain, sizeof(domain));
					if(r == 0){
						int site_id, user_id;
						find_site_id(g_sitelist, domain, site_id, &user_id)();
						k._site_id == site_id;
					}
				}
			}
			slogs[k].push_back(rlog);

			p = q + 1;
		}
	}
	/*extract ip and url from*/
	for(auto& slog : slogs){
		auto& sid = slog.first;

		int t = 0, f = 0;
		for(auto & log : slog.second){
			if(f)
				break;
			auto ret = parse_srs_log_item_conn(log.first, log.second, ip, url, t);
			if(ret != 0)
				continue;
			t == 1? sid.
		}
	}
	return slogs;
}

/*!
 * append logs from @param slog to dir @param logdir, by sid
 * because of append, connection log preserved
 */
void append_srs_log_by_sid(std::unordered_map<int, std::vector<srs_raw_log_t>> const& slog,
		std::string const& logdir, size_t& n)
{
	/*sid : log_file*/
	std::unordered_map<int, FILE *> filemap;
	for(auto & it : slog){
		auto && dir = logdir + std::to_string(it.first);
		auto & f = filemap[it.first];
		if(!f)
			f = fopen(dir.c_str(), "a");
		if(!f) {
			fprintf(stdout, "%s: can't open srs_sid_log_file '%s' for append\n", __FUNCTION__, dir.c_str());
			continue;
		}
		for(auto& item : it.second){
			auto len = item.second - item.first;
			auto result = fwrite(item.first, sizeof(char), len, f);
			if(result < len || ferror(f))
				++n;
		}
	}
	for(auto & it : filemap) {
		if(it.second)
			fclose(it.second);
	}
}

/*parse srs log file, from start addr @param start_p and fileinfo @param logfile_stat*/
static int parse_srs_log(char * start_p, struct stat const & logfile_stat,
		std::unordered_map<std::string, srs_domain_stat> & logstats)
{
	auto && slog = split_srs_log_by_sid(start_p, logfile_stat);

	char const * logdir = "./srs_log_by_id/";
	size_t failed_lines = 0;
//	append_srs_log_by_sid(slog, logdir, failed_lines);
//
//	for(auto & it : slog){
//		auto && dir = logdir + std::to_string(it.first);
//		auto f = fopen(dir.c_str(), "r");
//		if(!f) {
//			fprintf(stdout, "%s: can't open srs_sid_log_file '%s' for read\n", __FUNCTION__, dir.c_str());
//			continue;
//		}
//	}

	return 0;
}

/*extract useful log items and parse*/
static int extract_and_parse_srs_log(char * start_p, struct stat const & logfile_stat,
		std::unordered_map<std::string, srs_domain_stat> & logstats)
{
	size_t linecount = 0, failed_count = 0, skip_count = 0;
	std::vector<srs_connect_ip> ip_items;
	std::vector<srs_connect_url> url_items;

	/*FIXME empty line!!*/
	srs_log_item logitem;
	for(char * p = start_p, * q = p; q != start_p + logfile_stat.st_size; ++q){
		if(*q == '\n'){
			*q = '\0';
			++linecount;

			int log_type;
			/*FIXME: srs_connect_ip and srs_connect_url always comes before srs_trans?*/
			auto status = parse_srs_log_item(p, logitem, log_type);
			if(status == 0) {
				switch(log_type){
				case 2:
					status = do_srs_log_stats(logitem, log_type, ip_items, url_items, logstats);
					if(status != 0)
						++failed_count;
					break;
				case 1:
					ip_items.push_back(logitem.conn_ip);
					break;
				case 4:
					url_items.push_back(logitem.conn_url);
					break;
				case 0:
					++skip_count;
					break;
				default:
					break;
				}
			}
			else
				++failed_count;
			p = q + 1;
		}
	}
	if(plcdn_la_opt.verbose)
		fprintf(stdout, "%s: processed, total_line: %zu, failed=%zu, skip=%zu\n", __FUNCTION__
				, linecount, failed_count, skip_count);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*merge*/

/*FIXME: to be continued*/
static void append_flow_table(
		std::unordered_map<std::string, nginx_domain_stat> & nginx_stats,
		std::unordered_map<std::string, srs_domain_stat> const& srs_stats)
{
	for(auto srs_domain_pair : srs_stats){
		auto & dstat = nginx_stats[srs_domain_pair.first];

		auto f = (srs_domain_pair.second._site_id == dstat._site_id
				&& srs_domain_pair.second._user_id == dstat._user_id);
		if(!f){
			fprintf(stderr, "%s: interval error! site_id or user_id not equal in nginx and srs log!, domain=%s\n",
					__FUNCTION__, srs_domain_pair.first.c_str());
			continue;
		}
		for(auto & srs_log_pair : srs_domain_pair.second._stats){
			auto & nginx_stat = dstat._stats[srs_log_pair.first];
			auto & srs_stat = srs_log_pair.second;

			/*FIXME: is it OK?*/
			char buff[strlen(srs_stat.url)];
			sha1sum_r(srs_stat.url, sizeof(buff), buff);
			nginx_stat._url_stats[buff]._bytes[-1] += (srs_stat.obytes + srs_stat.ibytes);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//main
int test_plcdn_log_analysis_main(int argc, char ** argv)
{
//	test_nginx_log_analysis_main(argc, argv);	/*for test only*/

	int result = plcdn_la_parse_options(argc, argv);
	if(result != 0 || plcdn_la_opt.show_help){
		plcdn_la_opt.show_help? plcdn_la_show_help(stdout) :
				plcdn_la_show_usage(stdout);
		return 0;
	}
	if(plcdn_la_opt.verbose)
		plcdn_la_options_fprint(stdout, &plcdn_la_opt);
	if(plcdn_la_opt.print_device_id){	//query device_id and return
		int result = load_devicelist(plcdn_la_opt.devicelist_file, g_devicelist);
		int id = result == 0? get_device_id(g_devicelist) : 0;
		fprintf(stdout, "%d\n", id);
		return result == 0? 0 : 1;
	}
	g_plcdn_la_start_time = time(NULL);
	result = load_devicelist(plcdn_la_opt.devicelist_file, g_devicelist);
	if(result != 0){
		fprintf(stderr, "%s: load_devicelist() failed\n", __FUNCTION__);
		return 1;
	}
	g_plcdn_la_device_id = plcdn_la_opt.device_id > 0? plcdn_la_opt.device_id : get_device_id(g_devicelist);

	result = load_sitelist(plcdn_la_opt.siteuidlist_file, g_sitelist);
	if(result != 0){
		fprintf(stderr, "%s: load_sitelist() failed\n", __FUNCTION__);
		return 1;
	}
#ifdef ENABLE_IPMAP
	if(plcdn_la_opt.output_file_ip_source && 0 != locisp_group::load_ipmap_file(plcdn_la_opt.ipmap_file))  {
		fprintf(stderr, "%s: ipmap_load(%s) failed\n", __FUNCTION__, plcdn_la_opt.ipmap_file);
		return 1;
	}
#else
	fprintf(stdout, "%s: ipmap DISABLED on this platform\n", __FUNCTION__);
#endif //ENABLE_IPMAP
	int interval = plcdn_la_opt.interval;
	if(plcdn_la_opt.verbose && (interval < 300 || interval > 3600)){
		fprintf(stdout, "%s: WARNING, interval(%d) too %s\n", __FUNCTION__, interval, interval < 300? "small" : "large");
	}
	time_group::_sec = interval;

	/*parse logs*/

	/*inputs*/
	FILE * nginx_log_file = NULL, * srs_log_file = NULL;
	char * nginx_file_addr = NULL, * srs_file_addr = NULL ;
	struct stat nginx_file_stat, srs_file_stat;
	/*outputs*/
	std::unordered_map<std::string, nginx_domain_stat> nginx_logstats;	/*[domain: domain_stat]*/
	std::unordered_map<std::string, srs_domain_stat>  srs_logstats;		/*[domain: srs_domain_stat]*/

	/*for nginx_log*/
	if(plcdn_la_opt.nginx_log_file){
		nginx_log_file = fopen(plcdn_la_opt.nginx_log_file, "r");
		if(!nginx_log_file) {
			fprintf(stderr, "%s: fopen file '%s' failed\n", __FUNCTION__, plcdn_la_opt.nginx_log_file);
			return 1;
		}
		auto fno = fileno(nginx_log_file);
		if(fstat(fno, &nginx_file_stat) < 0){
			fprintf(stderr, "%s: fstat() failed for %s\n", __FUNCTION__, "nginx_log_file");
			return 1;
		}
		/*FIXME: PAGE_SIZE?*/
		nginx_file_addr = (char *)mmap(NULL, nginx_file_stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fno, 0);
		if(!nginx_file_addr || nginx_file_addr == MAP_FAILED){
			fprintf(stderr, "%s: mmap() failed for %s\n", __FUNCTION__, "nginx_log_file");
			return 1;
		}

		auto status = parallel_parse_nginx_log(nginx_file_addr, nginx_file_stat, nginx_logstats);
		if(status != 0){
			fprintf(stderr, "%s: parallel_parse_nginx_log failed, exit\n", __FUNCTION__);
			return 1;
		}
		/*split log*/
		if(plcdn_la_opt.output_split_nginx_log){
			if(plcdn_la_opt.verbose)
				fprintf(stdout, "%s: splitting log file: '%s'...\n", __FUNCTION__, plcdn_la_opt.nginx_log_file);
			auto status = split_nginx_log(nginx_logstats,
					plcdn_la_opt.output_split_nginx_log, plcdn_la_opt.format_split_nginx_log);
		}
	}

	/*for srs_log*/
	if(plcdn_la_opt.srs_log_file){
		srs_log_file = fopen(plcdn_la_opt.srs_log_file, "r");
		if(!srs_log_file) {
			fprintf(stderr, "%s: fopen file '%s' failed\n", __FUNCTION__, plcdn_la_opt.srs_log_file);
			return 1;
		}
		auto fno = fileno(srs_log_file);
		if(fstat(fno, &srs_file_stat) < 0){
			fprintf(stderr, "%s: fstat() failed for %s\n", __FUNCTION__, "srs_log_file");
			return 1;
		}
		/*FIXME: PAGE_SIZE?*/
		srs_file_addr = (char *)mmap(NULL, srs_file_stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fno, 0);
		if(!srs_file_addr || srs_file_addr == MAP_FAILED){
			fprintf(stderr, "%s: mmap() failed for %s\n", __FUNCTION__, "srs_log_file");
			return 1;
		}

		auto status = extract_and_parse_srs_log(srs_file_addr, srs_file_stat, srs_logstats);
		if(status != 0){
			fprintf(stderr, "%s: parse_srs_log failed, exit\n", __FUNCTION__);
			return 1;
		}
		FILE * srs_flow = NULL;
		auto srs_f = plcdn_la_opt.output_file_srs_flow;
		if(srs_f){
			srs_flow = stdout;
			if(strcmp(srs_f, "1") != 0)
				srs_flow = fopen(srs_f, "a");
			if(!srs_flow)
				fprintf(stderr, "%s: fopen file '%s' failed\n", __FUNCTION__, srs_f);
		}
		if(srs_flow)
			fprint_srs_log_stats(srs_flow, srs_logstats);
	}
	if(!nginx_log_file && !srs_log_file){
		fprintf(stderr, "%s: none of nginx, srs log file specified or can be read, exit\n", __FUNCTION__);
		return 1;
	}
//	append_flow_table(nginx_logstats, srs_logstats);

	/*output results*/
	print_plcdn_log_stats(nginx_logstats);

	/*uinit*/
	if(nginx_file_addr)
		munmap(nginx_file_addr, nginx_file_stat.st_size);
	if(srs_file_addr)
		munmap(srs_file_addr, srs_file_stat.st_size);
	return 0;
}
