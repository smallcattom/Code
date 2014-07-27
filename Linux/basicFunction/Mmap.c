#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#define FILELENGTH 80
int main()
{
	int fd = -1;
	char buf[] = "quick brown fox jumps over the lazy dog";
	char *ptr = NULL;
	fd = open("mmap.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);
	if(fd == -1)return -1;
	lseek(fd,FILELENGTH-1,SEEK_SET);

	write(fd,'a',1);


	return 0;
}
