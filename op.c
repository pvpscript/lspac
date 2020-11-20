#include <stdlib.h>
#include <alpm.h>

#include "container.h"
#include "containerutils.h"

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
	return str_to_container((char *)alpm_db_get_name(data), prefix);
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
