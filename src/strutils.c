#include <stdlib.h>
#include <strings.h>

#include "../include/strutils.h"

/*
 * convert VALUE1,VALUE2,VALUE3,... string to enum keys
 */
static int str_to_idarray(char *list, int *arr, size_t arrsz,
			  int (name_to_id)(const char *, size_t))
{
	const char *begin = NULL;
	const char *p;
	const char *end;
	size_t n = 0;
	int id;

	for(p = list; p && *p; p++) {
		end = NULL;

		if (n >= arrsz)
			return -2;
		if (!begin)
			begin = p;
		if (*p == ',')
			end = p;
		if (*(p + 1) == 0)
			end = p + 1;
		if (!end)
			continue;
		if (end == begin)
			return -1;

		id = name_to_id(begin, end - begin);
		if (id == -1)
			return -1;
		arr[n++] = id;
		begin = NULL;
	}

	return n;
}

int add_out_to_idarray(char *list, int *arr, size_t arrsz, size_t *arr_pos,
		       int (name_to_id)(const char *, size_t))
{
	int r;
	
	if (list[0] == '+')
		list++;
	else
		*arr_pos = 0;
	
	r = str_to_idarray(list, &arr[*arr_pos], arrsz - *arr_pos, name_to_id);
	if (r > 0)
		*arr_pos += r;

	return r;
}
