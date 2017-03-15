/*!
 * This file is PART of plcdn_log_analysis
 * @author hongjun.liao <docici@126.com>
 * @date 2017/03/07

 * transform log format, currently only for nginx
 * @NOTE:
 * 1.facebook.folly used, see https://github.com/facebook/folly
 * clone:
 * (1)git clone http://git.oschina.net/SuzhenProjects/folly
 * (2)git remote add github https://github.com/facebook/folly.git
 * (3)git pull github master
 * build:
 * see https://github.com/facebook/folly
 * use in gcc:
 * -L ${folly}/.libs/ -lfollybase
 *
 * @date 2017/03/15
 * change to use pl_logtrans_trans_file instead, a faster version
 */

/*
 * LOGTRANS_USE_REGEX_REPlACE  use boost.regex_place
 * LOGTRANS_USE_FACEBOOK_FOLLY use facebook.folly
 * else use the faster version
 * */
//#define LOGTRANS_USE_REGEX_REPlACE

#include "test_options.h"	/* plcdn_la_options */
#include <stdio.h>

/*plcdn_log_analysis/option.cpp*/
extern struct plcdn_la_options plcdn_la_opt;

#ifdef LOGTRANS_USE_REGEX_REPlACE
#include <string.h>				/* strcpy */
#include "nginx_log_analysis.h"	/* do_parse_nginx_log_item */

/* user: yunduan, url: https://www.isurecloud.com/ */
#define CUSTOME_FORMAT_YUNDUAN_REGEX \
"$remote_addr  -  $remote_user [$time_local] \"$request_method $scheme://$host$request_uri $server_protocol\" $status \
$request_time $body_bytes_sent $bytes_sent \"$http_referer\" \
$http_user_agent \"$http_x_forwarded_for\"  \"$connection\" \"$HIT\" $server_addr"

/*parse_fmt.cpp*/
extern int parse_fmt(char *in_out, std::unordered_map<std::string, std::string> const& argmap);

/* replace @param fmt with @param m, if NOT exist, use default value @param s
 * @note: 1.@param fmt is an in_and_out param */
static int do_nginx_transform_log(char** m, char * fmt, char const * s = "-");

/* use boost::regex_replace */
static int do_nginx_transform_log(char** m, char * fmt, char const * s /*= "-"*/)
{
	if(!m || !fmt)
		return -1;
	std::unordered_map<std::string, std::string> argmap{
		{ "\\$host", (m[0]? m[0] : s) },  { "\\$remote_addr", (m[1]? m[1] : s) },  { "\\$request_time", (m[2]? m[2] : s) },
		{ "\\$upstream_cache_status", (m[3]? m[3] : s) },  { "\\$time_local", (m[4]? m[4] : s) },  { "\\$request_method", (m[5]? m[5] : s) },
		{ "\\$request_uri", (m[6]? m[6] : s) },  { "\\$server_protocol", (m[7]? m[7] : s) },  { "\\$status", (m[8]? m[8] : s) },
		{ "\\$bytes_sent", (m[9]? m[9] : s) },  { "\\$http_referer", (m[10]? m[10] : s) },  { "\\$remote_user", (m[11]? m[11] : s) },
		{ "\\$http_cookie", (m[12]? m[12] : s) },  { "\\$http_user_agent", (m[13]? m[13] : s) },  { "\\$scheme", (m[14]? m[14] : s) },
		{ "\\$request_length", (m[15]? m[15] : s) },  { "\\$upstream_response_time", (m[16]? m[16] : s) },  { "\\$body_bytes_sent", (m[17]? m[17] : s) },
		{ "\\$http_x_forwarded_for", (m[18]? m[18] : s) },  { "\\$connection", (m[19]? m[19] : s) },  { "\\$server_addr", (m[20]? m[20] : s) },
	};
	argmap["HIT"] = m[3]? (strncmp(m[3], "HIT", 3) == 0? "HIT" : "MISS") : s;

	char buff[1024 * 64];
	strncpy(buff, s, sizeof(buff));
	snprintf(buff, sizeof(buff), "%s %s://%s%s %s", (m[5]? m[5] : s), (m[14]? m[14] : s),
			(m[0]? m[0] : s), (m[6]? m[6] : s), (m[7]? m[7] : s));
	argmap["request"] = buff;

	parse_fmt(fmt, argmap);
	return 0;
}


int nginx_transform_log(FILE * in, FILE * out, int fmt)
{
	if(!in || !out || fmt <= 0)
		return -1;
	char const * v[2] = { "[\"", "]\"" };
	char buff[1024 * 64];
	while(fgets(buff, sizeof(buff), in)){
		auto p = buff;
		char *items[60] = { 0 };
		int result = do_parse_nginx_log_item(items, p, v, {5}, '\n');
		if(result != 0){
			if(plcdn_la_opt.verbose > 3)
				fprintf(stderr, "%s: parse failed, skip:\n%s", __FUNCTION__, buff);
			continue;
		}
		/*use boost::regex_replace */
		fprintf(stdout, "%s: WARNING, facebook.folly disabled, use boost.regex instead(poor efficiency)\n", __FUNCTION__);
//		char const * fmtstr = "05 07 \"08.1://08.2";
		char outbuff[1024 * 64];
		strcpy(outbuff, (fmt == 2? CUSTOME_FORMAT_YUNDUAN_REGEX : ""));
		result = do_nginx_transform_log(items, outbuff);

		if(result != 0){
			if(plcdn_la_opt.verbose > 3)
				fprintf(stderr, "%s: transform failed, skip:\n%s", __FUNCTION__, buff);
			continue;
		}
		if(fprintf(out, "%s\n", outbuff) == EOF){
			if(plcdn_la_opt.verbose > 3)
				fprintf(stderr, "%s: fputs failed, skip:\n%s", __FUNCTION__, outbuff);
		}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
#elif (defined LOGTRANS_USE_FACEBOOK_FOLLY)
#include "folly/Format.h"	/* folly::svformat */
#include "nginx_log_analysis.h"	/* do_parse_nginx_log_item */

#define CUSTOME_FORMAT_YUNDUAN_FOLLY \
"{remote_addr} - {remote_user} [{time_local}] \"{request_method} {scheme}://{host}{request_uri} {server_protocol}\" {status} \
{request_time} {body_bytes_sent} {bytes_sent} \"{http_referer}\" \
{http_user_agent} \"{http_x_forwarded_for}\" \"{connection}\" \"{HIT}\" {server_addr}"

/* override version */
static int do_nginx_transform_log(char** m, char const * fmt, std::string& out, char const * s = "-");


/* use facebook.folly::svformat */
static int do_nginx_transform_log(char** m, char const * fmt, std::string& out, char const * s /*= "-"*/)
{
	if(!m || !fmt)
		return -1;
	/* NOTE: there is NO '$' */
	std::unordered_map<std::string, std::string> argmap{
		{ "host", (m[0]? m[0] : s) },  { "remote_addr", (m[1]? m[1] : s) },  { "request_time", (m[2]? m[2] : s) },
		{ "upstream_cache_status", (m[3]? m[3] : s) },  { "time_local", (m[4]? m[4] : s) },  { "request_method", (m[5]? m[5] : s) },
		{ "request_uri", (m[6]? m[6] : s) },  { "server_protocol", (m[7]? m[7] : s) },  { "status", (m[8]? m[8] : s) },
		{ "bytes_sent", (m[9]? m[9] : s) },  { "http_referer", (m[10]? m[10] : s) },  { "remote_user", (m[11]? m[11] : s) },
		{ "http_cookie", (m[12]? m[12] : s) },  { "http_user_agent", (m[13]? m[13] : s) },  { "scheme", (m[14]? m[14] : s) },
		{ "request_length", (m[15]? m[15] : s) },  { "upstream_response_time", (m[16]? m[16] : s) },  { "body_bytes_sent", (m[17]? m[17] : s) },
		{ "http_x_forwarded_for", (m[18]? m[18] : s) },  { "connection", (m[19]? m[19] : s) },  { "server_addr", (m[20]? m[20] : s) },
	};
	argmap["HIT"] = m[3]? (strncmp(m[3], "HIT", 3) == 0? "HIT" : "MISS") : s;
	argmap["request"] = folly::svformat("{request_method} {scheme}://{host}{request_uri} {server_protocol}", argmap);
	out = folly::svformat(CUSTOME_FORMAT_YUNDUAN_FOLLY, argmap);
	return 0;
}

int nginx_transform_log(FILE * in, FILE * out, int fmt)
{
	if(!in || !out || fmt <= 0)
		return -1;
	char const * v[2] = { "[\"", "]\"" };
	char buff[1024 * 64];
	while(fgets(buff, sizeof(buff), in)){
		auto p = buff;
		char *items[60] = { 0 };
		int result = do_parse_nginx_log_item(items, p, v, {5}, '\n');
		if(result != 0){
			if(plcdn_la_opt.verbose > 3)
				fprintf(stderr, "%s: parse failed, skip:\n%s", __FUNCTION__, buff);
			continue;
		}
		/*use folly::svformat */
		std::string outstr;
		result = do_nginx_transform_log(items, CUSTOME_FORMAT_YUNDUAN_FOLLY, outstr);
		auto outbuff = outstr.c_str();
		if(result != 0){
			if(plcdn_la_opt.verbose > 3)
				fprintf(stderr, "%s: transform failed, skip:\n%s", __FUNCTION__, buff);
			continue;
		}
		if(fprintf(out, "%s\n", outbuff) == EOF){
			if(plcdn_la_opt.verbose > 3)
				fprintf(stderr, "%s: fputs failed, skip:\n%s", __FUNCTION__, outbuff);
		}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
#else	/* use the faster verison */
/* test_plcdn_log_transform2.cpp */
extern int pl_logtrans_trans_file(char const * fmt, int rn, FILE * in, FILE * out);

int nginx_transform_log(FILE * in, FILE * out, int fmt)
{
	if(fmt == 2){	/* user/yunduan */
		size_t RN = 21;	/* field count for original file line */
		/* "%1 - %11 [%4] %5 \"%14://%0%6 %7\" %8 %2 %17 %9 \"%10\" %13 \"%18\" \"%19\" \"HIT\" %20\n" */
		return pl_logtrans_trans_file("%1 - %11 [%4] %5 \"%14://%0%6 %7\" %8 %2 %17 %9 \"%10\" %13 \"%18\" \"%19\" \"HIT\" %20\n",
				RN, stdin, stdout);
	}
	if(plcdn_la_opt.verbose)
		fprintf(stderr, "%s: format %d unrecognized\n", __FUNCTION__, fmt);
	return -1;
}

#endif
