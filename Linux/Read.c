#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	int fd = -1;
	ssize_t size = -1;
	char buf[10];
	char filename[] = "tmp.txt";
	fd = open(filename,O_RDONLY);
	if(fd == -1){
		printf("file is exist\n");
	}else{
		printf("Open success\n");
	}
	while(size){
		size = read(fd,buf,11);
		if(size == -1){
			close(fd);
			printf("read file error\n");
			return -1;
		}else{
			if(size > 0){
				printf("read %d byte:\n\"",(int)size);
				for(int i = 0;i < size;i ++)
					printf("%c",buf[i]);
				printf("\"\n");
			}else{
				puts("reach the end of file\n");
			}
		}
	}
    return 0;
}
