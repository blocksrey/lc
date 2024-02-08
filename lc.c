#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


// Add highlighting and make dotfiles darker (but don't hide them)

#define SHOULD(expression, block)\
do {\
	if (expression) {\
		printf("Line %d expected '%s' in function '%s'\n", __LINE__, #expression, __FUNCTION__);\
		block\
		exit(EXIT_FAILURE);\
	}\
}\
while (0)

#define ANSI_SET(text_state) "\x1b[" text_state "m"

// Offset modifiers from color codes
//#define FG 10
//#define BRIGHT 60
//#define COLOR 30

//#define BOLD 1
//#define DIM 2

//#define ON 0
//#define OFF 20

// Text color codes
//#define BLACK "30"
//#define RED "31"
//#define GREEN "32"
//#define YELLOW "33"
#define BLUE "34"
//#define MAGENTA "35"
//#define CYAN "36"
#define WHITE "37"

#define GRAY "90"

//#define ANSI_END "m"
//#define ANSI_BEGIN "\x1b"
//#define ANSI_AND ";"

#define RESET "0"

static void print_path_info(char *path) {
	struct stat file_stat;

	SHOULD(stat(path, &file_stat) != 0, {
		printf("Stat failed for path '%s'", path);
	});

	char perm_string[] = {
		file_stat.st_mode&S_IRUSR ? 'r' : '-',
		file_stat.st_mode&S_IWUSR ? 'w' : '-',
		file_stat.st_mode&S_IXUSR ? 'x' : '-',
		file_stat.st_mode&S_IRGRP ? 'r' : '-',
		file_stat.st_mode&S_IWGRP ? 'w' : '-',
		file_stat.st_mode&S_IXGRP ? 'x' : '-',
		file_stat.st_mode&S_IROTH ? 'r' : '-',
		file_stat.st_mode&S_IWOTH ? 'w' : '-',
		file_stat.st_mode&S_IXOTH ? 'x' : '-',
		'\0'
	};

	// Get owner and group names
	struct passwd *pw = getpwuid(file_stat.st_uid);
	struct group *gr = getgrgid(file_stat.st_gid);

	// Get time of last modification
	char timeStr[32];
	strftime(timeStr, sizeof(timeStr), "%c", localtime(&file_stat.st_mtime));

	printf("%s %s %s %6ld %s" " " ANSI_SET(WHITE) "%s" "\n",
		perm_string,
		pw ? pw->pw_name : "",
		gr ? gr->gr_name : "",
		file_stat.st_size,
		timeStr,
		path
	);
}

int main(int argc, char **argv) {
	char *flags_string = "";
	if (argc == 3) {
		flags_string = argv[2];
	}

	int show_info = 0;
	int list_form = 0;

	unsigned type_mask = 0;
	for (size_t i = strlen(flags_string); i--;) {
		switch (flags_string[i]) {
			case 'r': {
				list_form = 1;
				break;
			}
			case 'i': {
				show_info = 1;
				break;
			}
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

	if (type_mask == 0) {
		type_mask = 0xffffffff;
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

	size_t nod_heap_count = 32; // This can never be zero
	size_t nod_strings_count = 0;
	char **nod_strings = (char **)malloc(nod_heap_count*sizeof(char *));

	size_t dir_heap_count = 32; // This can never be zero
	size_t dir_strings_count = 0;
	char **dir_strings = (char **)malloc(dir_heap_count*sizeof(char *));

	struct dirent *dir_entry;
	while ((dir_entry = readdir(dir_handle)) != NULL) {
		if ((dir_entry->d_type&type_mask) != 0) {
			switch (dir_entry->d_type) {
				default: {
					if (nod_strings_count > nod_heap_count) {
						nod_heap_count *= 2;
						nod_strings = (char **)realloc(nod_strings, nod_heap_count*sizeof(char *));
					}

					nod_strings[nod_strings_count++] = dir_entry->d_name;

					break;
				}
				case DT_DIR: {
					if (dir_strings_count > dir_heap_count) {
						dir_heap_count *= 2;
						dir_strings = (char **)realloc(dir_strings, dir_heap_count*sizeof(char *));
					}

					dir_strings[dir_strings_count++] = dir_entry->d_name;

					break;
				}
			}
		}
	}

	closedir(dir_handle);

	switch (show_info) {
		case 1: {
			for (size_t i = nod_strings_count; i--;) {
				print_path_info(nod_strings[i]);
			}

			for (size_t i = dir_strings_count; i--;) {
				print_path_info(nod_strings[i]);
			}

			break;
		}
		case 0: {
			for (size_t i = nod_strings_count; i--;) {
				print_path_info(nod_strings[i]);
			}

			for (size_t i = dir_strings_count; i--;) {
				print_path_info(nod_strings[i]);
			}

			break;
		}
	}

	return 0;
}
