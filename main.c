#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

//yeeted from http://www.strudel.org.uk/itoa/
char* itoa(int value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}

int main() {

  struct stat fileStats;
  char * fileName = "./main.c";
  stat(fileName, &fileStats);

  printf("File Name: %s\n", fileName);
  printf("File Size: %ld B\n", fileStats.st_size);
  printf("User id: %d, Group id: %d\n", fileStats.st_uid, fileStats.st_gid);
  printf("File Permissions: %o\n", fileStats.st_mode);
  //https://stackoverflow.com/questions/6373093/how-to-print-binary-number-via-printf
  char buffer [33];
  itoa (fileStats.st_mode,buffer,2);
  printf ("binary: %s\n",buffer);

	int str_size = 11;
  char perm_str[str_size] = "drwxrwxrwx";

	int i;
	for (i = 0; i < 9; i++) {
		if ((fileStats.st_mode >> i) & 1 == 0) {
			perm_str[str_size-2-i] = '-';
		}
	}

	if (!(fileStats.st_mode & 040000)) {
		perm_str[0] = '-';
	}

  printf("Last accessed: %s\n", ctime(&fileStats.st_atim.tv_sec));
  printf("Last modified: %s\n", ctime(&fileStats.st_mtim.tv_sec));

  return 0;
}
