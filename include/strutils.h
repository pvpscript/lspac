#ifndef STRUTILS_H
#define STRUTILS_H

#define FOREACH_STR_DESTRUCTIVE(str, index, arr) \
        for ((index) = 0; (arr) && ((str) = ((arr)[(index)])); \
             free((str)), (index)++)

#define FOREACH_STR(str, index, arr) \
        for ((index) = 0; (arr) && ((str) = ((arr)[(index)])); (index)++)


int add_out_to_idarray(char *list, int *arr, size_t arrsz, size_t *arr_pos,
                       int name_to_id(const char *, size_t));

#endif /* STRUTILS_H */
