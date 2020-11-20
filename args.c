#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <getopt.h>
#include <alpm.h>

#include "args.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

enum {
	OUT_DBNAME = 0,
        OUT_NAME,
        OUT_FILENAME,
        OUT_DESC,
        OUT_ARCH,
        OUT_URL,
        OUT_PACKAGER,
        OUT_LICENSES,
        OUT_GROUPS,
        OUT_PROVIDES,
        OUT_DEPENDS,
        OUT_OPTDEPENDS,
        OUT_CONFLICTS,
        OUT_REPLACES,
        OUT_CHECKDEPENDS,
        OUT_MAKEDEPENDS,
        OUT_SIZE,
        OUT_BUILDDATE,
        OUT_INSTALLDATE,
        OUT_SCRIPTLET,
        OUT_VALIDATION,
        OUT_REASON,
        OUT_VERSION
};

struct outinfo {
	char *name;
	void (*get_values)(const void *pkg);
};

static struct outinfo infos[] = {
	[OUT_DBNAME] 		= { "DBNAME", NULL },
        [OUT_NAME] 		= { "NAME", NULL },
        [OUT_FILENAME] 		= { "FILENAME", NULL },
        [OUT_DESC] 		= { "DESC", NULL },
        [OUT_ARCH] 		= { "ARCH", NULL },
        [OUT_URL] 		= { "URL", NULL },
        [OUT_PACKAGER] 		= { "PACKAGER", NULL },
        [OUT_LICENSES] 		= { "LICENSES", NULL },
        [OUT_GROUPS] 		= { "GROUPS", NULL },
        [OUT_PROVIDES] 		= { "PROVIDES", NULL },
        [OUT_DEPENDS] 		= { "DEPENDS", NULL },
        [OUT_OPTDEPENDS] 	= { "OPTDEPENDS", NULL },
        [OUT_CONFLICTS] 	= { "CONFLICTS", NULL },
        [OUT_REPLACES] 		= { "REPLACES", NULL },
        [OUT_CHECKDEPENDS]	= { "CHECKDEPENDS", NULL },
        [OUT_MAKEDEPENDS] 	= { "MAKEDEPENDS", NULL },
        [OUT_SIZE] 		= { "SIZE", NULL },
        [OUT_BUILDDATE] 	= { "BUILDDATE", NULL },
        [OUT_INSTALLDATE] 	= { "INSTALLDATE", NULL },
        [OUT_SCRIPTLET] 	= { "SCRIPTLET", NULL },
        [OUT_VALIDATION] 	= { "VALIDATION", NULL },
        [OUT_REASON] 		= { "REASON", NULL },
        [OUT_VERSION] 		= { "VERSION", NULL },
};

static int outputs[ARRAY_SIZE(infos) * 2];
static size_t noutputs;

static inline void add_output(int id)
{
	if (noutputs >= ARRAY_SIZE(outputs)) {
		fprintf(stderr, "too many outputs defined, "
				"the limit is %lu values",
				ARRAY_SIZE(outputs) - 1);
		exit(EXIT_FAILURE);
	}

	outputs[noutputs++] = id;
}

static int output_id_to_number(int id)
{
	size_t i;

	for (i = 0; i < noutputs; i++)
		if (outputs[i] == id)
			return i;

	return -1;
}

static inline void add_uniq_output(int id)
{
	if (output_id_to_number(id) < 0)
		add_output(id);
}

static int output_name_to_id(const char *name, size_t namesz)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(infos); i++)
		if (!strncasecmp(name, infos[i].name, namesz) &&
		    !*(infos[i].name + namesz))
			return i;

	fprintf(stderr, "unknown output: %s", name);
	return -1;
}

int parse_args(int argc, char **argv)
{
	struct options *opts;
	int output_mask;
	int i;
        char c;
        int opt_index = 0;
	static struct option long_options[] = {
                {"delim",       required_argument,      NULL,   'd'},
                {"output",      required_argument,      NULL,   'o'},
                {"bytes",       no_argument,            NULL,   'b'},
                {"escape",      no_argument,            NULL,   'e'},
                {"pairs",       no_argument,            NULL,   'p'},
                {"version",     no_argument,            NULL,   'v'},
                {"unix",        no_argument,            NULL,   'u'},
		{"show-null",	no_argument,		NULL,	's'},
        };


        while ((c = getopt_long(argc, argv, "d:o:bepsuv", long_options, &opt_index)) != -1) {
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
			case 's':
				printf("When the output is blank, it shows NULL instead of showing nothing.\n");
				output_mask = -1;
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
