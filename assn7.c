#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>

/* Promise of Originality
I promise that this source code file has, in its entirety, been
written by myself and by no other person or persons. If at any time an
exact copy of this source code is found to be used by another person in
this term, I understand that both myself and the student that submitted
the copy will receive a zero on this assignment.
*/

long totalSpace = 0;
long my_readdir(char *pathname) {
	DIR *pdir;
	struct dirent *dent;
	struct stat st;
	char *tmpstr;

	fprintf(stdout, "Directory : %s\n", pathname);
	pdir = opendir(pathname);
	if(pdir == NULL){
	    perror("Something happened trying to open directory");
	    exit(1);
	}
	while((dent = readdir(pdir)) != NULL) {
		if(dent->d_name[0] == '.') continue;
		asprintf(&tmpstr, "%s/%s", pathname, dent->d_name);
		if(lstat(tmpstr, &st) != 0){
		    perror("Something happened with file.");
		    exit(1);
		};
		if(S_ISDIR(st.st_mode)) my_readdir(tmpstr);
		else{
		    fprintf(stdout, "   %ld: - Filename : %s\n",st.st_size, dent->d_name);
		    totalSpace += st.st_size;
		}

		free(tmpstr);
	}
	return totalSpace;
}

int main(int argc, char *argv[]) {
	char *pathname = ".";

	if(argc > 1) pathname = argv[1];

	totalSpace = my_readdir(pathname);
	printf("Total File Space Used: %ld\n", totalSpace);

	return 0;
}
