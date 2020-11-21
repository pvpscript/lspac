#ifndef MEMUTILS_H
#define MEMUTILS_H

/* 
 * A malloc wrapper that tests for allocation errors.
 * In case of an error, it finishes the program.
 */
void *c_malloc(size_t size);

/* 
 * A realloc wrapper that tests for allocation errors.
 * In case of an error, it finishes the program.
 */
void *c_realloc(void *ptr, size_t size);

#endif /* MEMUTILS_H */
