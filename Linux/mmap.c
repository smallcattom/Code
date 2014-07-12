#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>/*mmap*/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#define  FILELENGTH 80
/*
 mmap是将文件映射到内存空间里进行读写数据，偏移等。由于在内存中操作，可以提高速度。
 */
int main()
{
	int fd = -1;
	char buf[] = "quick brown fox jumps over the lazy dog";
	char *ptr = NULL;
	fd = open("tmp.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);
	if(fd == -1)
		return -1;
	lseek(fd,FILELENGTH-1,SEEK_SET);
	char ch = 'a';
	write(fd,"a",1);
	ptr = (char*)mmap(NULL,FILELENGTH,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	if((char*)-1 == ptr){
		puts("mmap failure\n");
		close(fd);
		return -1;
	}
	memcpy(ptr + 16,buf,strlen(buf));
	munmap(ptr,FILELENGTH);
	close(fd);
	return 0;
}
