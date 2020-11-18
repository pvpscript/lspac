#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "args.h"

int parse_args(int argc, char **argv)
{
	static struct option long_options[] = {
                {"delim",       required_argument,      NULL,   'd'},
                {"output",      required_argument,      NULL,   'o'},
                {"bytes",       no_argument,            NULL,   'b'},
                {"escape",      no_argument,            NULL,   'e'},
                {"pairs",       no_argument,            NULL,   'p'},
                {"version",     no_argument,            NULL,   'v'},
                {"unix",        no_argument,            NULL,   'u'},
        };

        int opt_index = 0;
        char c;
        while ((c = getopt_long(argc, argv, "d:o:bepvu", long_options, &opt_index)) != -1) {
                switch(c) {
                        case 'd':
                                printf("delim: %s\n", optarg);
                                break;
                        case 'o':
                                printf("output: %s\n", optarg);
                                break;
                        case 'b':
                                printf("bytes\n");
                                break;
                        case 'e':
                                printf("escape\n");
                                break;
                        case 'p':
                                printf("pairs\n");
                                break;
                        case 'v':
                                printf("verbose\n");
                                break;
                        case 'u':
                                printf("unix\n");
                                break;
                        case '?':
                                printf("question mark, smiley face\n");
                                break;
                        default:
                                printf("default\n");
                }
        }

        return 0;
}
