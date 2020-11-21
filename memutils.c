#include <stdio.h>
#include <stdlib.h>

#include "memutils.h"

void *c_malloc(size_t size)
{
	void *data = malloc(size);
	
	if (data == NULL)
		perror("malloc");

	return data;
}

void *c_realloc(void *ptr, size_t size)
{
	void *data = realloc(ptr, size);

	if (data == NULL)
		perror("realloc");

	return data;
}
