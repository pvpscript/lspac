#ifndef ARGS_H
#define ARGS_H

/*
DBNAME NAME VERSION FILENAME DESC ARCH URL PACKAGER [LICENSES]
[GROUPS] [PROVIDES] [DEPENDS] [OPTDEPENDS] [CONFLICTS] [REPLACES]
[CHECKDEPENDS] [MAKEDEPENDS] SIZE BUILDDATE INSTALLDATE
SCRIPTLET VALIDATION REASON 
*/

typedef enum output {
	FLAG_DBNAME = (1 << 0),
	FLAG_NAME = (1 << 1),
	FLAG_FILENAME = (1 << 2),
	FLAG_DESC = (1 << 3),
	FLAG_ARCH = (1 << 4),
	FLAG_URL = (1 << 5),
	FLAG_PACKAGER = (1 << 6),
	FLAG_LICENSES = (1 << 7),
	FLAG_GROUPS = (1 << 8),
	FLAG_PROVIDES = (1 << 9),
	FLAG_DEPENDS = (1 << 10),
	FLAG_OPTDEPENDS = (1 << 11),
	FLAG_CONFLICTS = (1 << 12),
	FLAG_REPLACES = (1 << 13),
	FLAG_CHECKDEPENDS = (1 << 14),
	FLAG_MAKEDEPENDS = (1 << 15),
	FLAG_SIZE = (1 << 16),
	FLAG_BUILDDATE = (1 << 17),
	FLAG_INSTALLDATE = (1 << 18),
	FLAG_SCRIPTLET = (1 << 19),
	FLAG_VALIDATION = (1 << 20),
	FLAG_REASON = (1 << 20),
	FLAG_VERSION = (1 << 21)
} output;

int parse_args(int argc, char **argv);

#endif /* ARGS_H */
