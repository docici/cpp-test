#include <time.h>	/* gmtime_s, strftime */
#include <cstdlib>	/*atoi*/
#include <cstring>	/*strcmp*/
#include <popt.h>	/*poptOption*/
#include "plcdn_la_option.h"	/* plcdn_la_options */
#include "plcdn_la_conf.h"	    /* plcdn_la_conf_t */
#include <boost/regex.hpp> 		/*boost::regex_match*/

/*main.cpp*/
extern time_t g_plcdn_la_start_time;

static char * g_confbuf = NULL;

/* plcdn_la_ngx_var.cpp */
extern void parse_args_split(char * buf, char const *& arg, char const * key, char const *& value);

/* plcdn_la_ngx_log_fmt.cpp */
extern void ngx_parse_nginx_log_format(char const * str, ngx_log_format & fmt);

static bool plcdn_la_options_is_ok(plcdn_la_options const& opt);

#define DEF_FORMAT_FLOW 			    "countfile.${interval}.${site_id}.${device_id}"
#define DEF_FORMAT_URL_POPULAR 		    "urlstat.${interval}.${site_id}.${device_id}"
#define DEF_FORMAT_IP_POPULAR   	    "UANStats.${datetime}.${device_id}"
#define DEF_FORMAT_HTTP_STATS   	    "DASStats.${datetime}.${device_id}"
#define DEF_FORMAT_IP_SLOWFAST   	    "UASStats.${interval}.${site_id}.${device_id}"
#define DEF_FORMAT_CUTIP_SLOWFAST       "ASStats.${datetime}.${device_id}"
#define DEF_FORMAT_IP_SOURCE   		    "IPSource.${interval}.${site_id}.${device_id}"
#define DEF_FORMAT_SPLIT_NGINX_LOG      "${site_id}/${day}"
#define DEF_FORMAT_SPLIT_SRS_LOG   	    "${site_id}/${day}"
#define DEF_SRS_SID_DIR				    "srs_sid_log/"
#define DEF_FORMAT_SRS_FLOW			    "srscountfile.${day}.${site_id}.${device_id}"
#define DEF_FORMAT_FILE_URL_KEY         "urlkey.${interval}.${device_id}.${site_id}"
#define DEF_FORMAT_NGINX_HTTP_REF_UA 	"httprefua.${interval}"


#define DEF_NGINX_HIT                   "STALE|UPDATING|REVALIDATED|HIT"
#define DEF_NGINX_USER_AGENT_PC         "Windows|Macintosh"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//plcdn_la_options
struct plcdn_la_options plcdn_la_opt = {
		.nginx_log_file = NULL,
		.nginx_rotate_dir = NULL,
		.nginx_rotate_time = 7200,
		.devicelist_file = "devicelist.txt",
		.siteuidlist_file = "siteuidlist.txt",
		.ipmap_file = "iplocation.bin",
		.parse_url_mode = 2,

		.nginx_hit = DEF_NGINX_HIT,
		.nginx_ua_pc = DEF_NGINX_USER_AGENT_PC,

		.begin_time = 0,
		.end_time = 0,

		.no_merge_datetime = 0,

		.srs_log_file = NULL,
		.srs_calc_flow_mode = 0,
		.output_srs_flow = NULL,
		.format_srs_flow = DEF_FORMAT_SRS_FLOW,
		.srs_sid_dir = DEF_SRS_SID_DIR,
		.output_split_srs_log_by_sid = NULL,
		.interval = 300,
		.output_nginx_flow = NULL,
		.format_nginx_flow = DEF_FORMAT_FLOW,
		.output_file_url_popular = NULL,
		.format_url_popular = DEF_FORMAT_URL_POPULAR,
		.output_file_ip_popular = NULL,
		.format_ip_popular = DEF_FORMAT_IP_POPULAR,
		.min_ip_popular = 10,
		.max_ip_popular = 0,
		.output_file_http_stats = NULL,
		.format_http_stats = DEF_FORMAT_HTTP_STATS,
		.output_file_ip_slowfast = NULL,
		.format_ip_slowfast = DEF_FORMAT_IP_SLOWFAST,
		.output_file_cutip_slowfast = NULL,
		.format_cutip_slowfast = DEF_FORMAT_CUTIP_SLOWFAST,
		.output_file_ip_source = NULL,
		.format_ip_source = DEF_FORMAT_IP_SOURCE,

		.output_file_url_key = NULL,
		.format_file_url_key = DEF_FORMAT_FILE_URL_KEY,

		.output_file_http_ref_ua = NULL,
		.format_file_http_ref_ua = DEF_FORMAT_NGINX_HTTP_REF_UA,

		.local_url_key = NULL,
		.output_split_nginx_log = NULL,
		.format_split_nginx_log = DEF_FORMAT_SPLIT_NGINX_LOG,

		.output_split_srs_log = NULL,
		.format_split_srs_log = DEF_FORMAT_SPLIT_SRS_LOG,

		.nginx_trans_log = 0,

		.device_id = 0,
		.print_device_id = 0,
		.enable_multi_thread = 0,
		.work_mode = 0,
		.append_flow_nginx = 0,
		.show_help = 0,
		.show_version = 0,

		.log_file = NULL,
		.config_file = ".plcdn_la",
		.ngx_logfmt = {
				.host = 0,
				.remote_addr = 1,
				.request_time_msec = 2,
				.upstream_cache_status = 3,
				.time_local = 4,
				.request_method = 5,
				.request_uri = 6,
				.server_protocol = 7,
				.status = 8,
				.bytes_sent = 9,
				.http_referer = 10,
				.remote_user = 11,
				.http_user_agent = 12,
				.scheme = 13,
				.request_length = 14,
				.upstream_response_time = 15,
				.start_response_time_msec = 16,
				.body_bytes_sent = 17,
				.http_x_forwarded_for = 18,
				.connection = 19,
				.server_addr = 20,
		},
		.verbose = 0,
};

static poptContext pc = 0;
static struct poptOption plcdn_la_popt[] = {
	  /* longName, shortName, argInfo, argPtr, value, descrip, argDesc */
	{"nginx-log-file",          'l',  POPT_ARG_STRING,   0, 'l', "nginx_log_file", 0 },
	{"nginx-rotate-dir",        0,    POPT_ARG_STRING,   0, 'A', "directory for nginx_rotate, also set work_mode to rotate, see NOTES for details", 0 },
	{"nginx-rotate-time",       0,    POPT_ARG_INT,      0, 'H', "time for nginx_rotate, default 7200 (in seconds)", 0 },
	{"begin-time",             	0,    POPT_ARG_STRING,   0, 'D', "time_range, default 0, begin time, see NOTES for details", 0 },
	{"end-time",          		0,    POPT_ARG_STRING,   0, 'I', "time_range, default 0, end time", 0 },
	{"no-merge-datetime",
			                     0,   POPT_ARG_NONE,      0, 'L', "default OFF, if set, don't merge rows before print output tables where ${datetime} same", 0 },

	{"device-list-file",        'd',  POPT_ARG_STRING,   0, 'd', "devicelist_file default: devicelist.txt", 0 },
	{"siteuid-list-file",       's',  POPT_ARG_STRING,   0, 's', "siteuidlist_file default: siteuidlist.txt", 0 },
	{"ipmap-file",              'm',  POPT_ARG_STRING,   0, 'm', "ipmap_file default: iplocation.bin", 0 },
	{"parse-url-mode",          0,    POPT_ARG_INT,      0, 'M', "parse nginx log field '$request_uri' url mode, 0|1|2, default 2", 0 },
	{"nginx-hit",               0,    POPT_ARG_STRING,   0, '4', "values for nginx hit, '|' separated, default '" DEF_NGINX_HIT "'", 0 },
	{"nginx-ua-pc",             0,    POPT_ARG_STRING,   0, '6', "values for nginx http_user_agent PC, '|' separated, default '" DEF_NGINX_USER_AGENT_PC "'", 0 },

	{"interval",                'i',  POPT_ARG_INT,      0, 'i', "interval in seconds, default: 300", 0 },

	{"srs-log-file",            'n',  POPT_ARG_STRING,   0, 'n', "srs_log_file", 0 },
	{"srs-calc-flow-mode",       0,   POPT_ARG_INT,      0, 'N', "0 or 1, default 0. mode for calculate srs flow, see NOTES for details", 0 },

	{"output-srs-sid",          'k',  POPT_ARG_STRING,   0, 'k', "folder for srs_log_by_sid, default '" DEF_SRS_SID_DIR "'", 0 },
	{"output-srs-flow",         'b',  POPT_ARG_STRING,   0, 'b', "output folder for srs_flow_table, disabled if NULL", 0 },
	{"format-srs-flow",         'B',  POPT_ARG_STRING,   0, 'B', "filename format for srs_flow_table, default '" DEF_FORMAT_SRS_FLOW "'", 0 },
	{"output-split-srs-log-by-sid",
			                    0,    POPT_ARG_STRING,   0, 'C', "output folder for splitted srs log(by sid), usually for debug", 0 },

	{"output-nginx-flow",       'o',  POPT_ARG_STRING,   0, 'o', "output folder for nginx_flow_table, disabled if NULL", 0 },
	{"format-nginx-flow",       'O',  POPT_ARG_STRING,   0, 'O', "filename format for nginx_flow_table, default '" DEF_FORMAT_FLOW "'", 0 },

	{"output-file-url-popular", 'u',  POPT_ARG_STRING,   0, 'u', "output_folder for url_popular_table, disabled if NULL", 0 },
	{"format-url-popular",      'U',   POPT_ARG_STRING,   0, 'U', "filename format for url_popular table, default '" DEF_FORMAT_URL_POPULAR "'", 0 },

	{"output-file-url-key",       'y',  POPT_ARG_STRING,   0, 'y', "output_folder for url_key_table, disabled if NULL",0},
	{"format-file-url-key",       'Y',  POPT_ARG_STRING,   0, 'Y', "filename format for url_key_table, default '" DEF_FORMAT_FILE_URL_KEY "'", 0},
	{"local-url-key",            0,   POPT_ARG_STRING,   0, '2', "output_folder for local_url_key, disabled if NULL, see NOTES for details",0},


	{"output-file-ip-popular",  'p',  POPT_ARG_STRING,   0, 'p', "output folder for ip_popular_table, disabled if NULL", 0 },
	{"format-ip-popular",       'P',  POPT_ARG_STRING,   0, 'P', "filename format for ip_popular table, default '" DEF_FORMAT_IP_POPULAR "'", 0 },
	{"min-ip-popular",           0,   POPT_ARG_INT,      0, 'Q', "min_access_count, filter for ip_popular table, default 10(>=), disabled if negative", 0 },
	{"max-ip-popular",           0,   POPT_ARG_INT,      0, 'S', "max_access_count, filter for ip_popular table, default unlimited(<=), disabled if negative", 0 },

	{"output-file-http-stats",  't',  POPT_ARG_STRING,   0, 't', "output folder for http_stats_table, disabled if NULL", 0 },
	{"format-http-stats",       'T',  POPT_ARG_STRING,   0, 'T', "filename format for http_stats table, default '" DEF_FORMAT_HTTP_STATS "'", 0 },

	{"output-file-ip-slowfast", 'w',  POPT_ARG_STRING,   0, 'w', "output folder for ip_slowfast_table, disabled if NULL", 0 },
	{"format-ip-slowfast",      'W',  POPT_ARG_STRING,   0, 'W', "filename format for ip_slowfast table, default '" DEF_FORMAT_IP_SLOWFAST "'", 0 },

	{"output-file-cutip-slowfast"
							  , 'f',  POPT_ARG_STRING,   0, 'f', "output folder for cutip_slowfast_table, disabled if NULL", 0 },
	{"format-cutip-slowfast",   'F',  POPT_ARG_STRING,   0, 'F', "filename format for cutip_slowfast table, default '" DEF_FORMAT_CUTIP_SLOWFAST "'", 0 },

	{"output-file-ip-source",   'r',  POPT_ARG_STRING,   0, 'r', "output folder for ip_source_table, disabled if NULL", 0 },
	{"format-ip-source",        'R',   POPT_ARG_STRING,  0, 'R', "filename format for ip_source table, default '" DEF_FORMAT_IP_SOURCE "'", 0 },

	{"output-file-http-ref-ua", 'e',  POPT_ARG_STRING,   0, '5', "output folder for nginx_httpref_ua_table, disabled if NULL", 0 },


	{"output-split-nginx-log",  'g',  POPT_ARG_STRING,   0, 'g', "output folder for split_nginx_log, disabled if NULL", 0 },
	{"format-split-nginx-log",  'G',  POPT_ARG_STRING,   0, 'G', "filename format for split_nginx_log, default '" DEF_FORMAT_SPLIT_NGINX_LOG "'", 0 },

	{"output-split-srs-log",    'j',  POPT_ARG_STRING,   0, 'j', "output folder for split_srs_log, disabled if NULL", 0 },
	{"format-split-srs-log",    'J',  POPT_ARG_STRING,   0, 'J', "filename format for split_srs_log, default '" DEF_FORMAT_SPLIT_SRS_LOG "'", 0 },

/* for transform log */
	{"nginx-transform-log",         0,  POPT_ARG_INT,    0, '1', "transform nginx log, disabled if 0, ${user_id}", 0 },

	{"device-id",                 0,  POPT_ARG_INT,      0, 'e', "device_id integer(> 0)", 0 },
	{"print-divice-id",         'c',  POPT_ARG_NONE,     0, 'c', "print device_id and exit", 0 },
	{"enable-multi-thread",     0,  POPT_ARG_NONE,       0, 'a', "enable_multi_thread, ONLY for nginx yet", 0 },
	{"merge-srs-flow",          0,  POPT_ARG_NONE,       0, 'E', "set work_mode to merge_srs_flow, see NOTES for details", 0 },
	{"append-flow-nginx",       0,  POPT_ARG_NONE,       0, 'X', "if set, append other(currently srs) flows to nginx", 0 },
	{"help",                    'h',    POPT_ARG_NONE,   0, 'h', "print this help", 0 },
	{"version",                   0,    POPT_ARG_NONE,   0, 'V', "print version info and exit", 0},
	{"log-file",                0,    POPT_ARG_STRING,   0, '3', "log file for error(default to stderr)", 0},
	{"config-file",             0,    POPT_ARG_STRING,   0, '7', "config file, default .plcdn_la", 0},
	{"verbose",                 'v',  POPT_ARG_INT,     0, 'v', "verbose, >=0, print more details, 0 for close", 0},
	NULL	/*required!!!*/
};

/* sample: '2016-10-31 14:00:04' */
/* TODO: to '%Y-%m-%d %H:%M:%S' */
static int parse_time(char const * str, time_t & t)
{
	if(!str || str[0] == '\0')
		return -1;
	auto s1 = "([0-9]{4})-([0-9]{2})-([0-9]{2})";
	boost::regex re{s1};
	boost::cmatch cm;
	if(!boost::regex_match(str, cm, re))
		return -1;
	tm my_tm{ 0 };
	auto result = strptime(str, "%Y-%m-%d", &my_tm);
	if(!result)
		return -1;
	t = mktime(&my_tm);
	return 0;
}

#define PLCDN_LA_CONF(conf, opt, section, field, len) \
   {auto && s = conf.impl.get<std::string>(section); \
	if(!s.empty()){                                  \
		strcat(g_confbuf + len, s.c_str());          \
		field = g_confbuf + len;                     \
		len += s.size();                             \
		g_confbuf[len] = '\0';                       \
	}                                                \
   }

int reset_plcdn_la_options(plcdn_la_conf_t const& conf, plcdn_la_options& opt)
{
	return -1;
	if(!g_confbuf)
		g_confbuf = (char *)malloc(1024 * 2);
	if(!g_confbuf)
		return -1;

	size_t len = 0;


	auto && str = plcdn_la_config_get_string(conf, "nginx_log_format");
	if(!str.empty())
		ngx_parse_nginx_log_format(str.c_str(), plcdn_la_opt.ngx_logfmt);

	PLCDN_LA_CONF(conf, opt, "NginxFile", opt.nginx_log_file, len);
	PLCDN_LA_CONF(conf, opt, "IPMAP", opt.nginx_log_file, len);

//	auto && s = conf.impl.get<std::string>("NginxFile");
//	if(!s.empty()){
//		strcat(g_confbuf + len, s.c_str());
//		opt.nginx_log_file = g_confbuf + len;
//
//		len += s.size(); g_confbuf[len] = '\0';
//	}
//	s = conf.impl.get<std::string>("IPMAP");
//	if(!s.empty()){
//		strcat(g_confbuf + len, s.c_str());
//		len += s.size(); g_confbuf[len] = '\0';
//
//		opt.nginx_log_file = g_confbuf + len;
//	}

	return 0;
}

int plcdn_la_parse_options(int argc, char ** argv)
{
	if(pc)
		poptFreeContext(pc);
	pc = poptGetContext("plcdn_log_analysis", argc, (const char **)argv, plcdn_la_popt, 0);
	for(int opt; (opt = poptGetNextOpt(pc)) != -1; ){
		switch(opt){
		case '7': {
			plcdn_la_opt.config_file = poptGetOptArg(pc);
			plcdn_la_conf_t conf;
			if(plcdn_la_parse_config_file(plcdn_la_opt.config_file, conf) == 0)
				reset_plcdn_la_options(conf, plcdn_la_opt);
		}
		break;
		case 'i': plcdn_la_opt.interval = atoi(poptGetOptArg(pc)); break;
		case 'l': plcdn_la_opt.nginx_log_file = poptGetOptArg(pc); break;
		case 'D':{
			auto c = poptGetOptArg(pc);
			if(c && strcmp(c, "0") == 0)
				plcdn_la_opt.begin_time = 0;
			else if(c && strcmp(c, "1") == 0){
				/* @see time_group */
				size_t n = difftime(g_plcdn_la_start_time, 0) / plcdn_la_opt.interval;
				plcdn_la_opt.begin_time = (n - 1) * plcdn_la_opt.interval;
			}
			else{
				if(parse_time(c, plcdn_la_opt.begin_time) != 0)
					return -1;
			}
/*			printf("%s: t=%zu, c='%s', begin_time=%zu, interval=%d\n", __FUNCTION__,
					g_plcdn_la_start_time, c, plcdn_la_opt.begin_time, plcdn_la_opt.interval);*/
		}
		break;
		case 'I':{
			auto c = poptGetOptArg(pc);
			if(c && strcmp(c, "0") == 0)
				plcdn_la_opt.end_time = 0;
			else if(c && strcmp(c, "1") == 0){
				/* @see time_group */
				size_t n = difftime(g_plcdn_la_start_time, 0) / plcdn_la_opt.interval;
				plcdn_la_opt.end_time = n * plcdn_la_opt.interval;
			}
			else{
				if(parse_time(c, plcdn_la_opt.end_time) != 0)
					return -1;
			}
			/*printf("%s: c='%s', end_time=%zu, interval=%d\n", __FUNCTION__, c, plcdn_la_opt.end_time, plcdn_la_opt.interval);*/
		}
		break;

		case 'n': plcdn_la_opt.srs_log_file = poptGetOptArg(pc); break;
		case 'A': {
				plcdn_la_opt.work_mode = 2;
				plcdn_la_opt.nginx_rotate_dir = poptGetOptArg(pc);
				plcdn_la_opt.no_merge_datetime = 0;
			} break;
		case 'H': plcdn_la_opt.nginx_rotate_time = atoi(poptGetOptArg(pc)); break;
		case 'N': plcdn_la_opt.srs_calc_flow_mode = atoi(poptGetOptArg(pc)); break;
		case 'L': {
			plcdn_la_opt.no_merge_datetime = 1;
			if(plcdn_la_opt.work_mode == 2)
				plcdn_la_opt.no_merge_datetime = 0;
		} break;
		case 'k': plcdn_la_opt.srs_sid_dir = poptGetOptArg(pc); break;
		case 'b': plcdn_la_opt.output_srs_flow = poptGetOptArg(pc); break;
		case 'B': plcdn_la_opt.format_srs_flow = poptGetOptArg(pc); break;
		case 'C': plcdn_la_opt.output_split_srs_log_by_sid = poptGetOptArg(pc); break;

		case 'e': plcdn_la_opt.device_id = atoi(poptGetOptArg(pc)); break;
		case 'd': plcdn_la_opt.devicelist_file = poptGetOptArg(pc); break;
		case 's': plcdn_la_opt.siteuidlist_file = poptGetOptArg(pc); break;
		case 'm': plcdn_la_opt.ipmap_file = poptGetOptArg(pc); break;

		case 'o': { plcdn_la_opt.output_nginx_flow = poptGetOptArg(pc); } break;
		case 'O': { plcdn_la_opt.format_nginx_flow = poptGetOptArg(pc); } break;

		case 'u': { plcdn_la_opt.output_file_url_popular = poptGetOptArg(pc); }; break;
		case 'U': { plcdn_la_opt.format_url_popular= poptGetOptArg(pc); }; break;

		case 'y': { plcdn_la_opt.output_file_url_key = poptGetOptArg(pc); }; break;
		case 'Y': { plcdn_la_opt.format_file_url_key = poptGetOptArg(pc); }; break;

		case '2': { plcdn_la_opt.local_url_key = poptGetOptArg(pc); }; break;
		case 'p': { plcdn_la_opt.output_file_ip_popular = poptGetOptArg(pc); } break;
		case 'P': { plcdn_la_opt.format_ip_popular = poptGetOptArg(pc); } break;
		case 'Q': { plcdn_la_opt.min_ip_popular = atoi(poptGetOptArg(pc)); } break;
		case 'S': { plcdn_la_opt.max_ip_popular = atoi(poptGetOptArg(pc)); } break;

		case 't': { plcdn_la_opt.output_file_http_stats = poptGetOptArg(pc); } break;
		case 'T': { plcdn_la_opt.format_http_stats = poptGetOptArg(pc); } break;

		case 'w': { plcdn_la_opt.output_file_ip_slowfast = poptGetOptArg(pc); } break;
		case 'W': { plcdn_la_opt.format_ip_slowfast = poptGetOptArg(pc); } break;

		case 'f': { plcdn_la_opt.output_file_cutip_slowfast = poptGetOptArg(pc); } break;
		case 'F': { plcdn_la_opt.format_cutip_slowfast = poptGetOptArg(pc); } break;

		case 'r': { plcdn_la_opt.output_file_ip_source = poptGetOptArg(pc); }; break;
		case 'R': { plcdn_la_opt.format_ip_source = poptGetOptArg(pc); }; break;

		case '5': {
			parse_args_split(poptGetOptArg(pc), plcdn_la_opt.output_file_http_ref_ua,
					"fmt", plcdn_la_opt.format_file_http_ref_ua);
		};
		break;

		case 'g': plcdn_la_opt.output_split_nginx_log = poptGetOptArg(pc); break;
		case 'G': plcdn_la_opt.format_split_nginx_log = poptGetOptArg(pc); break;

		case 'j': plcdn_la_opt.output_split_srs_log = poptGetOptArg(pc); break;
		case 'J': plcdn_la_opt.format_split_srs_log = poptGetOptArg(pc); break;

		case '1': plcdn_la_opt.nginx_trans_log = atoi(poptGetOptArg(pc)); break;

		case 'c': plcdn_la_opt.print_device_id = 1; break;
		case 'a': plcdn_la_opt.enable_multi_thread = 1; break;
		case 'E': plcdn_la_opt.work_mode = 1; break;
		case 'M': plcdn_la_opt.parse_url_mode = atoi(poptGetOptArg(pc)); break;
		case '4': plcdn_la_opt.nginx_hit = poptGetOptArg(pc); break;
		case '6': plcdn_la_opt.nginx_ua_pc = poptGetOptArg(pc); break;
		case 'X': plcdn_la_opt.append_flow_nginx = 1; break;
		case 'h': plcdn_la_opt.show_help = 1; break;
		case 'V': plcdn_la_opt.show_version = 1; break;
		case '3': plcdn_la_opt.log_file = poptGetOptArg(pc); break;
		case 'v': plcdn_la_opt.verbose = atoi(poptGetOptArg(pc)); break;
		default:
			break;
		}
	}

	return plcdn_la_options_is_ok(plcdn_la_opt)? 0 : -1;
}

int test_plcdn_log_analysis_options_main(int argc, char ** argv)
{
	return plcdn_la_parse_options(argc, argv);
}

void plcdn_la_show_help(FILE * stream)
{
	fprintf(stream, "analysis log file, print result tables, or merge results. currently support nginx, srs log files. build at %s %s\n"
			, __DATE__, __TIME__);
	fprintf(stream, "\n****************************************************************************************************************\n");
	fprintf(stream, "branch: 'master'\n");
	fprintf(stream, "****************************************************************************************************************\n\n");
	poptPrintHelp(pc, stream, 0);
	fprintf(stream, "NOTES:\n"
			"  1.work_mode\n"
			"    analysis: analysis log file and output result tables, for a single log file(usually huge), default\n"
			"    rotate: rotate log file(usually continuous, periodic log pieces from a daemon), analysis and output result tables(update it if needed)\n"
			"            NOTES: only available for nginx currently; option '--no-merge-datetime' is ignored and always be OFF in this mode\n"
			"    merge_srs_flow: merge srs_flow_table(use --merge-srs-flow). output format: '${datetime} ${obytes} ${ibytes} ${obps} ${ibps} ${user_id}'\n"
			"  2.about 'filename format'(option --format-*, e.g. --format-ip-source):\n"
	        "    ${datetime}   current date time, format YYYYmmDDHHMM\n"
			"    ${interval}   according to option --interval, in minute, format YYYYmmDDHHMM\n"
			"    ${day}        $time_local in log, in day, format YYYYmmDD\n"
			"    ${device_id}  device_id\n"
			"    ${site_id}    site_id/domain_id\n"
			"    ${user_id}    user_id\n"
			"    ${domain}     domain\n"
			"  3.time_range, range in [begin_time, end_time), applied for both nginx and srs log if enabled, format:\n"
			"    (1)'YYYY-mm-dd', sample '2017-02-14'\n"
			"    (2)'1'           use interval time, according to system time and --interval, sample: \n"
			"                     system time: 2017-03-29 14:13:05, --interval 300, then time_range = [2017-03-29 14:05:00, 2017-03-29 14:10:00)\n"
			"    (3)'0'           default, unlimited\n"
			"  4.use ulimit(or other command) to increase 'open files', or may crash!\n"
			"  5.about srs: https://github.com/ossrs/srs/wiki/v2_CN_Home\n"
			"  6.nginx_log_format: '$host $remote_addr $request_time_msec $upstream_cache_status [$time_local] \"$request_method $request_uri $server_protocol\" \\\n"
			"      $status $bytes_sent \"$http_referer\" \"$remote_user\" - \"$http_user_agent\" $scheme $request_length $upstream_response_time \\\n"
			"      $start_response_time_msec $body_bytes_sent \"$http_x_forwarded_for\" \"$connection\" \"$server_addr\"'\n"
			"  7.DO NOT mix up option '--output-srs-sid' with '--output-split-srs-log' when split srs log!\n"
			"  8.output table formats\n"
			"    for nginx:\n"
			"    (1)nginx_flow_table:      '${site_id} ${datetime} ${device_id} ${num_total} ${bytes_total} ${user_id} \\\n"
			"                                 ${pvs_m} ${px_m} ${tx_rtmp_in} ${tx_rtmp_out} ${loc} ${isp} ${fst_pkg_time} ${svg_speed}'\n"
			"    (2)url_popular_table:     '${url_key} ${num_total} ${num_200} ${size_200} ${num_206} ${size_206} ${num_301302} \\\n"
		    "                                 ${num_304} ${num_403} ${num_404} ${num_416} ${num_499} ${num_500} ${num_502} ${num_other}'\n"
			"    (3)ip_popular_table:      '${site_id} ${device_id} ${ip} ${datetime} ${num}'\n"
			"    (4)http_stats_table:      '${site_id} ${device_id} ${httpstatus} ${datetime} ${num} ${num_m} ${loc} ${isp}'\n"
			"    (5)ip_slowfast_table:     '${device_id} ${ip} ${datetime} ${speed} ${type}'\n"
			"    (6)cutip_slowfast_table:  '${device_id} ${datetime} ${ip} ${speed}'\n"
			"    (7)ip_source_table:       '${datetime} ${local_id} ${isp_id} ${pvs} ${tx} ${pvs_m} ${tx_m} ${device_id}'\n"
            "    (8)url_key_table:         '$[+-]\"{url_key}\"${url}'(note: '\"' separated)\n"
			"    (9)http_referer_ua_table: '${datetime} ${device_id} ${site_id} ${user_id} ${domain} \\\n"
			"                                 ${bytes_total} ${access_total} ${bytes_pc} ${access_pc} ${bytes_mobile} ${access_mobile}'\n"
			"    for srs:\n"
			"    (1)srs_flow_table:       '${site_id} ${datetime} ${device_id} ${obytes} ${ibytes} ${obps} ${ibps} ${user_id}'\n"
			"  9.for srs log, currently supports 2 formats of trans_log, 0: official , 1: custom\n"
			"    >>sample official_format: '[2016-12-07 14:49:54.057][trace][20308][105] <- CPB time=1980013, \\\n"
            "      okbps=0,0,0, ikbps=477,428,472, mr=0/350, p1stpt=20000, pnt=20000'\n"
			"    >>sample custom_format: '[2017-02-07 15:03:31.138][trace][6946][107] time=3460008, type=CPB, ip=127.0.0.1, \\\n"
			"      tcUrl=rtmp://localhost/live, vhost=__defaultVhost__, obytes=4187, ibytes=206957159, okbps=0,0,0, ikbps=475,580,471'\n"
			"  10.about option --srs-calc-flow-mode, 0: use obytes/ibytes, 1: use okbps/ikbps\n"
			"  11.file '--device-list-file' format: '${device_id} ${device_ip}'\n"
			"  12.file '--siteuid-list-file' format: '${site_id} ${user_id} ${domain} ${is_top}'\n"
			"  13.option '--local-url-key' only support ${site_id}(default if no filename), ${user_id} in filename(NOT folder name), create dirs if NOT exist.\n"
			"     sample: '/tmp/LocalUrlKey/${site_id}', '/tmp/LocalUrlKey/'(use default ${site_id} as filename)\n"
	);
}

void plcdn_la_show_usage(FILE * stream)
{
	poptPrintUsage(pc, stream, 0);
}

static bool plcdn_la_options_is_ok(plcdn_la_options const& opt)
{
	/*FIXME: update this function*/
	if(opt.show_help) return true;
	if(opt.show_version) return true;
	return true;
}

void plcdn_la_options_fprint(FILE * stream, plcdn_la_options const * popt)
{
	if(!popt) return;
	auto& opt = *popt;

	char btime[32] = "0", etime[32] = "0";
	if(opt.begin_time != 0){
		tm btmbuf;
		strftime(btime, sizeof(btime), "%Y-%m-%d %H:%M:%S", localtime_r(&opt.begin_time, &btmbuf));
	}
	if(opt.end_time != 0){
		tm etmbuf;
		strftime(etime, sizeof(etime), "%Y-%m-%d %H:%M:%S", localtime_r(&opt.end_time, &etmbuf));
	}
	fprintf(stream,
			"%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20d\n" "%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20d\n" "%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20d\n" "%-34s%-20d\n" "%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20d\n" "%-34s%-20d\n"
			"%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20d\n" "%-34s%-20d\n" "%-34s%-20d\n"
			"%-34s%-20d\n" "%-34s%-20d\n"

			"%-34s%-20s\n" "%-34s%-20s\n"

			"%-34s%-20d\n" "%-34s%-20d\n" "%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20d\n"
		, "nginx_log_file", opt.nginx_log_file
		, "nginx_rotate_dir", opt.nginx_rotate_dir
		, "nginx_rotate_time", opt.nginx_rotate_time
		, "begin_time", btime
		, "end_time", etime

		, "interval", opt.interval
		, "devicelist_file", opt.devicelist_file
		, "siteuidlist_file", opt.siteuidlist_file
		, "ipmap_file", opt.ipmap_file

		, "srs_log_file", opt.srs_log_file
		, "srs_calc_flow_mode", opt.srs_calc_flow_mode
		, "no_merge_datetime", opt.no_merge_datetime
		, "srs_sid_dir", opt.srs_sid_dir
		, "output_split_srs_log_by_sid", opt.output_split_srs_log_by_sid
		, "output_srs_flow", opt.output_srs_flow
		, "format_srs_flow", opt.format_srs_flow

		, "output_nginx_flow", opt.output_nginx_flow
		, "format_nginx_flow", opt.format_nginx_flow

		, "output_file_url_popular", opt.output_file_url_popular
		, "format_url_popular", opt.format_url_popular


		, "output_file_ip_popular", opt.output_file_ip_popular
		, "format_ip_popular", opt.format_ip_popular
		, "min_ip_popular", opt.min_ip_popular
		, "max_ip_popular", opt.max_ip_popular

		, "output_file_http_stats", opt.output_file_http_stats
		, "format_http_stats", opt.format_http_stats

		, "output_file_ip_slowfast", opt.output_file_ip_slowfast
		, "format_ip_slowfast", opt.format_ip_slowfast

		, "output_file_cutip_slowfast", opt.output_file_cutip_slowfast
		, "format_cutip_slowfast", opt.format_cutip_slowfast
		, "output_file_ip_source", opt.output_file_ip_source
		, "format_ip_source", opt.format_ip_source

		, "output_file_url_key", opt.output_file_url_key
		, "format_file_url_key", opt.format_file_url_key
		, "output_file_http_ref_ua", opt.output_file_http_ref_ua
		, "format_file_http_ref_ua", opt.format_file_http_ref_ua
		, "local_url_key", opt.local_url_key

		, "output_split_nginx_log", opt.output_split_nginx_log
		, "format_split_nginx_log", opt.format_split_nginx_log

		, "output_split_srs_log", opt.output_split_srs_log
		, "format_split_srs_log", opt.format_split_srs_log

		, "work_mode", (opt.work_mode == 0? "analysis"
					: (opt.work_mode == 1? "merge_srs_flow"
					: (opt.work_mode == 2? "rotate" : "<error>")))
		, "append_flow_nginx", opt.append_flow_nginx
		, "device_id", opt.device_id
		, "nginx_trans_log", opt.nginx_trans_log

		, "print_device_id", opt.print_device_id
		, "parse_url_mode", opt.parse_url_mode

		, "nginx_hit", opt.nginx_hit
		, "nginx_ua_pc", opt.nginx_ua_pc

		, "show_help", opt.show_help
		, "show_version", opt.show_version
		, "log_file", opt.log_file
		, "config_file", opt.config_file

		, "verbose", opt.verbose
	);
}
