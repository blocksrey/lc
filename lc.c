#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Add highlighting and make dotfiles darker (but don't hide them)

#define SHOULD(expression, block)\
do {\
	if (expression) {\
		printf("Line %d expected '%s' in function '%s'\n", __LINE__, #expression, __FUNCTION__);\
		block\
		exit(EXIT_FAILURE);\
	}\
} while (0)

int main(int argc, char **argv) {
	char *flags_string = "bcdflpsu";
	if (argc == 3) {
		flags_string = argv[2];
	}

	unsigned type_mask = 0;
	for (size_t i = strlen(flags_string); i--;) {
		switch (flags_string[i]) {
			case 'b': {
				type_mask |= DT_BLK;
				break;
			}
			case 'c': {
				type_mask |= DT_CHR;
				break;
			}
			case 'd': {
				type_mask |= DT_DIR;
				break;
			}
			case 'f': {
				type_mask |= DT_REG;
				break;
			}
			case 'l': {
				type_mask |= DT_LNK;
				break;
			}
			case 'p': {
				type_mask |= DT_FIFO;
				break;
			}
			case 's': {
				type_mask |= DT_SOCK;
				break;
			}
			case 'u': {
				type_mask |= DT_UNKNOWN;
				break;
			}
		}
	}

	char *dir_string = "./";
	if (argc == 2) {
		dir_string = argv[1];
	}

	size_t dir_string_len = strlen(dir_string);

	SHOULD(dir_string[dir_string_len - 1] != '/', {
		printf("Malformed directory '%s'\n", dir_string);
	});

	DIR *dir_handle = opendir(dir_string);
	SHOULD(dir_handle == NULL, {
		printf("Failed to open directory '%s'\n", dir_string);
	});

	struct dirent *dir_entry;
	while ((dir_entry = readdir(dir_handle)) != NULL) {
		if ((dir_entry->d_type&type_mask) != 0) {
			puts(dir_entry->d_name);
		}
	}

	closedir(dir_handle);

	return 0;
}
