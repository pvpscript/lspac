#include <stdlib.h>
#include <time.h>
#include <alpm.h>

#include "container.h"
#include "containerutils.h"

static int time_raw;
static int size_raw;

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
	time_t _time = *((time_t *)time);
	struct tm *ltime;
	char buf[50];

	if (time) {
		if (time_raw) {
			snprintf(buf, 50, "%lld", (long long)time);
		} else {
			ltime = localtime(&_time);
			strftime(buf, 50, "%F %T", ltime);
		}

		put_str_alloc(c, buf);
	}

	return c;
}

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

	if (size_raw)
		snprintf(buf, 50, "%lld", (long long)size);
	else
		fmt_human_readable_size(size, buf);

	put_str_alloc(c, buf);

	return c;
}

struct container *get_required_by(alpm_pkg_t *pkg, char *prefix)
{
	struct container *c = empty_container(prefix);
	alpm_list_t *content = alpm_pkg_compute_requiredby(pkg);
	alpm_list_t *v;

	FOREACH_ALPM_ITEM(v, content)
		put_str(c, v->data);

	alpm_list_free(content);

	return c;
}

struct container *get_optional_for(alpm_pkg_t *pkg, char *prefix)
{
	struct container *c = empty_container(prefix);
	alpm_list_t *content = alpm_pkg_compute_optionalfor(pkg);
	alpm_list_t *v;

	FOREACH_ALPM_ITEM(v, content)
		put_str(c, v->data);

	alpm_list_free(content);

	return c;
}
