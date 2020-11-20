#include <stdlib.h>
#include <string.h>

#include "container.h"

struct container {
	char *prefix;
        char **arr;
        size_t len;
};

struct container *empty_container(char *prefix)
{
	struct container *c = malloc(sizeof (struct container));

	c->prefix = prefix;
	c->arr = NULL;
	c->len = 0;

	return c;
}

void destroy_container(struct container *c)
{
        free(c->arr);
        free(c);
}

void put_str_alloc(struct container *c, char *str)
{
	size_t strsz;
	
	if (str != NULL) {
		strsz = strlen(str) + 1;

		c->arr = realloc(c->arr, sizeof (char **) * (c->len+2)); /* c_realloc (checked realloc, which finishes the program with perror("malloc");) */

		c->arr[c->len] = malloc(sizeof (char *) * strsz); /* c_malloc */
		strncpy(c->arr[c->len], str, strsz);

		c->arr[++c->len] = NULL;
	}
}

void put_str(struct container *c, char *str)
{
        c->arr = realloc(c->arr, sizeof (char **) * (c->len+2));
        c->arr[c->len] = str;
        c->arr[++c->len] = NULL;
}

char *get_container_prefix(struct container *c)
{
	return c->prefix;
}

char **get_container_arr(struct container *c)
{
	return c->arr;
}
