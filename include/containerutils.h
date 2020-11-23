#ifndef CONTAINERUTILS_H
#define CONTAINERUTILS_H

#include <alpm.h>

#include "container.h"


#define FOREACH_ALPM_ITEM(ptr, list) \
	for ((ptr) = list; (ptr); (ptr) = alpm_list_next((ptr)))


/* 
 * options to be handled.
 *
 * overkill, scalable, or simply shenanigans? :)
 */
enum {
        OPT_BYTES 	= (1 << 0),
        OPT_UNIX 	= (1 << 1)
};

/*
 * sets the bitmask according to the enum flags
 */
void set_bitmask(unsigned mask);

struct container *str_to_container(char *str, char *prefix);
struct container *list_to_container(alpm_list_t *list, char *prefix);
struct container *get_depends(alpm_list_t *list, char *prefix);
struct container *get_time(alpm_time_t time, char *prefix);
struct container *get_size(off_t size, char *prefix);
struct container *get_required_by(alpm_pkg_t *pkg, char *prefix);
struct container *get_optional_for(alpm_pkg_t *pkg, char *prefix);
struct container *get_dbname(alpm_db_t *db, char *prefix);
struct container *has_scriptlet(int b, char *prefix);
struct container *get_reason(alpm_pkgreason_t r, char *prefix);
struct container *get_validation(alpm_pkgvalidation_t v, char *prefix);


#endif /* CONTAINERUTILS_H */
