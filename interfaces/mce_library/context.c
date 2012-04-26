/* -*- mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *      vim: sw=4 ts=4 et tw=80
 */
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <mce/defaults.h>

#include "context.h"
#include "version.h"
#include "../defaults/config.h"

/* Retreive a directory named "name" from mas.cfg, or use default "def" if not
 * found */
static char *get_default_dir(config_setting_t *masconfig, const char *name,
        const char *def)
{
    config_setting_t *config_item;
    
    if (masconfig == NULL)
        return strdup(def);

    if ((config_item = config_setting_get_member(masconfig, name)) == NULL
            || (config_setting_type(config_item) != CONFIG_TYPE_STRING))
    {
        if (def == NULL)
            return NULL;
        return strdup(def);
    }
    return strdup(config_setting_get_string(config_item));
}

mce_context_t* mcelib_create(int fibre_card, const char *mas_config)
{
    char *mas_cfg;
    config_setting_t *masconfig;
    config_setting_t *config_item = NULL;

    mce_context_t* c = (mce_context_t*)malloc(sizeof(mce_context_t));

    if (c == NULL)
        return NULL;

    memset(c, 0, sizeof(mce_context_t));
    if (fibre_card == MCE_DEFAULT_MCE)
        c->fibre_card = mcelib_default_mce();
    else
        c->fibre_card = fibre_card;


    /* load mas.cfg */
    if (mas_config)
        mas_cfg = strdup(mas_config);
    else {
        mas_cfg = mcelib_default_masfile();
        if (mas_cfg == NULL) {
            fprintf(stderr,
                    "mcelib: Unable to obtain path to default MAS config!\n");
            free(c);
            return NULL;
        }
    }

    c->mas_cfg = (struct config_t *)malloc(sizeof(struct config_t));
    config_init(c->mas_cfg);

    /* read mas.cfg */
    if (!config_read_file(c->mas_cfg, mas_cfg)) {
        fprintf(stderr, "mcelib: Could not read config file '%s':\n"
                "   %s on line %i\n", mas_cfg, config_error_text(c->mas_cfg),
                config_error_line(c->mas_cfg));
        mcelib_destroy(c);
        return NULL;
    }

    /* load default paths */
    masconfig = config_lookup(c->mas_cfg, "mas");
    if (masconfig == NULL)
        fprintf(stderr, "mcelib: Warning: Missing required section `mas' in "
                "MAS configuration.\n"
                "mcelib: Warning: Using configuration defaults.\n");
    else
        c->etc_dir = get_default_dir(masconfig, "etcdir", NULL);
    /* etc dir (the location of mce*.cfg) */
    if (c->etc_dir == NULL) {
        /* if etcdir is not specified, MAS assumes the hardware config files
         * are in the same directory as the mas.cfg that we've just read. */

        /* (dirname may modify it's input) */
        char *temp = strdup(mas_cfg);
        c->etc_dir = strdup(dirname(temp));
        free(temp);

        /* absolutify, if necessary */
        if (c->etc_dir[0] != '/') {
            char *realpath = c->etc_dir;
            char *cwd = getcwd(NULL, 0);
            c->etc_dir = realloc(cwd, strlen(cwd) + strlen(realpath) + 2);
            strcat(strcat(c->etc_dir, "/"), realpath);
            free(realpath);
        }
    }

    /* data root */
    if (c->fibre_card == MCE_NULL_MCE)
        c->data_root = NULL;
    else if (masconfig == NULL || (config_item =
                config_setting_get_member(masconfig, "dataroot")) == NULL ||
            (config_setting_type(config_item) != CONFIG_TYPE_ARRAY) ||
            config_setting_type(config_setting_get_elem(config_item, 0)) !=
            CONFIG_TYPE_STRING)
    {
        c->data_root = malloc(20);
#if MULTICARD
        sprintf(c->data_root, "/data/mce%i", c->fibre_card);
#else
        strcpy(c->data_root, "/data/cryo");
#endif
    } else
        c->data_root = strdup(config_setting_get_string_elem(config_item,
                    c->fibre_card));

    /* other dirs */
    c->temp_dir =  get_default_dir(masconfig, "tmpdir", "/tmp");
    c->data_subdir = get_default_dir(masconfig, "datadir", "current_data");
    c->mas_root = get_default_dir(masconfig, "masroot",
            MAS_PREFIX "/mce_script");
    free(mas_cfg);

    return c;
}


void mcelib_destroy(mce_context_t* context)
{
    if (context==NULL)
        return;

    mceconfig_close(context);
    mcedata_close(context);
    mcecmd_close(context);

    maslog_close(context->maslog);
    config_destroy(context->mas_cfg);
    free(context->mas_cfg);

    free(context->etc_dir);
    free(context->data_dir);
    free(context->data_subdir);
    free(context->data_root);
    free(context->mas_root);
    free(context->idl_dir);
    free(context->python_dir);
    free(context->script_dir);
    free(context->template_dir);
    free(context->temp_dir);
    free(context->test_dir);

    free(context);
}


char* mcelib_version()
{
    return VERSION_STRING;
}
