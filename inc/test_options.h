/*parse options and arguments*/

#ifndef _CPP_TEST_OPTIONS_H_
#define _CPP_TEST_OPTIONS_H_

#ifdef __cplusplus
extern "C"{
#endif

/*nla: nginx_log_analysis*/
struct nla_options
{
	char const * log_file;
	int  interval;
	char const * devicelist_file;
	char const * siteuidlist_file;
	char const * ipmap_file;

	char const * output_file_flow;	/*'1' for stdout*/
	char const * output_file_url_popular;
	bool output_file_url_popular_split;
	char const * output_file_ip_popular;
	char const * output_file_http_stats;
	char const * output_file_ip_slowfast;
	char const * output_file_cutip_slowfast;
	char const * output_file_ip_source;

	int flow; 			/*print flow table?*/
	int url_popular; 	/*print url_popular table?*/
	int ip_popular; 	/*print ip_popular table?*/
	int http_stats; 	/*print http_stats table?*/
	int cutip_slowfast; 	/*print cutip_slowfast table?*/
	int ip_source; 		/*print ip_source table?*/

	int device_id;		/*if not provided, find it in devicelist_file by local machine ip*/
	int print_device_id;
	int print_site_user_id;
	int enable_multi_thread;	/*enalbe_multi_thread?*/
	int show_help;
	int show_version;
	int verbose;
};

/*test_options.cpp*/
void nla_options_fprint(FILE * stream, nla_options const * opt);
int nginx_log_stats_parse_options(int argc, char ** argv);
void nginx_log_stats_show_help(FILE * stream);
void nginx_log_stats_show_usage(FILE * stream);

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif /*_CPP_TEST_OPTIONS_H_*/