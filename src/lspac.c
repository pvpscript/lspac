#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <getopt.h>
#include <alpm.h>

#include "../include/strutils.h"
#include "../include/container.h"
#include "../include/containerutils.h"
#include "../include/op.h"

#define DEFAULT_DELIM 32 /* space */
#define DEFAULT_SURROUND 34 /* double quotes */

#define FOREACH_STR_DESTRUCTIVE(str, index, arr) \
	for ((index) = 0; (arr) && ((str) = ((arr)[(index)])); \
	     free((str)), (index)++)

#define FOREACH_STR(str, index, arr) \
	for ((index) = 0; (arr) && ((str) = ((arr)[(index)])); (index)++)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


struct config {
	char delim;
	char surround;

	/* alpm initialization settings */
	char *root;
	char *dbpath;

	/* if extra options are added, replace this with a bitmask */
	int pairs; 

	unsigned bitmask;
};

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
	char *desc;
	struct container *(*get_values)(void *, char *);
};

static struct outinfo infos[] = {
	/* returns single value */
        [OUT_NAME] 		= { "NAME", "Package name", &lspac_pkg_get_name },
	[OUT_DBNAME] 		= { "DBNAME", "Database name", &lspac_db_get_name },
	[OUT_BASENAME]		= { "BASENAME", "Package base name", &lspac_pkg_get_base },
        [OUT_FILENAME] 		= { "FILENAME", "Name of the file which the package was loaded", &lspac_pkg_get_filename },
	[OUT_VERSION]		= { "VERSION", "Package version", &lspac_pkg_get_version },
        [OUT_DESC] 		= { "DESC", "Package description", &lspac_pkg_get_desc },
        [OUT_ARCH] 		= { "ARCH", "Package architecture", &lspac_pkg_get_arch },
        [OUT_URL] 		= { "URL", "Package URL", &lspac_pkg_get_url },
        [OUT_PACKAGER] 		= { "PACKAGER", "Name of the packager", &lspac_pkg_get_packager },
        [OUT_SIZE] 		= { "SIZE", "Size of the installed package", &lspac_pkg_get_isize },
        [OUT_BUILDDATE] 	= { "BUILDDATE", "Package's build timestamp", &lspac_pkg_get_builddate },
        [OUT_INSTALLDATE] 	= { "INSTALLDATE", "Package's install date", &lspac_pkg_get_installdate },
        [OUT_SCRIPTLET] 	= { "SCRIPTLET", "Shows if the package has a install script", &lspac_pkg_has_scriptlet },
        [OUT_VALIDATION] 	= { "VALIDATION", "Package's validation method", &lspac_pkg_get_validation },
        [OUT_REASON] 		= { "REASON", "Package's install reason", &lspac_pkg_get_reason },

	/* might return multiple values */
        [OUT_LICENSES] 		= { "LICENSES", "Package's licenses", &lspac_pkg_get_licenses },
        [OUT_GROUPS] 		= { "GROUPS", "Package's groups", &lspac_pkg_get_groups },
        [OUT_PROVIDES] 		= { "PROVIDES", "Secondary packages provided by given package", &lspac_pkg_get_provides },
        [OUT_DEPENDS] 		= { "DEPENDS", "Package's dependencies", &lspac_pkg_get_depends },
        [OUT_OPTDEPENDS] 	= { "OPTDEPENDS", "Package's optional dependencies", &lspac_pkg_get_optdepends },
        [OUT_CONFLICTS] 	= { "CONFLICTS", "Package's conflicts", &lspac_pkg_get_conflicts },
        [OUT_REPLACES] 		= { "REPLACES", "Packages replaces by given package", &lspac_pkg_get_replaces },
        [OUT_CHECKDEPENDS]	= { "CHECKDEPENDS", "Package's check dependencies", &lspac_pkg_get_checkdepends },
        [OUT_MAKEDEPENDS] 	= { "MAKEDEPENDS", "Package's make dependencies", &lspac_pkg_get_makedepends },
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

	fprintf(stderr, "unknown output: %s\n", name);
	return -1;
}

static void print_lspac(struct container *c, struct config cfg)
{
	char *str;
	size_t i;

	printf("\n%s\n", get_container_prefix(c));
	FOREACH_STR_DESTRUCTIVE(str, i, get_container_arr(c))
		printf("%s\n", str);
	destroy_container(c);
}

static size_t readlen(const char *str)
{
	size_t len = strlen(str);
	const char *ptr;
	char c;

	for (c = 1; c < 32 && len; c++)
		for (ptr = str; (ptr = strchr(str + (str - ptr), c));
				ptr++, len--)
			;

	return len;
}

static void fmt_help(const char *cmd, const char *desc)
{
	size_t cmdsz = readlen(cmd);
	int spacing = 20 - cmdsz;

	fprintf(stdout, "%s%*s%s\n", cmd, spacing, "", desc);
}

static void usage()
{
	size_t i;

	puts("Usage:");
	puts(" lspac [options] [<package> ...]");

	puts("\nList information about pacman packages");

	puts("\nOptions:");
	fmt_help(" -d, --dbpath", "database path");
	fmt_help(" -o, --output", "output fields");
	fmt_help(" -r, --root", "installation root");
	fmt_help(" -D, --delim", "set field delimiter (default: tab)");
	fmt_help(" -b, --bytes", "display size as bytes instead of human readable");
	fmt_help(" -p, --pairs", "show outputs in a KEY=\"VALUE\" fashion");
	fmt_help(" -u, --unix", "display dates as unix timestamp instead of human readable");
	fmt_help(" -s, --show-null", "when the output is blank, it shows NULL instead of showing nothing");
	fmt_help(" -B, --basic", "show basic informations about a package");
	fmt_help(" -R, --relations", "show the relations of a given package");

	fmt_help("\n -h, --help", "displays this help");

	puts("\nAvailable output columns:");

	for (i = 0; i < ARRAY_SIZE(infos); i++)
		printf(" %14s %s\n", infos[i].name, infos[i].desc);
}

int main(int argc, char **argv)
{
	struct config cfg = {
		.delim = DEFAULT_DELIM,
		.surround = DEFAULT_SURROUND,
		.pairs = 0,
		.bitmask = 0,
		.root = "/",
		.dbpath = "/var/lib/pacman/"
	};
	char *outarg = NULL;

	alpm_handle_t *handle;
	alpm_db_t *db;
	alpm_pkg_t *pkg;
	alpm_list_t *pkg_list = NULL;

	struct container *con;

        char c;
        int opt_index = 0;
        static struct option long_options[] = {
		{"dbpath",	required_argument,	NULL,	'd'},
                {"output",      required_argument,      NULL,   'o'},
		{"root",	required_argument,	NULL,	'r'},
                {"delim",       required_argument,      NULL,   'D'},
		{"output-all",	no_argument,		NULL,	'O'},
                {"bytes",       no_argument,            NULL,   'b'},
                {"escape",      no_argument,            NULL,   'e'},
		{"help",	no_argument,		NULL,	'h'},
                {"pairs",       no_argument,            NULL,   'p'},
                {"unix",        no_argument,            NULL,   'u'},
		{"basic",	no_argument,		NULL,	'B'},
		{"relations", 	no_argument,		NULL,	'R'}
        };

	/*
	 * raw: don't put any surrounding and makes space the default delimiter
	 * local-only: fetch packages only from the localdb;
	 * sync-only: fetch packages only from the syncdb;
	 * dbext: add extra sync db extensions;
	 */

        while ((c = getopt_long(argc, argv, "d:o:r:D:bepsuBROh", long_options,
				&opt_index)) != -1) {
                switch(c) {
		case 'd':
			puts(optarg);
			cfg.dbpath = optarg;
			break;
		case 'o':
			outarg = optarg;
			printf("output: %s\n", optarg);
			break;
		case 'r':
			puts(optarg);
			cfg.root = optarg;
			break;
		case 'D':
			if (strlen(optarg) > 1) {
				fprintf(stderr, "\nDelimiter must be a single character\n");
				exit(EXIT_FAILURE);
			}

			cfg.delim = *optarg;
			break;
		case 'O':
			for (noutputs = 0; noutputs < ARRAY_SIZE(infos); noutputs++)
				outputs[noutputs] = noutputs;
			break;
		case 'b':
			cfg.bitmask |= OPT_BYTES;
			break;
		case 'e':
			printf("escape\n"); /* might not be necessary */
			break;
		case 'p':
			cfg.pairs = 1;
			break;
		case 'u':
			cfg.bitmask |= OPT_UNIX;
			break;
		case 'B':
			add_uniq_output(OUT_PROVIDES);
			add_uniq_output(OUT_DEPENDS);
			add_uniq_output(OUT_CONFLICTS);
			add_uniq_output(OUT_REPLACES);
			add_uniq_output(OUT_CHECKDEPENDS);
			add_uniq_output(OUT_MAKEDEPENDS);

			break;
		case 'R':
			add_uniq_output(OUT_DBNAME);
			add_uniq_output(OUT_BASENAME);
			add_uniq_output(OUT_VERSION);
			add_uniq_output(OUT_DESC);
			add_uniq_output(OUT_ARCH);
			add_uniq_output(OUT_URL);
			add_uniq_output(OUT_PACKAGER);
			add_uniq_output(OUT_SIZE);
			add_uniq_output(OUT_BUILDDATE);
			add_uniq_output(OUT_INSTALLDATE);
			break;
		case 'h':
			usage();
			break;
		case '?':
			printf("question mark, smiley face\n");
			break;
		default:
			printf("default\n");
                }
        }

	handle = alpm_initialize(cfg.root, cfg.dbpath, NULL);
	db = alpm_get_localdb(handle); /* only works with local db for now */

        if (!noutputs) {
                add_uniq_output(OUT_DBNAME);
                add_uniq_output(OUT_BASENAME);
                add_uniq_output(OUT_VERSION);
        }

	if (outarg && add_out_to_idarray(outarg, outputs, ARRAY_SIZE(outputs),
					 &noutputs, output_name_to_id) < 0)
		exit(EXIT_FAILURE);

	if (optind == argc) {
		fprintf(stderr, "Must provide at least one package name\n");
		exit(EXIT_FAILURE);
	} else if (argc > optind) {
		// one or more packages given
		for (; optind < argc; optind++) {
			pkg = alpm_db_get_pkg(db, argv[optind]);
			pkg_list = alpm_list_add(pkg_list, pkg);
		}
		// make alpmutils to handle packages not found and put a meta loop for the alpm_list
	}

	printf("optind:%d -> argc:%d\n", optind, argc);

	for (size_t i = 0; i < noutputs; i++) {
		con = infos[outputs[i]].get_values(
				pkg, infos[outputs[i]].name);
		print_lspac(con, cfg);
	}

		//printf("%d\n", outputs[i]);
		

	alpm_release(handle);
	alpm_list_free(pkg_list);

	return 0;
}
