/* Command description file - libconfig syntax */

        {
            name = "ret_dat command";

            parameters = (
                {
                    name = "ret_dat";
                    id = 0x16;
                    type = "cmd";
                }
            );
        }, // ret_dat command

        {
            name = "readout-all commands";

            parameters = (
                {
                    name = "sa_bias";
                    id = 0x10;
                    count = 8;
                    default_set = 0;
                },

                {
                    name = "offset";
                    id = 0x11;
                    count = 8;
                    default_set = 0;
                },

                {
                    name = "fltr_rst";
                    id = 0x14;
                    write_only = 1;
                },

                {
                    name = "en_fb_jump";
                    id = 0x15;
                    default_set = 1;
                },

                {
                    name = "data_mode";
                    id = 0x17;
                    default_set = 0;
                },

                {
                    name = "captr_raw";
                    id = 0x18;
                    default_set = 0;
                    write_only = 1;
                },
/*
                {
                    name = "filt_coef";
                    id = 0x1A;
                    count = 7;
                    default_items = ( 0, 0, 0, 0, 0, 0, 0 );
                },
*/
                {
                    name = "servo_mode";
                    id = 0x1B;
                    count = 8;
                    default_set = 0;
                },

                {
                    name = "ramp_dly";
                    id = 0x1C;
                    default_set = 5;
                },

                {
                    name = "ramp_amp";
                    id = 0x1D;
                    default_set = 8192;
                },

                {
                    name = "ramp_step";
                    id = 0x1E;
                    default_set = 1;
                },

                {
                    name = "fb_const";
                    id = 0x1F;
                    count = 8;
                    default_set = 8192;
                },

                {
                    name = "sample_dly";
                    id = 0x32;
                    default_set = 16;
                },

                {
                    name = "sample_num";
                    id = 0x33;
                    default_set = 40;
                },

                {
                    name = "fb_dly";
                    id = 0x34;
                    default_set = 3;
                },

                {
                    name = "flx_lp_init";
                    id = 0x37;
                    write_only = 1;
                },

                {
                    name = "readout_row_index";
                    id = 0x13;
                }
            );
        }, // readout-all commands

        {
            name = "readout commands";

            parameters = (
                { name = "gainp0"; id = 0x70; count = 41; },
                { name = "gainp1"; id = 0x71; count = 41; },
                { name = "gainp2"; id = 0x72; count = 41; },
                { name = "gainp3"; id = 0x73; count = 41; },
                { name = "gainp4"; id = 0x74; count = 41; },
                { name = "gainp5"; id = 0x75; count = 41; },
                { name = "gainp6"; id = 0x76; count = 41; },
                { name = "gainp7"; id = 0x77; count = 41; },

                { name = "gaini0"; id = 0x78; count = 41; },
                { name = "gaini1"; id = 0x79; count = 41; },
                { name = "gaini2"; id = 0x7A; count = 41; },
                { name = "gaini3"; id = 0x7B; count = 41; },
                { name = "gaini4"; id = 0x7C; count = 41; },
                { name = "gaini5"; id = 0x7D; count = 41; },
                { name = "gaini6"; id = 0x7E; count = 41; },
                { name = "gaini7"; id = 0x7F; count = 41; },

                { name = "flx_quanta0"; id = 0x80; count = 41; },
                { name = "flx_quanta1"; id = 0x81; count = 41; },
                { name = "flx_quanta2"; id = 0x82; count = 41; },
                { name = "flx_quanta3"; id = 0x83; count = 41; },
                { name = "flx_quanta4"; id = 0x84; count = 41; },
                { name = "flx_quanta5"; id = 0x85; count = 41; },
                { name = "flx_quanta6"; id = 0x86; count = 41; },
                { name = "flx_quanta7"; id = 0x87; count = 41; },

                { name = "gaind0"; id = 0x88; count = 41; },
                { name = "gaind1"; id = 0x89; count = 41; },
                { name = "gaind2"; id = 0x8A; count = 41; },
                { name = "gaind3"; id = 0x8B; count = 41; },
                { name = "gaind4"; id = 0x8C; count = 41; },
                { name = "gaind5"; id = 0x8D; count = 41; },
                { name = "gaind6"; id = 0x8E; count = 41; },
                { name = "gaind7"; id = 0x8F; count = 41; },

                { name = "adc_offset0"; id = 0x68; count = 41; },
                { name = "adc_offset1"; id = 0x69; count = 41; },
                { name = "adc_offset2"; id = 0x6A; count = 41; },
                { name = "adc_offset3"; id = 0x6B; count = 41; },
                { name = "adc_offset4"; id = 0x6C; count = 41; },
                { name = "adc_offset5"; id = 0x6D; count = 41; },
                { name = "adc_offset6"; id = 0x6E; count = 41; },
                { name = "adc_offset7"; id = 0x6F; count = 41; }

            );

        }, // readout commands
