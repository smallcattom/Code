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
   int input = 0;
   char buf[] = "welcome to Linux world and network";
   char filename[] = "test.txt";
   fd = open(filename,O_RDWR|O_CREAT);
   if(fd == -1){
	   puts("Open file failure");
   }else{
	   puts("Open success");
   }
   size = write(fd,buf,strlen(buf));
   printf("write %d bytes to file %s\n",size,filename);
   close(fd);
   return 0;
}
