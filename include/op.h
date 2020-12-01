#ifndef OP_H
#define OP_H

/*
 * Encapsulation for useful alpm functions
 */

#include "container.h"

/*
 * Creates a container that holds a string representing a package's name
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_name(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's base name
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_base(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's database
 * name
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_db_get_name(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's filename
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_filename(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's version
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_version(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's description
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_desc(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's
 * architecture
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_arch(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's's URL
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_url(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's packager
 * name
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_packager(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's md5 sum
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_md5sum(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's sha256 sum
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_sha256sum(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's base64
 * signature
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_base64_sig(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's licences
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_licenses(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's groups
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_groups(void *data, char *prefix);

/*
 * Creates a container that holds an array of strings representing packages
 * provided by the given package
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_provides(void *data, char *prefix);

/*
 * Creates a container that holds an array of strings representing a package's
 * dependencies
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_depends(void *data, char *prefix);

/*
 * Creates a container that holds an array of strings representing a package's
 * optional dependencies
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_optdepends(void *data, char *prefix);

/*
 * Creates a container that holds an array of strings representing the packages
 * that conflicts with the given package
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_conflicts(void *data, char *prefix);

/*
 * Creates a container that holds an array of strings representing the packages
 * that are replaced by the given package
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_replaces(void *data, char *prefix);

/*
 * Creates a container that holds an array of strings representing the check
 * dependencies of a given package
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_checkdepends(void *data, char *prefix);

/*
 * Creates a container that holds an array of strings representing the make
 * dependencies of a given package
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_makedepends(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's installed
 * size
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_isize(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's build date
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_builddate(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's install
 * date
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_installdate(void *data, char *prefix);

/*
 * Creates a container that holds a string indicating if a given packag has
 * a scriptlet
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_has_scriptlet(void *data, char *prefix);

/*
 * Creates a container that holds an array of strings representing the
 * validations for a given package
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_validation(void *data, char *prefix);

/*
 * Creates a container that holds a string representing a package's
 * installation reason
 *
 * @param data: an alpm package
 * @param prefix: a container prefix
 * @returns a pointer to a container
 */
struct container *lspac_pkg_get_reason(void *data, char *prefix);

#endif /* OP_H */
