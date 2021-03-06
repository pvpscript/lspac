#include <stdlib.h>
#include <time.h>
#include <alpm.h>

#include "../include/container.h"
#include "../include/containerutils.h"

static unsigned bitmask;


void set_bitmask(unsigned mask)
{
	bitmask = mask;
}

struct container *str_to_container(char *str, char *prefix)
{
	struct container *c = empty_container(prefix);
	
	put_str_alloc(c, str);

	return c;
}

struct container *list_to_container(alpm_list_t *list, char *prefix)
{
        struct container *c = empty_container(prefix);
        alpm_list_t *v;

        FOREACH_ALPM_ITEM(v, list)
                put_str_alloc(c, v->data);

        return c;
}

struct container *get_depends(alpm_list_t *list, char *prefix)
{
	struct container *c = empty_container(prefix);
	alpm_list_t *v;

	FOREACH_ALPM_ITEM(v, list)
		put_str(c, alpm_dep_compute_string(v->data));

	return c;
}

struct container *get_time(alpm_time_t time, char *prefix)
{
	struct container *c = empty_container(prefix);
	time_t _time = (time_t)time;
	struct tm *ltime;
	char buf[50];

	if (time) {
		if (bitmask & OPT_UNIX) {
			snprintf(buf, 50, "%lld", (long long)time);
		} else {
			ltime = localtime(&_time);
			strftime(buf, 50, "%F %T", ltime);
		}

		put_str_alloc(c, buf);
	}

	return c;
}

/* 
 * Formats bytes to human readable size.
 */
static void fmt_human_readable_size(off_t bytes, char *output) {
	double d_bytes = (double) bytes;
	static char *suffix[] = {"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB",
		"ZiB", "YiB", NULL};
	int i;

	for(i = 0; d_bytes >= 1000 && suffix[i+1]; d_bytes /= 1024, i++);

	sprintf(output, "%.2f%s", d_bytes, suffix[i]);
}

struct container *get_size(off_t size, char *prefix)
{
	struct container *c = empty_container(prefix);
	char buf[50];

	if (bitmask & OPT_BYTES)
		snprintf(buf, 50, "%lld", (long long)size);
	else
		fmt_human_readable_size(size, buf);

	put_str_alloc(c, buf);

	return c;
}

struct container *get_dbname(alpm_db_t *db, char *prefix)
{
	return str_to_container((char *)alpm_db_get_name(db), prefix);
}

struct container *get_boolean(int b, char *prefix)
{
	return str_to_container(b ? "Yes" : "No", prefix);
}

struct container *get_reason(alpm_pkgreason_t r, char *prefix)
{
	int expl = r == ALPM_PKG_REASON_EXPLICIT;

	return str_to_container(expl ? "Explicit" : "Dependency", prefix);
}

struct container *get_validation(alpm_pkgvalidation_t v, char *prefix)
{
	struct container *c = empty_container(prefix);

	if (v == ALPM_PKG_VALIDATION_UNKNOWN)
		put_str_alloc(c, "Unknown");
	if (v & ALPM_PKG_VALIDATION_NONE)
		put_str_alloc(c, "None");
	if (v & ALPM_PKG_VALIDATION_MD5SUM)
		put_str_alloc(c, "MD5");
	if (v & ALPM_PKG_VALIDATION_SHA256SUM)
		put_str_alloc(c, "SHA-256");
	if (v & ALPM_PKG_VALIDATION_SIGNATURE)
		put_str_alloc(c, "Signature");

	return c;
}
