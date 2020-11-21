#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <getopt.h>

#include "container.h"
#include "op.h"
#include "args.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


enum {
        OUT_NAME = 0,
	OUT_DBNAME,
	OUT_BASENAME,
        OUT_FILENAME,
        OUT_VERSION,
        OUT_DESC,
        OUT_ARCH,
        OUT_URL,
        OUT_PACKAGER,
        OUT_SIZE,
        OUT_BUILDDATE,
        OUT_INSTALLDATE,
        OUT_SCRIPTLET,
        OUT_VALIDATION,
        OUT_REASON,
        OUT_LICENSES,
        OUT_GROUPS,
        OUT_PROVIDES,
        OUT_DEPENDS,
        OUT_OPTDEPENDS,
        OUT_CONFLICTS,
        OUT_REPLACES,
        OUT_CHECKDEPENDS,
        OUT_MAKEDEPENDS,
};

struct outinfo {
	char *name;
	struct container *(*get_values)(void *, char *);
};

static struct outinfo infos[] = {
	/* single value */
        [OUT_NAME] 		= { "NAME", &lspac_pkg_get_name },
	[OUT_DBNAME] 		= { "DBNAME", &lspac_db_get_name },
	[OUT_BASENAME]		= { "BASENAME", &lspac_pkg_get_base },
        [OUT_FILENAME] 		= { "FILENAME", &lspac_pkg_get_filename },
	[OUT_VERSION]		= { "VERSION", &lspac_pkg_get_version },
        [OUT_DESC] 		= { "DESC", &lspac_pkg_get_desc },
        [OUT_ARCH] 		= { "ARCH", &lspac_pkg_get_arch },
        [OUT_URL] 		= { "URL", &lspac_pkg_get_url },
        [OUT_PACKAGER] 		= { "PACKAGER", &lspac_pkg_get_packager },
        [OUT_SIZE] 		= { "SIZE", &lspac_pkg_get_isize },
        [OUT_BUILDDATE] 	= { "BUILDDATE", &lspac_pkg_get_builddate },
        [OUT_INSTALLDATE] 	= { "INSTALLDATE", &lspac_pkg_get_installdate },
        [OUT_SCRIPTLET] 	= { "SCRIPTLET", &lspac_pkg_has_scriptlet },
        [OUT_VALIDATION] 	= { "VALIDATION", &lspac_pkg_get_validation },
        [OUT_REASON] 		= { "REASON", &lspac_pkg_get_reason },

	/* might have multiple values */
        [OUT_LICENSES] 		= { "LICENSES", &lspac_pkg_get_licenses },
        [OUT_GROUPS] 		= { "GROUPS", &lspac_pkg_get_groups },
        [OUT_PROVIDES] 		= { "PROVIDES", &lspac_pkg_get_provides },
        [OUT_DEPENDS] 		= { "DEPENDS", &lspac_pkg_get_depends },
        [OUT_OPTDEPENDS] 	= { "OPTDEPENDS", &lspac_pkg_get_optdepends },
        [OUT_CONFLICTS] 	= { "CONFLICTS", &lspac_pkg_get_conflicts },
        [OUT_REPLACES] 		= { "REPLACES", &lspac_pkg_get_replaces },
        [OUT_CHECKDEPENDS]	= { "CHECKDEPENDS", &lspac_pkg_get_checkdepends },
        [OUT_MAKEDEPENDS] 	= { "MAKEDEPENDS", &lspac_pkg_get_makedepends },
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
