#ifndef STRUTILS_H
#define STRUTILS_H

#define FOREACH_STR(str, arr_ptr) \
	for (; (arr_ptr) && ((str) = *(arr_ptr)); (arr_ptr)++)

#define FOREACH_STR_DESTRUCTIVE(str, arr_ptr) \
	for (; (arr_ptr) && ((str) = *(arr_ptr)); free((str)), (arr_ptr)++)


int add_out_to_idarray(char *list, int *arr, size_t arrsz, size_t *arr_pos,
                       int name_to_id(const char *, size_t));

#endif /* STRUTILS_H */
