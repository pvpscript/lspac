#include <stdlib.h>
#include <alpm.h>

#include "container.h"
#include "containerutils.h"

struct container *lspac_pkg_get_name(void *data, char *prefix)
{
	alpm_pkg_t *pkg = (alpm_pkg_t *)data;

	return str_to_container((char *)alpm_pkg_get_name(pkg), prefix);
}

struct container *lspac_pkg_get_base(void *data, char *prefix)
{
	alpm_pkg_t *pkg = (alpm_pkg_t *)data;

	return str_to_container((char *)alpm_pkg_get_base(pkg), prefix);
}

struct container *lspac_db_get_name(void *data, char *prefix)
{
	alpm_db_t *db = (alpm_db_t *)data;

	return str_to_container((char *)alpm_db_get_name(db), prefix);
}

struct container *lspac_pkg_get_filename(void *data, char *prefix)
{
	alpm_pkg_t *pkg = (alpm_pkg_t *)data;

	return str_to_container((char *)alpm_pkg_get_filename(pkg), prefix);
}

struct container *lspac_pkg_get_version(void *data, char *prefix)
{
	alpm_pkg_t *pkg = (alpm_pkg_t *)data;

	return str_to_container((char *)alpm_pkg_get_version(pkg), prefix);
}

struct container *lspac_pkg_get_desc(void *data, char *prefix)
{
	alpm_pkg_t *pkg = (alpm_pkg_t *)data;

	return str_to_container((char *)alpm_pkg_get_desc(pkg), prefix);
}

struct container *lspac_pkg_get_arch(void *data, char *prefix)
{
	alpm_pkg_t *pkg = (alpm_pkg_t *)data;

	return str_to_container((char *)alpm_pkg_get_arch(pkg), prefix);
}

struct container *lspac_pkg_get_url(void *data, char *prefix)
{
	alpm_pkg_t *pkg = (alpm_pkg_t *)data;

	return str_to_container((char *)alpm_pkg_get_url(pkg), prefix);
}

struct container *lspac_pkg_get_packager(void *data, char *prefix)
{
	alpm_pkg_t *pkg = (alpm_pkg_t *)data;

	return str_to_container((char *)alpm_pkg_get_packager(pkg), prefix);
}

struct container *lspac_pkg_get_md5sum(void *data, char *prefix)
{
	alpm_pkg_t *pkg = (alpm_pkg_t *)data;

	return str_to_container((char *)alpm_pkg_get_md5sum(pkg), prefix);
}

struct container *lspac_pkg_get_sha256sum(void *data, char *prefix)
{
	alpm_pkg_t *pkg = (alpm_pkg_t *)data;

	return str_to_container((char *)alpm_pkg_get_sha256sum(pkg), prefix);
}

struct container *lspac_pkg_get_base64_sig(void *data, char *prefix)
{
	alpm_pkg_t *pkg = (alpm_pkg_t *)data;

	return str_to_container((char *)alpm_pkg_get_base64_sig(pkg), prefix);
}
