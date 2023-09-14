#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Add highlighting and make dotfiles darker (but don't hide them)

#define ASSERT(expr)\
do {\
	if (!(expr)) {\
		printf("Line %d failed assertion '%s' in function '%s'\n", __LINE__, #expr, __FUNCTION__);\
		exit(EXIT_FAILURE);\
	}\
} while (0)

int main(int argc, char **argv) {
	struct dirent *dir_entry;
	DIR *dir_handle;
	size_t input_len;
	char *input_dir;

	if (argc == 2) {
		input_dir = argv[1];
	}
	else {
		input_dir = "./";
	}

	input_len = strlen(input_dir);
	if (input_len < 2 || input_dir[input_len - 1] != '/') {
		printf("'%s' is malformed\n", input_dir);
		return 1;
	}

	dir_handle = opendir(input_dir);
	ASSERT(dir_handle != NULL);

	while ((dir_entry = readdir(dir_handle)) != NULL) {
		if (dir_entry->d_type == DT_REG) {
			puts(dir_entry->d_name);
		}
	}

	closedir(dir_handle);

	return 0;
}
