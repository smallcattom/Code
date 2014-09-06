#include <sys/types.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#define  MAXLINE 1000
#define  SA struct sockaddr
static void chara(char *str)
{
	char *ptr;
	int  c;
	setbuf(stdout,NULL);
	for (ptr = str;(c = *ptr++) != 0;)
		putc(c,stdout);
}
int pfd1[2],pfd2[2];
void TELL_WAIT(void)
{
	if (pipe(pfd1) < 0 || pipe(pfd2) < 0)
		perror("pipe");
}
void TELL_PARENT(pid_t pid)
{
	if (write(pfd2[1],"c", 1) != 1)
		perror("write");
}
void WAIT_PARENT(void)
{
	char 	c;

	if (read(pfd1[0], &c, 1) != 1)
		perror("read error");
	if (c != 'p')
		perror("WAIT_PARRENT");
}
void TELL_CHILD(pid_t pid)
{
	if (write(pfd1[1], "p", 1) != 1)
		perror("write");
}
void WAIT_CHILD(void)
{
	char	c;
	if (read(pfd2[0], &c, 1) != 1)
		perror("read");
	if (c != 'c')
		perror("WAIT_CHILD");
}
int main(int argc,char *argv[])
{
	pid_t pid;
	TELL_WAIT();

	if ((pid = fork()) < 0){
		perror("fork");
	}else if (pid == 0){
		TELL_PARENT(getppid());
		WAIT_PARENT();
		chara("output from child\n");
	}else{
		chara("output from parent\n");
		TELL_CHILD(pid);
	}
	exit(0);
}
