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
struct container *lspac_pkg_get_licenses(void *data, char *prefix);
struct container *lspac_pkg_get_groups(void *data, char *prefix);
struct container *lspac_pkg_get_provides(void *data, char *prefix);
struct container *lspac_pkg_get_depends(void *data, char *prefix);
struct container *lspac_pkg_get_optdepends(void *data, char *prefix);
struct container *lspac_pkg_get_conflicts(void *data, char *prefix);
struct container *lspac_pkg_get_replaces(void *data, char *prefix);
struct container *lspac_pkg_get_checkdepends(void *data, char *prefix);
struct container *lspac_pkg_get_makedepends(void *data, char *prefix);
struct container *lspac_pkg_get_isize(void *data, char *prefix);
struct container *lspac_pkg_get_builddate(void *data, char *prefix);
struct container *lspac_pkg_get_installdate(void *data, char *prefix);
struct container *lspac_pkg_has_scriptlet(void *data, char *prefix);
struct container *lspac_pkg_get_validation(void *data, char *prefix);
struct container *lspac_pkg_get_reason(void *data, char *prefix);

#endif /* OP_H */
