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
	off_t offset = -1;
	offset = lseek(STDIN_FILENO,0,SEEK_CUR);
	if(offset == -1){
		printf("STDIN can't seek\n");
	}else{
		printf("STDIN can seek\n");
	}
    return 0;
}
