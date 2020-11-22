#ifndef CONTAINER_H
#define CONTAINER_H

struct container;

struct container *empty_container(char *prefix);
void destroy_container(struct container *c);
void put_str_alloc(struct container *c, char *str);
void put_str(struct container *c, char *str);
char *get_container_prefix(struct container *c);
char **get_container_arr(struct container *c);

#endif /* CONTAINER_H */
