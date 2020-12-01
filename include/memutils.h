#ifndef MEMUTILS_H
#define MEMUTILS_H

/* 
 * A malloc wrapper that tests for allocation errors. In case of an error,
 * it finishes the program.
 *
 * @param size: the size to allocate in memory
 * @returns: a pointer to the allocated area
 */
void *c_malloc(size_t size);

/* 
 * A realloc wrapper that tests for allocation errors. In case of an error,
 * it finishes the program.
 *
 * @param ptr: a pointer to an area in memory to be reallocated
 * @param size: the size to reallocate in memory
 * @returns: a pointer to the reallocated area
 */
void *c_realloc(void *ptr, size_t size);

#endif /* MEMUTILS_H */
