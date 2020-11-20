#ifndef OP_H
#define OP_H

#include "container.h"

struct container *lspac_pkg_get_name(void *data, char *prefix);
struct container *lspac_pkg_get_base(void *data, char *prefix);
struct container *lspac_db_get_name(void *data, char *prefix);
struct container *lspac_pkg_get_filename(void *data, char *prefix);
struct container *lspac_pkg_get_version(void *data, char *prefix);
struct container *lspac_pkg_get_desc(void *data, char *prefix);
struct container *lspac_pkg_get_arch(void *data, char *prefix);
struct container *lspac_pkg_get_url(void *data, char *prefix);
struct container *lspac_pkg_get_packager(void *data, char *prefix);
struct container *lspac_pkg_get_md5sum(void *data, char *prefix);
struct container *lspac_pkg_get_sha256sum(void *data, char *prefix);
struct container *lspac_pkg_get_base64_sig(void *data, char *prefix);

#endif /* OP_H */
