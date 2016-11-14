#include "test_options.h"
#include <popt.h>	/*poptOption*/
#include <cstdlib>	/*atoi*/
#include <cstring>	/*strcmp*/
#include <unordered_map>		/*std::unordered_map*/
#include <string>				/*std::string*/
#include <boost/regex.hpp> 		/*boost::regex_search*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//nla_options

static bool nla_options_is_ok(nla_options const& opt);

#define DEF_FORMAT_FLOW 	"countfile.${interval}.${site_id}.${device_id}"
#define DEF_FORMAT_URL_POPULAR 	"urlstat.${interval}.${site_id}.${device_id}"
#define DEF_FORMAT_IP_POPULAR   "UANStats.${datetime}.${device_id}"
#define DEF_FORMAT_HTTP_STATS   "DASStats.${datetime}.${device_id}"
#define DEF_FORMAT_IP_SLOWFAST   "UASStats.${interval}.${site_id}.${device_id}"
#define DEF_FORMAT_CUTIP_SLOWFAST   "ASStats.${interval}.${site_id}.${device_id}"
#define DEF_FORMAT_IP_SOURCE   	"IPSource.${interval}.${site_id}.${device_id}"

/*parse_option.cpp*/
extern int parse_option(char * in, std::unordered_map<std::string, char *> & out);

nla_options nla_opt = {
		.log_file = "nginx.log",
		.interval = 300,
		.devicelist_file = "devicelist.txt",
		.siteuidlist_file = "siteuidlist.txt",
		.ipmap_file = "iplocation.bin",

		.output_file_flow = NULL,
		.format_flow = DEF_FORMAT_FLOW,
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

		.device_id = 0,
		.print_device_id = 0,
		.enable_multi_thread = 0,
		.parse_url_mode = 2,
		.show_help = 0,
		.show_version = 0,
		.verbose = 0,
};

static poptContext pc = 0;
static struct poptOption nla_popt[] = {
  /* longName, shortName, argInfo, argPtr, value, descrip, argDesc */
	{"log-file",                'l',  POPT_ARG_STRING,   0, 'l', "nginx_log_file default: nginx.log", 0 },
	{"interval",                'i',  POPT_ARG_INT,      0, 'i', "interval in seconds, default: 300", 0 },
	{"device-list-file",        'd',  POPT_ARG_STRING,   0, 'd', "devicelist_file default: devicelist.txt", 0 },
	{"siteuid-list-file",       's',  POPT_ARG_STRING,   0, 's', "siteuidlist_file default: siteuidlist.txt", 0 },
	{"ipmap-file",              'm',  POPT_ARG_STRING,   0, 'm', "ipmap_file default: iplocation.bin", 0 },

	{"output-file-flow",        'o',  POPT_ARG_STRING,   0, 'o', "output folder for flow_table, disabled if NULL", 0 },
	{"format-flow",             'O',  POPT_ARG_STRING,   0, 'O', "filename format for flow_table, default '" DEF_FORMAT_FLOW "', see NOTES for details", 0 },

	{"output-file-url-popular", 'u',  POPT_ARG_STRING,   0, 'u', "output_folder for url_popular table, disabled if NULL", 0 },
	{"format-url-popular",      'U',   POPT_ARG_STRING,   0, 'U', "filename format for url_popular table, default '" DEF_FORMAT_URL_POPULAR "'", 0 },

	{"output-file-ip-popular",  'p',  POPT_ARG_STRING,   0, 'p', "output folder for ip_popular table, disabled if NULL", 0 },
	{"format-ip-popular",       'P',  POPT_ARG_STRING,   0, 'P', "filename format for ip_popular table, default '" DEF_FORMAT_IP_POPULAR "'", 0 },
	{"min-ip-popular",           0,   POPT_ARG_INT,      0, 'Q', "min_access_count, filter for ip_popular table, default 10(>=), disabled if negative", 0 },
	{"max-ip-popular",           0,   POPT_ARG_INT,      0, 'S', "max_access_count, filter for ip_popular table, default unlimited(<=), disabled if negative", 0 },

	{"output-file-http-stats",  't',  POPT_ARG_STRING,   0, 't', "output folder for http_stats table, disabled if NULL", 0 },
	{"format-http-stats",       'T',  POPT_ARG_STRING,   0, 'T', "filename format for http_stats table, default '" DEF_FORMAT_HTTP_STATS "'", 0 },

	{"output-file-ip-slowfast", 'w',  POPT_ARG_STRING,   0, 'w', "output folder for ip_slowfast table, disabled if NULL", 0 },
	{"format-ip-slowfast",      'W',  POPT_ARG_STRING,   0, 'W', "filename format for ip_slowfast table, default '" DEF_FORMAT_IP_SLOWFAST "'", 0 },

	{"output-file-cutip-slowfast"
			                  , 'f',  POPT_ARG_STRING,   0, 'f', "output folder for cutip_slowfast table, disabled if NULL", 0 },
	{"format-cutip-slowfast",   'F',  POPT_ARG_STRING,   0, 'F', "filename format for cutip_slowfast table, default '" DEF_FORMAT_CUTIP_SLOWFAST "'", 0 },

	{"output-file-ip-source",   'r',  POPT_ARG_STRING,   0, 'r', "output folder for ip_source table, disabled if NULL", 0 },
	{"format-ip-source",        'R',   POPT_ARG_STRING,  0, 'R', "filename format for ip_source table, default '" DEF_FORMAT_IP_SOURCE "'", 0 },

	{"device-id",                 0,  POPT_ARG_INT,      0, 'e', "device_id integer(> 0)", 0 },
	{"print-divice-id",         'c',  POPT_ARG_NONE,     0, 'c', "print device_id and exit", 0 },
	{"enable-multi-thread",     0,  POPT_ARG_NONE,       0, 'a', "enable_multi_thread", 0 },
	{"parse-url-mode",          0,    POPT_ARG_INT,      0, 'M', "parse nginx log field '$request_uri' url mode, 0|1|2, default 2", 0 },
	{"help",                    'h',    POPT_ARG_NONE,   0, 'h', "print this help", 0 },
	{"version",                   0,    POPT_ARG_NONE,   0, 'V', "print version info and exit", 0},
	{"verbose",                 'v',  POPT_ARG_NONE,     0, 'v', "verbose, print more details", 0 },
	NULL	/*required!!!*/
};

int nginx_log_stats_parse_options(int argc, char ** argv)
{
	if(pc)
		poptFreeContext(pc);
	pc = poptGetContext("nginx_log_analysis", argc, (const char **)argv, nla_popt, 0);
	for(int opt; (opt = poptGetNextOpt(pc)) != -1; ){
		switch(opt){
		case 'l': nla_opt.log_file = poptGetOptArg(pc); break;
		case 'i': nla_opt.interval = atoi(poptGetOptArg(pc)); break;
		case 'e': nla_opt.device_id = atoi(poptGetOptArg(pc)); break;
		case 'd': nla_opt.devicelist_file = poptGetOptArg(pc); break;
		case 's': nla_opt.siteuidlist_file = poptGetOptArg(pc); break;
		case 'm': nla_opt.ipmap_file = poptGetOptArg(pc); break;

		case 'o': { nla_opt.output_file_flow = poptGetOptArg(pc); } break;
		case 'O': { nla_opt.format_flow = poptGetOptArg(pc); } break;

		case 'u': { nla_opt.output_file_url_popular = poptGetOptArg(pc); }; break;
		case 'U': { nla_opt.format_url_popular = poptGetOptArg(pc); }; break;

		case 'p': { nla_opt.output_file_ip_popular = poptGetOptArg(pc); } break;
		case 'P': { nla_opt.format_ip_popular = poptGetOptArg(pc); } break;
		case 'Q': { nla_opt.min_ip_popular = atoi(poptGetOptArg(pc)); } break;
		case 'S': { nla_opt.max_ip_popular = atoi(poptGetOptArg(pc)); } break;

		case 't': { nla_opt.output_file_http_stats = poptGetOptArg(pc); } break;
		case 'T': { nla_opt.format_http_stats = poptGetOptArg(pc); } break;

		case 'w': { nla_opt.output_file_ip_slowfast = poptGetOptArg(pc); } break;
		case 'W': { nla_opt.format_ip_slowfast = poptGetOptArg(pc); } break;

		case 'f': { nla_opt.output_file_cutip_slowfast = poptGetOptArg(pc); } break;
		case 'F': { nla_opt.format_cutip_slowfast = poptGetOptArg(pc); } break;

		case 'r': { nla_opt.output_file_ip_source = poptGetOptArg(pc); }; break;
		case 'R': { nla_opt.format_ip_source = poptGetOptArg(pc); }; break;

		case 'c': nla_opt.print_device_id = 1; break;
		case 'a': nla_opt.enable_multi_thread = 1; break;
		case 'M': nla_opt.parse_url_mode = atoi(poptGetOptArg(pc)); break;
		case 'h': nla_opt.show_help = 1; break;
		case 'V': nla_opt.show_version = 1; break;
		case 'v': nla_opt.verbose = 1; break;
		default:
			break;
		}
	}
	return nla_options_is_ok(nla_opt)? 0 : -1;
}

int test_nginx_log_analysis_options_main(int argc, char ** argv)
{
	return nginx_log_stats_parse_options(argc, argv);
}

void nginx_log_stats_show_help(FILE * stream)
{
	fprintf(stream, "analysis nginx log file and print results, build at %s %s\n", __DATE__, __TIME__);
	poptPrintHelp(pc, stream, 0);
	fprintf(stream, "NOTES:\n  1.about 'filename format'(option --format-*, e.g. --format-ip-source):\n"
	        "    ${datetime}   current date time, format YYYYmmDDHHMM\n"
			"    ${interval}   according to option --interval, format YYYYmmDDHHMM\n"
			"    ${device_id}  device_id\n"
			"    ${site_id}    site_id/domain id\n"
			"    ${user_id}    user_id\n"
			"  2.use ulimit(or other command) to increase 'open files', or may crash!\n"
	);

}

void nginx_log_stats_show_usage(FILE * stream)
{
	poptPrintUsage(pc, stream, 0);
}

static bool nla_options_is_ok(nla_options const& opt)
{
	/*FIXME: update this function*/
	if(opt.show_help) return true;
	if(opt.show_version) return true;
	if(opt.print_device_id) return true;
	bool result = (opt.log_file && opt.interval > 0
			&& opt.devicelist_file  && opt.siteuidlist_file
			&& (opt.device_id >=  0)
			);
	return result;
}

void nla_options_fprint(FILE * stream, nla_options const * popt)
{
	if(!popt) return;
	auto& opt = *popt;
	fprintf(stream,
			"%-34s%-20s" "\n%-34s%-20d" "\n%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20d\n" "%-34s%-20d\n"
			"%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20s\n" "%-34s%-20s\n"
			"%-34s%-20d\n" "%-34s%-20d\n" "%-34s%-20d\n" "%-34s%-20d\n" "%-34s%-20d\n"
			"%-34s%-20d\n"
		, "log_file", opt.log_file
		, "interval", opt.interval
		, "devicelist_file", opt.devicelist_file
		, "siteuidlist_file", opt.siteuidlist_file
		, "ipmap_file", opt.ipmap_file

		, "output_file_flow", opt.output_file_flow

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

		, "device_id", opt.device_id
		, "print_device_id", opt.print_device_id
		, "parse_url_mode", opt.parse_url_mode
		, "show_help", opt.show_help
		, "show_version", opt.show_version

		, "verbose", opt.verbose
	);
}

