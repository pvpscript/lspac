#ifndef CONTAINERUTILS_H
#define CONTAINERUTILS_H

#include <alpm.h>

#include "container.h"


/*
 * Iterates over an alpm_list_t list
 */
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
 *
 * @param mask: a bitmask
 */
void set_bitmask(unsigned mask);

/*
 * Creates a container with the given string and prefix
 *
 * @param str: a pointer to a string
 * @param prefix: a container prefix
 * @returns a pointer to a new container
 */
struct container *str_to_container(char *str, char *prefix);

/*
 * Creates a container with an array of strings given by a list
 *
 * @param list: a list that contains strings
 * @param prefix: a container prefix
 * @returns a pointer to a new container
 */
struct container *list_to_container(alpm_list_t *list, char *prefix);

/*
 * Creates a container that holds a string list of a package's dependencies
 *
 * @param list: a list of dependencies
 * @param prefix: a container prefix
 * @returns a pointer to a new container
 */
struct container *get_depends(alpm_list_t *list, char *prefix);

/*
 * Creates a container that holds a string representing a timestamp
 *
 * @param time: an unix timestamp
 * @param prefix: a container prefix
 * @returns a pointer to a new container
 */
struct container *get_time(alpm_time_t time, char *prefix);

/*
 * Creates a container that holds a string representing a size
 *
 * @param size: a size in bytes
 * @param prefix: a container prefix
 * @returns a pointer to a new container
 */
struct container *get_size(off_t size, char *prefix);

/*
 * Creates a container that holds an array of strings representing the
 * packages required by the given package
 *
 * @param pkg: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a new container
 */
struct container *get_required_by(alpm_pkg_t *pkg, char *prefix);

/*
 * Creates a container that holds an array of strings representing the
 * packages optionally required by the given package
 *
 * @param pkg: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a new container
 */
struct container *get_optional_for(alpm_pkg_t *pkg, char *prefix);

/*
 * Creates a container that holds a string representing the name of a
 * alpm database
 *
 * @param db: an alpm database
 * @param prefix: a container prefix
 * @returns a pointer to a new container
 */
struct container *get_dbname(alpm_db_t *db, char *prefix);

/*
 * Creates a container that holds a string containing "Yes" or "No",
 * representing a boolean
 *
 * @param b: a boolean value
 * @param prefix: a container prefix
 * @returns a pointer to a new container
 */
struct container *get_boolean(int b, char *prefix);

/*
 * Creates a container that holds a string representing an alpm package
 * installation reason
 *
 * @param r: an installation reason
 * @param prefix: a container prefix
 * @returns a pointer to a new container
 */
struct container *get_reason(alpm_pkgreason_t r, char *prefix);

/*
 * Creates a container that holds an array of strings representing
 * an alpm package validation
 *
 * @param v: a package validation
 * @param prefix: a container prefix
 * @returns a pointer to a new container
 */
struct container *get_validation(alpm_pkgvalidation_t v, char *prefix);


#endif /* CONTAINERUTILS_H */
