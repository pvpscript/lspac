#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv)
{
	static struct option long_options[] = {
		{"aaa",		no_argument,	NULL,	'a'},
		{"test",	required_argument,	NULL,	't'},
	};

	int opt_index = 0;
	char c;
	while ((c = getopt_long(argc, argv, "at:", long_options, &opt_index)) != -1) {
		switch(c) {
			case 'a':
				printf("opt aaa\n");
				break;
			case 't':
				printf("opt test, with value %s\n", optarg);
				break;
		}
	}

	return 0;
}
