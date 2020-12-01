#ifndef CONTAINER_H
#define CONTAINER_H

/*
 * Holds a string container
 */
struct container;

/*
 * Creates an empty container
 *
 * @param prefix: the container prefix name
 * @returns a pointer to a container struct
 */
struct container *empty_container(char *prefix);

/* 
 * Frees the memory of a container
 *
 * @param c: a pointer to a container
 */
void destroy_container(struct container *c);

/*
 * Puts the string 'str' into the container allocating memory for it
 *
 * @param c: a pointer to a container
 * @param str: a pointer to a string
 */
void put_str_alloc(struct container *c, char *str);

/*
 * Puts the string 'str' into the container without allocating memory for it
 *
 * @param c: a pointer to a container
 * @param str: a pointer to a string
 */
void put_str(struct container *c, char *str);

/*
 * Returns the container's prefix name
 *
 * @param c: a pointer to a container
 * @returns the container's prefix
 */
char *get_container_prefix(struct container *c);

/*
 * Returns the container array of strings
 *
 * @param c: a pointer to a container
 * @returns an array of strings
 */
char **get_container_arr(struct container *c);

#endif /* CONTAINER_H */
