#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <getopt.h>

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

static char *out_names[] = {
	[OUT_DBNAME] = "DBNAME",
        [OUT_NAME] = "NAME",
        [OUT_FILENAME] = "FILENAME",
        [OUT_DESC] = "DESC",
        [OUT_ARCH] = "ARCH",
        [OUT_URL] = "URL",
        [OUT_PACKAGER] = "PACKAGER",
        [OUT_LICENSES] = "LICENSES",
        [OUT_GROUPS] = "GROUPS",
        [OUT_PROVIDES] = "PROVIDES",
        [OUT_DEPENDS] = "DEPENDS",
        [OUT_OPTDEPENDS] = "OPTDEPENDS",
        [OUT_CONFLICTS] = "CONFLICTS",
        [OUT_REPLACES] = "REPLACES",
        [OUT_CHECKDEPENDS] = "CHECKDEPENDS",
        [OUT_MAKEDEPENDS] = "MAKEDEPENDS",
        [OUT_SIZE] = "SIZE",
        [OUT_BUILDDATE] = "BUILDDATE",
        [OUT_INSTALLDATE] = "INSTALLDATE",
        [OUT_SCRIPTLET] = "SCRIPTLET",
        [OUT_VALIDATION] = "VALIDATION",
        [OUT_REASON] = "REASON",
        [OUT_VERSION] = "VERSION"
};

static int outputs[ARRAY_SIZE(out_names) * 2];
static size_t noutputs;

static void add_output(int id)
{
	if (noutputs >= ARRAY_SIZE(outputs)) {
		fprintf(stderr, "too many outputs defined, "
				"the limit is %lu values",
				ARRAY_SIZE(outputs) - 1);
		exit(EXIT_FAILURE);
	}

	outputs[noutputs++] = id;
}

static int column_name_to_id(const char *name, size_t namesz)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(out_names); i++)
		if (!strncasecmp(name, out_names[i], namesz) &&
		    !*(out_names[i] + namesz))
			return i;

	fprintf(stderr, "unknown output: %s", name);
	return -1;
}

static int output_id_to_number(int id)
{
	size_t i;

	for (i = 0; i < noutputs; i++)
		if (outputs[i] == id)
			return i;

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
