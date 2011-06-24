/* -*- mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *      vim: sw=4 ts=4 et tw=80
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mce/defaults.h>

#include "../../defaults/config.h"
#include "options.h"

/*
  This is for MAS configuration file specification, mostly.  Since
  other arguments are processed by the main routines, the function
  must return the offset of the first unprocessed argument.
*/

#define USAGE_MESSAGE "" \
"  Initial options (MAS config):\n" \
"        -n <device index>       override default MCE device\n"\
"        -w <hardware file>      override default hardware configuration file\n"\
"        -m <MAS config file>    override default MAS configuration file\n"\
"        -i                      read psc_status as ascii from stdin (no MCE)\n"\
""

int process_options(option_t *options, int argc, char **argv)
{
    char *s;
    int option;
    // Note the "+" at the beginning of the options string forces the
    // first non-option string to return a -1, which is what we want.
    while ( (option = getopt(argc, argv, "+?hm:n:w:i0123456789")) >=0) {

        switch(option) {
            case '?':
            case 'h':
                printf(USAGE_MESSAGE);
                return -1;

            case 'n':
                options->dev_index = (int)strtol(optarg, &s, 10);
                if (*optarg == '\0' || *s != '\0' || options->dev_index < 0) {
                    fprintf(stderr, "%s: invalid fibre card number\n", argv[0]);
                    return -1;
                }
                break;

            case 'm':
                if (options->config_file)
                    free(options->config_file);
                options->config_file = strdup(optarg);
                break;

            case 'w':
                if (options->hardware_file)
                    free(options->hardware_file);
                options->hardware_file = strdup(optarg);
                break;

            case 'i':
                options->read_stdin = 1;
                break;

            case '0' ... '9':
                //It's a number! Get out of here!
                optind--;
                break;

            default:
                printf("Unimplemented option '-%c'!\n", option);
        }
    }

    return optind;
}
