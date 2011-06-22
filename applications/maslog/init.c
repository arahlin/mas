/* -*- mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *      vim: sw=4 ts=4 et tw=80
 */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libconfig.h>
#include <mce_library.h>

#include "init.h"

#define OPT "f:o:F:D:h"
#define USAGE_OPT \
"  -f cfgfile        use alternate configuration file\n" \
"  -o outfile        log to outfile instead of default\n" \
"  -F [0 | 1]        enable/disable flushing after each log\n" \
"  -D [0 | 1]        enable/disable daemon mode\n"

static char *get_config_file(int argc, char **argv)
{
	optind = 0;
	int option;
	while ( (option = getopt(argc, argv, OPT )) >=0) {
		if (option=='f')
			return strdup(optarg);
	}
	return NULL;
}

static int destroy_exit(mce_context_t *mce, int error)
{
    mcelib_destroy(mce);
	return error;
}

static config_setting_t *get_setting(config_setting_t *parent,
			      const char *name)
{
	config_setting_t *set =
		config_setting_get_member(parent, name);
	if (set==NULL) {
		fprintf(stderr, "%s: key '%s' not found in config file\n", __func__,
			name);
		return NULL;
	}
	return set;
}

static int get_integer(int *dest,
		config_setting_t *parent, const char *name)
{
	config_setting_t *set = get_setting(parent,name);
	if (set==NULL) return -1;
	*dest = config_setting_get_int(set);
	return 0;
}

static int get_string(char *dest,
	       config_setting_t *parent, const char *name)
{
	config_setting_t *set = get_setting(parent,name);
	if (set==NULL) return -1;
	strcpy(dest, config_setting_get_string(set));
	return 0;
}

static int load_config(params_t *p, char *config_file)
{
    mce_context_t *mce;
    struct config_t *cfg;

    /* laziness: get libmce to parse the config file.  This magically
     * takes care of figuring out the default mas.cfg if none was specified.
     */

    mce = mcelib_create(-1, config_file);
    if (mce == NULL) {
        fprintf(stderr, "%s: Could not initialise the MCE\n", __func__);
		return -1;
	}
    cfg = mce->mas_cfg;

    config_setting_t *server = config_lookup(cfg, CONFIG_SERVER);
	if (server==NULL) {
		fprintf(stderr, "%s: could not find '%s' section "
				"in config file\n", __func__, CONFIG_SERVER);
        return destroy_exit(mce, -1);
	}

	//Now load the server settings
	if (get_string(p->serve_address, server, CONFIG_LOGADDR)!=0)
        return destroy_exit(mce, -1);

	if (get_string(p->filename, server, CONFIG_LOGFILE)!=0)
        return destroy_exit(mce, -1);

	//Non-fatal
	get_integer(&p->daemon, server, CONFIG_DAEMON);
	get_integer(&p->level, server, CONFIG_LEVEL);


    return destroy_exit(mce, 0);
}


int init(params_t *p, int argc, char **argv)
{
	log_init(p);

	if (check_usage(argc, argv)==0)
		return 1;

	char *config_file;
    config_file = get_config_file(argc, argv);

	if (load_config(p, config_file))
		return 2;

	if (process_options(p, argc, argv)!=0)
		return 3;

    if (massock_listener_init(&p->listener, MAX_CLIENTS, MAX_MSG, MAX_MSG)!=0)
		return 4;

	if (log_openfile(p)) {
		fprintf(stderr, "Failed to open file.\n");
		return 5;
	}

    if (massock_listener_listen(&p->listener, p->serve_address)!=0)
		return 6;

	return 0;
}


int check_usage(int argc, char **argv) {
	optind = 0;
	int option;
	while ( (option = getopt(argc, argv, OPT)) >=0) {

		switch(option) {
			case '?':
			case 'h':
				printf("Usage:\n\t%s [options]\n"
						" Options\n" USAGE_OPT,
						argv[0]);
				return 0;
		}
	}
	return -1;
}

int process_options(params_t *p, int argc, char **argv)
{
	optind = 0;
	int option;
	while ( (option = getopt(argc, argv, OPT)) >=0) {

		switch(option) {
		case '?':

		case 'h':
			printf("Usage:\n\t%s [options]\n"
					" Options\n" USAGE_OPT,
					argv[0]);
			return -1;

		case 'f':
			//Preloaded, ignore.
			break;

		case 'o':
			strcpy(p->filename, optarg);
			break;

		case 'F':
			if (optarg[0]=='0') log_clearflag(p, FLAG_FLUSH);
			else if (optarg[0]=='1') log_setflag(p, FLAG_FLUSH);
			else fprintf(stderr,
					"Invalid -F argument, ignoring.\n");
			break;

		case 'D':
			if (optarg[0]=='0') p->daemon = 0;
			else if (optarg[0]=='1') p->daemon = 1;
			else fprintf(stderr,
					"Invalid -D argument, ignoring.\n");
			break;

		default:
			printf("Unimplemented option '-%c'!\n", option);
		}
	}

	return 0;

}
