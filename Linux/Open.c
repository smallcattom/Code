#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = -1;
	char filename[] = "test.txt";
	fd = open(filename,O_RDWR);
	if(fd == -1){
		printf("Open file %s failure,fd:%d\n",filename,fd);
	}else
	{
		printf("Open file success");
	}
	return 0;
}
