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

#define DEFAULT_DELIM_INNER 32 /* space */
#define DEFAULT_DELIM_PKG 10 /* new line */
#define DEFAULT_DELIM_FIELD 9 /* tab */
#define DEFAULT_SURROUND 34 /* double quotes */

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


/* so much very scalable!!1!eleven */
enum {
	OPT_PAIRS 	= (1 << 0),
	OPT_LOCAL 	= (1 << 1),
	OPT_SYNC 	= (1 << 2),
        OPT_TARBALL     = (1 << 3)
};

struct config {
	char delim_inner;
	char delim_field;
	char delim_pkg;
	char surround;

	/* alpm initialization settings */
	char *root;
	char *dbpath;

        /* pacman config file */
        char *pacman_conf;

	/* output option */
	unsigned mask_output; 

	/* inner options */
	unsigned mask_con;
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
	char **arr = get_container_arr(c);
	char *str;

	if (cfg.mask_output & OPT_PAIRS)
		printf("%s=%c", get_container_prefix(c), cfg.surround);
	else
		printf("%c", cfg.surround);
	if (arr) {
		printf("%s", *arr);
		free(*(arr++));

		FOREACH_STR_DESTRUCTIVE(str, arr)
			printf("%c%s", cfg.delim_inner, str);
	}
	printf("%c", cfg.surround);

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

static void set_single_character(char *optarg, char *field_ref)
{
	if (strlen(optarg) > 1) {
		fprintf(stderr, "error: delimiter must be a single character\n");
		exit(EXIT_FAILURE);
	}

	*field_ref = *optarg;
}

static void usage()
{
	size_t i;

	puts("Usage:");
	puts(" lspac [options] [<package> ...]");

	puts("\nList information about pacman packages");

	puts("\nOptions:");
        fmt_help(" -c, --pacman-conf", "set the pacman config file");
	fmt_help(" -d, --dbpath", "database path (default: '/var/lib/pacman/')");
	fmt_help(" -r, --root", "filesystem root (default: '/')");
	fmt_help(" -f, --field-delim", "set the field delimiter (default: tab)");
	fmt_help(" -i, --inner-delim", "set the inner values delimiter (default: space)");
        fmt_help(" -p, --pkg-delim", "set the delimiter used between packages (default: newline)");
	fmt_help(" -o, --output", "output fields");
	fmt_help(" -s, --surround", "character used to surround each output (default: double quotes)");
        fmt_help(" -t, --tarball", "fetches data from a given package tarball");
        fmt_help(" -S, --select-db", "select between local db and sync dbs (default: both)");
	fmt_help(" -b, --bytes", "display size as bytes, instead of human readable");
	fmt_help(" -P, --pairs", "show outputs in a KEY=\"VALUE\" fashion");
	fmt_help(" -u, --unix", "display dates as unix timestamp, instead of human readable");
	fmt_help(" -w, --raw", "remove surrounding character (overwrites -s)");
	fmt_help(" -B, --basic", "show basic informations about a package");
	fmt_help(" -R, --relations", "show the relations of a given package");
	fmt_help(" -O, --output-all", "shows every single available output");

	fmt_help("\n -h, --help", "displays this help");
	fmt_help(" -v, --version", "display version");

	puts("\nAvailable output values:");

	for (i = 0; i < ARRAY_SIZE(infos); i++)
		printf(" %14s %s\n", infos[i].name, infos[i].desc);

	exit(EXIT_SUCCESS);
}

void register_sync_dbs(alpm_handle_t *handle, struct config cfg)
{
        FILE *f = fopen(cfg.pacman_conf, "r");
        char buf[255];
        size_t namesz;

        if (f == NULL) {
                fprintf(stderr, "error: pacman config file '%s' not found\n",
                                cfg.pacman_conf);
                exit(EXIT_FAILURE);
        }

        while (fgets(buf, 255, f)) {
                if (*buf == '[' && strncmp(buf, "[options]", 9)) {
                        namesz = strlen(buf);
                        buf[namesz - 2] = 0;

                        alpm_register_syncdb(handle, buf + 1, 0);
                }
        }

        fclose(f);
}

/*
 * Just to get rid of the warning
 */
void (*alpm_pkg_free_closure(int (*fn)(alpm_pkg_t *)))(void *)
{
        return ((void (*)(void *))fn);
}

int main(int argc, char **argv)
{
	struct config cfg = {
		.delim_inner = DEFAULT_DELIM_INNER,
		.delim_field = DEFAULT_DELIM_FIELD,
		.delim_pkg = DEFAULT_DELIM_PKG,
		.surround = DEFAULT_SURROUND,
		.mask_output = OPT_LOCAL | OPT_SYNC,
		.mask_con = 0,
		.root = "/",
		.dbpath = "/var/lib/pacman/",
                .pacman_conf = "/etc/pacman.conf"
	};
	char *outarg = NULL;
        char *pkg_name = NULL;

	alpm_handle_t *handle;
	alpm_list_t *dbs = NULL;
	alpm_list_t *pkg_list = NULL;
        alpm_list_t *tmp_pkg_list = NULL;
	alpm_list_t *v;
	alpm_pkg_t *pkg;
	char *pkgarg;

	struct container *con;

        char c;
        int opt_index = 0;
        static struct option long_options[] = {
                {"pacman-conf", required_argument,      NULL,   'c'}, /* custom path for pacman config file */
		{"dbpath",	required_argument,	NULL,	'd'},
                {"field-delim",	required_argument,      NULL,   'f'},
                {"inner-delim",	required_argument,      NULL,   'i'},
                {"output",      required_argument,      NULL,   'o'},
		{"pkg-delim",	required_argument,	NULL,	'p'},
		{"root",	required_argument,	NULL,	'r'},
		{"surround",	required_argument,	NULL,	's'},
                {"tarball",     required_argument,      NULL,   't'}, /* loads package from tarball */
		{"dbext",	required_argument,	NULL,	'x'},
		{"select-db",	required_argument,	NULL,	'S'},
                {"bytes",       no_argument,            NULL,   'b'},
                {"unix",        no_argument,            NULL,   'u'},
		{"version",	no_argument,		NULL,	'v'},
		{"raw",		no_argument,		NULL,	'w'},
		{"basic",	no_argument,		NULL,	'B'},
		{"output-all",	no_argument,		NULL,	'O'},
                {"pairs",       no_argument,            NULL,   'P'},
		{"relations", 	no_argument,		NULL,	'R'},
		{"help",	no_argument,		NULL,	'h'},
                {NULL, 0, NULL, 0}
        };

        while ((c = getopt_long(argc, argv, "c:d:f:i:o:p:s:t:r:x:S:bpuvwBOPRh",
				long_options, &opt_index)) != -1) {
                switch(c) {
                case 'c':
                        cfg.pacman_conf = optarg;
                        break;
		case 'd':
			cfg.dbpath = optarg;
			break;
		case 'o':
			outarg = optarg;
			break;
		case 'p':
			set_single_character(optarg, &cfg.delim_pkg);
			break;
		case 'r':
			puts(optarg);
			cfg.root = optarg;
			break;
		case 'f':
			set_single_character(optarg, &cfg.delim_field);
			break;
		case 'i':
			set_single_character(optarg, &cfg.delim_inner);
			break;
		case 'b':
			cfg.mask_con |= OPT_BYTES;
			break;
		case 'P':
			cfg.mask_output |= OPT_PAIRS;
			break;
		case 's':
			if (cfg.surround) /* check wether it's not raw */
				set_single_character(optarg, &cfg.surround);
			break;
                case 't':
                        cfg.mask_output |= OPT_TARBALL;
                        pkg_name = optarg;
                        break;
		case 'S':
			/* only local db available for now! */
	
			if (!strcmp(optarg, "local")) {
				cfg.mask_output &= ~OPT_SYNC;
			} else if (!strcmp(optarg, "sync")) {
				cfg.mask_output &= ~OPT_LOCAL;
			} else {
				fprintf(stderr, "error: unknown database '%s'\n", optarg);
				exit(EXIT_FAILURE);
			}
			break;
		case 'w':
			cfg.surround = 0;
			break;
		case 'u':
			cfg.mask_con |= OPT_UNIX;
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
		case 'O':
			for (noutputs = 0; noutputs < ARRAY_SIZE(infos); noutputs++)
				outputs[noutputs] = noutputs;
			break;
		case 'h':
			usage();
		case 'v':
			printf("lspac %s\n", VERSION);
			exit(EXIT_SUCCESS);
		default:
			fprintf(stderr, "Try 'lspac --help' for more information\n");
			exit(EXIT_FAILURE);
                }
        }

	set_bitmask(cfg.mask_con);

	if (!(handle = alpm_initialize(cfg.root, cfg.dbpath, NULL))) {
                fprintf(stderr, "error: unable to initialize alpm\n");
                exit(EXIT_FAILURE);
        }

        if (cfg.mask_output & OPT_TARBALL) {
                if (alpm_pkg_load(handle, pkg_name, 1, 0, &pkg) < 0) {
                        fprintf(stderr, "error: unable to load package '%s'",
                                        pkg_name);
                        exit(EXIT_FAILURE);
                }

                pkg_list = alpm_list_add(pkg_list, pkg);
        }
        if (cfg.mask_output & OPT_LOCAL)
                dbs = alpm_list_add(dbs, alpm_get_localdb(handle));
        if (cfg.mask_output & OPT_SYNC) {
                register_sync_dbs(handle, cfg);
                FOREACH_ALPM_ITEM(v, alpm_get_syncdbs(handle))
                        dbs = alpm_list_add(dbs, v->data);
        }

        if (!noutputs) {
                add_uniq_output(OUT_DBNAME);
                add_uniq_output(OUT_BASENAME);
                add_uniq_output(OUT_VERSION);
        }

	if (outarg && add_out_to_idarray(outarg, outputs, ARRAY_SIZE(outputs),
					 &noutputs, output_name_to_id) < 0)
		exit(EXIT_FAILURE);

	if (optind == argc && !(cfg.mask_output & OPT_TARBALL)) {
		fprintf(stderr, "error: must provide at least one package name\n");
		exit(EXIT_FAILURE);
	} else if (argc > optind) {
		for (; optind < argc; optind++) {
			pkgarg = argv[optind];

                        FOREACH_ALPM_ITEM(v, dbs) {
                                if ((pkg = alpm_db_get_pkg(v->data, pkgarg)))
                                        tmp_pkg_list = alpm_list_add(tmp_pkg_list, pkg);
                        }

                        if (!tmp_pkg_list) {
				fprintf(stderr, "error: package '%s' not found"
                                                " in any given database\n",
                                                pkgarg);
                                exit(EXIT_FAILURE);
                        } else {
                                pkg_list = alpm_list_join(pkg_list, tmp_pkg_list);
                                tmp_pkg_list = NULL;
                        }
		}
	}

	FOREACH_ALPM_ITEM(v, pkg_list) {
		for (size_t i = 0; i < noutputs; i++) {
			con = infos[outputs[i]].get_values(v->data,
					infos[outputs[i]].name);

			print_lspac(con, cfg);
			if (i + 1 < noutputs)
				putchar(cfg.delim_field); /* puts delimiter between fields */
		}
		if (alpm_list_next(v))
			putchar(cfg.delim_pkg); /* puts delimiter between packages */
	}
	putchar('\n'); /* puts newline to output */

	alpm_list_free_inner(pkg_list, alpm_pkg_free_closure(alpm_pkg_free));
        alpm_list_free(pkg_list);
        alpm_list_free(dbs);
	alpm_release(handle);

	return 0;
}
