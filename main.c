#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main() {

  struct stat fileStats;
  char * fileName = "./main.c";
  stat(fileName, &fileStats);

  printf("File Name: %s\n", fileName);
	//Base 10 for hard disk, base 2 for memory
  printf("File Size: %ld GB %ld MB %ld KB %ld B\n", fileStats.st_size/1000000000%1000, fileStats.st_size/1000000%1000, fileStats.st_size/1000%1000, fileStats.st_size%1000);
  printf("User id: %d, Group id: %d\n", fileStats.st_uid, fileStats.st_gid);
	int str_size = 11;
  char perm_str[] = "drwxrwxrwx";

	int i;
	for (i = 0; i < 9; i++) {
		if (((fileStats.st_mode >> i) & 1) == 0) {
			perm_str[str_size-2-i] = '-';
		}
	}

	if (!(fileStats.st_mode & 040000)) {
		perm_str[0] = '-';
	}

	printf("File Permissions: %s\n", perm_str);

  printf("Last accessed: %s\n", ctime(&fileStats.st_atim.tv_sec));
  printf("Last modified: %s\n", ctime(&fileStats.st_mtim.tv_sec));

  return 0;
}

/*
This is an extra comment to increase the size of the file. :))))))))))))))))))))))))))))))))000
*/
