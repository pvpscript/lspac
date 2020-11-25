#include <stdlib.h>
#include <alpm.h>

#include "../include/container.h"
#include "../include/containerutils.h"

struct container *lspac_pkg_get_name(void *data, char *prefix)
{
	return str_to_container((char *)alpm_pkg_get_name(data), prefix);
}

struct container *lspac_pkg_get_base(void *data, char *prefix)
{
	return str_to_container((char *)alpm_pkg_get_base(data), prefix);
}

struct container *lspac_db_get_name(void *data, char *prefix)
{
	return get_dbname(alpm_pkg_get_db(data), prefix);
}

struct container *lspac_pkg_get_filename(void *data, char *prefix)
{
	return str_to_container((char *)alpm_pkg_get_filename(data), prefix);
}

struct container *lspac_pkg_get_version(void *data, char *prefix)
{
	return str_to_container((char *)alpm_pkg_get_version(data), prefix);
}

struct container *lspac_pkg_get_desc(void *data, char *prefix)
{
	return str_to_container((char *)alpm_pkg_get_desc(data), prefix);
}

struct container *lspac_pkg_get_arch(void *data, char *prefix)
{
	return str_to_container((char *)alpm_pkg_get_arch(data), prefix);
}

struct container *lspac_pkg_get_url(void *data, char *prefix)
{
	return str_to_container((char *)alpm_pkg_get_url(data), prefix);
}

struct container *lspac_pkg_get_packager(void *data, char *prefix)
{
	return str_to_container((char *)alpm_pkg_get_packager(data), prefix);
}

struct container *lspac_pkg_get_md5sum(void *data, char *prefix)
{
	return str_to_container((char *)alpm_pkg_get_md5sum(data), prefix);
}

struct container *lspac_pkg_get_sha256sum(void *data, char *prefix)
{
	return str_to_container((char *)alpm_pkg_get_sha256sum(data), prefix);
}

struct container *lspac_pkg_get_base64_sig(void *data, char *prefix)
{
	return str_to_container((char *)alpm_pkg_get_base64_sig(data), prefix);
}

/* ---------- */

struct container *lspac_pkg_get_licenses(void *data, char *prefix)
{
	return list_to_container(alpm_pkg_get_licenses(data), prefix);
}

struct container *lspac_pkg_get_groups(void *data, char *prefix)
{
	return list_to_container(alpm_pkg_get_groups(data), prefix);
}

/* ---------- */

struct container *lspac_pkg_get_provides(void *data, char *prefix)
{
	return get_depends(alpm_pkg_get_provides(data), prefix);
}

struct container *lspac_pkg_get_depends(void *data, char *prefix)
{
	return get_depends(alpm_pkg_get_depends(data), prefix);
}

struct container *lspac_pkg_get_optdepends(void *data, char *prefix)
{
	return get_depends(alpm_pkg_get_optdepends(data), prefix);
}

struct container *lspac_pkg_get_conflicts(void *data, char *prefix)
{
	return get_depends(alpm_pkg_get_conflicts(data), prefix);
}

struct container *lspac_pkg_get_replaces(void *data, char *prefix)
{
	return get_depends(alpm_pkg_get_replaces(data), prefix);
}

struct container *lspac_pkg_get_checkdepends(void *data, char *prefix)
{
	return get_depends(alpm_pkg_get_checkdepends(data), prefix);
}

struct container *lspac_pkg_get_makedepends(void *data, char *prefix)
{
	return get_depends(alpm_pkg_get_makedepends(data), prefix);
}

/* ---------- */

struct container *lspac_pkg_get_isize(void *data, char *prefix)
{
	return get_size(alpm_pkg_get_isize(data), prefix);
}

struct container *lspac_pkg_get_builddate(void *data, char *prefix)
{
	return get_time(alpm_pkg_get_builddate(data), prefix);
}

struct container *lspac_pkg_get_installdate(void *data, char *prefix)
{
	return get_time(alpm_pkg_get_installdate(data), prefix);
}

/* ---------- */

struct container *lspac_pkg_has_scriptlet(void *data, char *prefix)
{
	return get_boolean(alpm_pkg_has_scriptlet(data), prefix);
}

struct container *lspac_pkg_get_validation(void *data, char *prefix)
{
	return get_validation(alpm_pkg_get_validation(data), prefix);
}

struct container *lspac_pkg_get_reason(void *data, char *prefix)
{
	return get_reason(alpm_pkg_get_reason(data), prefix);
}
