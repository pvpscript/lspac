#ifndef CONTAINERUTILS_H
#define CONTAINERUTILS_H

#include <alpm.h>

#include "container.h"


#define FOREACH_ALPM_ITEM(ptr, list) \
	for ((ptr) = list; (ptr); (ptr) = alpm_list_next((ptr)))


struct container *str_to_container(char *str, char *prefix);
struct container *list_to_container(alpm_list_t *list, char *prefix);
struct container *get_depends(alpm_list_t *list, char *prefix);
struct container *get_time(alpm_time_t time, char *prefix);
struct container *get_size(off_t size, char *prefix);
struct container *get_required_by(alpm_pkg_t *pkg, char *prefix);
struct container *get_optional_for(alpm_pkg_t *pkg, char *prefix);

#endif /* CONTAINERUTILS_H */
