#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <time.h>
#include <sys/stat.h>

char buf[PATH_MAX + 1]; 

// The isdirectory function 
// returns true (nonzero)if path is a directory
// and false (0) otherwise.
int isdirectory(char *path) {
	struct stat statbuf;
	if (stat(path, &statbuf) == -1)
      		return 0;
	else
		return S_ISDIR(statbuf.st_mode); 
}

depthfirst (DIR *root){
	struct dirent *sd;
	printf ("depthfirst e girdi\n");
	while( (sd=readdir(root)) != NULL ){
		printf("while a girdi\n");
                printf("%s\n", sd->d_name);
		realpath(sd->d_name, buf);
		if(isdirectory(buf)){
			printf("if e girdi\n");
			depthfirst (opendir (sd->d_name));
		}
        }
}

int main (int argc, char *argv[]) {

	DIR *root;
	struct dirent *sd;

	root = opendir (".");

	if (root == NULL) {
		printf("dt: Error: Unable to open directory.\n");
		exit(1);
	}

	//while( (sd=readdir(dir)) != NULL ){
	//	printf("%s\n", sd->d_name);
	//}
	
	depthfirst(root);

	closedir(root);

	return 0;

} //end of main
