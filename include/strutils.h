#ifndef STRUTILS_H
#define STRUTILS_H

/*
 * Iterates over an array of strings
 */
#define FOREACH_STR(str, arr_ptr) \
	for (; (arr_ptr) && ((str) = *(arr_ptr)); (arr_ptr)++)

/* 
 * Iterates over an array of strings and frees the memory for each string
 */
#define FOREACH_STR_DESTRUCTIVE(str, arr_ptr) \
	for (; (arr_ptr) && ((str) = *(arr_ptr)); free((str)), (arr_ptr)++)


/*
 * Adds an output list to an id array
 *
 * @param list: a comma separated list of outputs
 * @param arr: a pointer to an array of ids
 * @param arrsz: the length of the array of ids
 * @param arr_pos: a position for an array of ids
 * @param name_to_id: function that converts a string name to an enum id
 * @return the amount of added ids or -1 on error
 */
int add_out_to_idarray(char *list, int *arr, size_t arrsz, size_t *arr_pos,
                       int name_to_id(const char *, size_t));

#endif /* STRUTILS_H */
