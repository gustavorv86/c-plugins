
#include <dirent.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../plugins/plugin.h"

const unsigned int MAX_PATH = 1024;
const unsigned int MAX_BUFFER = 1024;

const char * _PROGNAME_ = NULL;

void help_and_exit(void) {
	printf("USAGE: %s <plugin directory> \n\n", _PROGNAME_);
	exit(1);
}

bool str_endswith(const char * string, const char * ends) {
	int string_len = strlen(string);
	int ends_len = strlen(ends);
	
	if(string_len < ends_len) {
		return false;
	}

	// printf("%s == %s \n", string + string_len - ends_len, ends);

	return strncmp(string + string_len - ends_len, ends, ends_len) == 0;
}

int main(int argc, char**argv) {
	
	_PROGNAME_ = argv[0];

	if(argc == 1) {
		help_and_exit();
	}

	printf("START: %s \n", _PROGNAME_);

	const char * plugin_dir = argv[1];

	struct stat stat_plugin_dir;
	stat(plugin_dir, &stat_plugin_dir);
	
	if(! S_ISDIR(stat_plugin_dir.st_mode)) {
		fprintf(stderr, "ERROR: %s is not a directory", plugin_dir);
		exit(1);
	}

	DIR * dir = opendir(plugin_dir);
	if(dir == NULL) {
		perror("ERROR: ");
		exit(1);
	}	
	
	char shared_buffer[MAX_BUFFER];		
	struct dirent * ep;
	while ((ep=readdir(dir)) != NULL) {
		if(! str_endswith(ep->d_name, ".so")) {
			continue;
		}
		const char * plugin_so = ep->d_name;
		char path_plugin_so[MAX_PATH];
		snprintf(path_plugin_so, MAX_PATH, "%s/%s", plugin_dir, plugin_so);

		printf("Loading %s... \n", plugin_so);

		void * handle = dlopen (path_plugin_so, RTLD_LAZY);
		if (!handle) {
			fprintf (stderr, "ERROR: %s\n", dlerror());
			continue;
		}
		
		char * error = NULL;
	
		plugin_read = dlsym(handle, "plugin_read");
		if ((error = dlerror()) != NULL)  {
			fprintf (stderr, "ERROR: %s\n", error);
			dlclose(handle);
			continue;
		}
                
		plugin_write = dlsym(handle, "plugin_write");
		if ((error = dlerror()) != NULL)  {
			fprintf (stderr, "ERROR: %s\n", error);
			dlclose(handle);
			continue;
		}

		plugin_read(shared_buffer, MAX_BUFFER);
		printf("plugin_read: %s\n", shared_buffer);

		snprintf(shared_buffer, MAX_BUFFER, "Hello Write!!");
		plugin_write(shared_buffer, MAX_BUFFER);

		dlclose(handle);
	}
	
	closedir(dir);
	
	printf("END: %s \n", _PROGNAME_);
	return 0;
}

