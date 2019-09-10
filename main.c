#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

char buf[PATH_MAX + 1]; 
//char buff[PATH_MAX];
//char buff2[PATH_MAX];

// The isdirectory function 
// returns true (nonzero)if path is a directory
// and false (0) otherwise.


int isdirectory(char *path) {
	struct stat statbuf;
	if (stat(path, &statbuf) == -1){
		//printf("%s",errno);		
      		//printf("%s if e girdi ve 0 return etti\n",path);
		//printf("isdir degeri: %d\n",S_ISDIR(statbuf.st_mode));
		return 0;
	}
	else {
		//printf("%s else e girdi ve 0 return etti\n",path);
		return S_ISDIR(statbuf.st_mode);
	}
}

depthfirst (char *dirpath, int space, int spaceOriginal, int ThirdOption){
	DIR *root;
	root = opendir(dirpath);
	struct dirent *sd;
	struct stat statbuf;
	char buff[PATH_MAX];
	char buff2[PATH_MAX];
	if (root == NULL) {
                perror("dt: Error: Unable to open directory.\n");
                exit(1);
        } 
	while( (sd=readdir(root)) != NULL ){
		realpath(sd->d_name, buf);
		if ( !(strcmp(sd->d_name,".")==0 || strcmp(sd->d_name,"..")==0) ){
			int i;
			for (i=0;i<space;i++){
				printf(" ");
			}
			printf("%s\t", sd->d_name);
//printf("1");
			switch(ThirdOption){
				case 1: /* L */
					break;
				case 2: /* d */
					printf("Last Access: %s",ctime(&statbuf.st_atime));
                                        break;
				case 3: /* g */
					printf("Group id: %d", statbuf.st_uid);
                                        break;
				case 4: /* i */
					printf("Number of links: %d", statbuf.st_nlink);
                                        break;
                                case 5: /* p */
					printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
    					printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
    					printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
    					printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
    					printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
    					printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
    					printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
    					printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
    					printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
    					printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
                                        break;
                                case 6: /* s */
					//printf("File Size: %d bytes and ",statbuf.st_size);
					if (statbuf.st_size/1000000000.0 > 1) printf("File Size: %.2fG",(double)statbuf.st_size/1000000000.0);
					else if (statbuf.st_size/1000000.0 > 1) printf("File Size: %.2fM",(double)statbuf.st_size/1000000.0);
					else if (statbuf.st_size/1000.0 > 1) printf("File Size: %.2fK",(double)statbuf.st_size/1000.0);
					else printf("File Size: %d bytes",statbuf.st_size);
                                        break;
				case 7: /* t */
					if (!(stat(buf, &statbuf) == -1)){
						if (S_ISBLK(statbuf.st_mode)) printf ("block special file");
						else if(S_ISCHR(statbuf.st_mode)) printf ("character special file");
						else if(S_ISDIR(statbuf.st_mode)) printf ("directory");
						else if(S_ISFIFO(statbuf.st_mode)) printf ("pipe or FIFO special file");
                                                else if(S_ISLNK(statbuf.st_mode)) printf ("symbolic link");
						else if(S_ISREG(statbuf.st_mode)) printf ("regular file");
                                                else if(S_ISSOCK(statbuf.st_mode)) printf ("socket");
					}
                                        break;
                                case 8: /* u */
					printf("User id: %d ", statbuf.st_uid);
                                        break;
                                case 9: /* l */
					if (!(stat(buf, &statbuf) == -1)){
                                                if (S_ISBLK(statbuf.st_mode)) printf ("block special file\t");
                                                else if(S_ISCHR(statbuf.st_mode)) printf ("character special file\t");
                                                else if(S_ISDIR(statbuf.st_mode)) printf ("directory\t");
                                                else if(S_ISFIFO(statbuf.st_mode)) printf ("pipe or FIFO special file\t");
                                                else if(S_ISLNK(statbuf.st_mode)) printf ("symbolic link\t");
                                                else if(S_ISREG(statbuf.st_mode)) printf ("regular file\t");
                                                else if(S_ISSOCK(statbuf.st_mode)) printf ("socket\t");
                                        }

					printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
                                        printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
                                        printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
                                        printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
                                        printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
                                        printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
                                        printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
                                        printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
                                        printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
                                        printf( (statbuf.st_mode & S_IXOTH) ? "x\t" : "-\t");
					
					printf("Number of links: %d\t", statbuf.st_nlink);

					printf("Group id: %d\t", statbuf.st_uid);

					printf("User id: %d\t", statbuf.st_uid);

					if (statbuf.st_size/1000000000.0 > 1) printf("File Size: %.2fG",(double)statbuf.st_size/1000000000.0);
                                        else if (statbuf.st_size/1000000.0 > 1) printf("File Size: %.2fM",(double)statbuf.st_size/1000000.0);
                                        else if (statbuf.st_size/1000.0 > 1) printf("File Size: %.2fK",(double)statbuf.st_size/1000.0);
                                        else printf("File Size: %d bytes",statbuf.st_size);

                                        break;
			} /* end of switch */
                	printf("\n");
			/*
			printf("buf is: %s\n",buf);
                	printf("the value of isdirectory : %d\n", isdirectory(bufp));
			printf("the value of isFile : %d\n", isFile(bufp));
			printf("the value of d_type & DT_DIR: \n", sd->d_type & DT_DIR);
			printf("-------------\n");
			*/
		} /* end of if */
		
//printf("2");
		if (isdirectory(buf)){
//printf("3");
			if ( !(strcmp(sd->d_name,".")==0 || strcmp(sd->d_name,"..")==0) ){
//printf("4");
				getcwd(buff,PATH_MAX);
				getcwd(buff2,PATH_MAX);
//printf("5");
				//printf("%s\n",buff);
//printf("a");
				strcat(buff,"/");
//printf("b");
				strcat(buff,sd->d_name);
//printf("c");
				//printf("%s\n",buff);
//printf("d");
				if (chdir(buff)==0){
					depthfirst (dirpath,space+spaceOriginal,spaceOriginal,ThirdOption);
				}
				if (chdir(buff2)!=0){
					printf("ger donus cortladi");
					exit(1);
				}
				//depthfirst (opendir (sd->d_name),space+spaceOriginal,spaceOriginal,ThirdOption);
			}
		} // end of isdirectory if
        } // end of while
	closedir(root);
} // end of depthfirst

int main (int argc, char * const argv[]) {
	int option;
	int argOfI;
	int optCount = 0;
	int ThirdOption = 0;
	bool hflag = false;
	bool Iflag = false;
	bool Lflag = false;
	bool dflag = false;
        bool gflag = false;
        bool iflag = false;
	bool pflag = false;
        bool sflag = false;
	bool tflag = false;
        bool uflag = false;
        bool lflag = false;
	while ((option = getopt (argc,argv,"hI:Ldgiphstul")) != -1) {
		switch (option) {
			case 'h':
				hflag = true;
				optCount++;
				break;
			case 'I':
                                Iflag = true;
				printf("%s",optarg);
				if (optarg == NULL){
					perror("dt: Error: error happened, program execution is over, need argument for -I\n");
					exit(1);
				}
				argOfI = atoi(optarg);
                                optCount++;
				optCount++;
				break;
			case 'L':
                                Lflag = true;
                                optCount++;
				ThirdOption = 1;
				break;
			case 'd':
                                dflag = true;
                                optCount++;
				ThirdOption = 2;
				break;
                        case 'g':
                                gflag = true;
                                optCount++;
				ThirdOption = 3;
				break;
                        case 'i':
                                iflag = true;
                                optCount++;
				ThirdOption = 4;
				break;
			case 'p':
                                pflag = true;
                                optCount++;
				ThirdOption = 5;
				break;
                        case 's':
                                sflag = true;
                                optCount++;
				ThirdOption = 6;
				break;
                        case 't':
                                tflag = true;
                                optCount++;
				ThirdOption = 7;
				break;
			case 'u':
                                uflag = true;
                                optCount++;
				ThirdOption = 8;
				break;
                        case 'l':
                                lflag = true;
                                optCount++;
				ThirdOption = 9;
				break;
		}
	}	
	
	char *dirpath;
	struct dirent *sd;
	if(argc < 2 || argc-1 == optCount) {
		dirpath = ".";
	}

	else {
		//getcwd(buff,PATH_MAX);
		dirpath = argv[argc-1];
	}
	printf("\n\n");
	if (hflag){
                printf ("Help Message\n");
		printf ("This program traverse directories\n");
		printf ("Please see following execute options\nh Print a help message and exit\nI n Change indentation tonspaces for each level\n");
		printf ("L Follow symbolic links, if any. Default will be to not follow symbolic links\n");
		printf ("t Print information on file type\np Print permission bits asrwxrwxrwx\ni Print the number of links to file in inode table\n");
		printf ("u Print theuidassociated with the file\ng Print thegidassociated with the file\ns Print the size of file in bytes\nd Show the time of last modification\n");
		printf ("l This option will be used to print information on the file as if the optionstpiugsare all specified\n");
		exit(1);
        }	
	if (Iflag){
		depthfirst(dirpath,argOfI,argOfI,ThirdOption);
	} else {
		depthfirst(dirpath,4,4,ThirdOption);
	}

	return 0;

} //end of main
