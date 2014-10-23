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
#include <signal.h>
#define  MAXLINE 1000
#define  SA struct sockaddr
#define PAGER "${PAGER:-more}"
void sig_pipe(int signo)
{
	printf("SIGPIPE\n");
	exit(1);
}
int main(int argc,char *argv[])
{
	int 	n, fd1[2],fd2[2];
	pid_t pid;
	char line[MAXLINE];

	if (signal(SIGPIPE,sig_pipe) == SIG_ERR)
		perror("signal");
	pipe(fd1);
	pipe(fd2);

	if ((pid = fork()) == 0){
		close(fd1[1]);
		close(fd2[0]);
		if (fd1[0] != STDIN_FILENO) {
			if (dup2(fd1[0],STDIN_FILENO) != STDIN_FILENO)
				perror("dup2");
			close(fd1[0]);
		}
		if (fd2[1] != STDOUT_FILENO) {
			dup2(fd2[1],STDOUT_FILENO);
			close(fd2[1]);
		}
		if (execl("./add2","add2",(char*)0) < 0)
			perror("error");
	}else {
		close(fd1[0]);
		close(fd2[1]);
		while (fgets(line,MAXLINE,stdin) != NULL){
			n = strlen(line);
			write(fd1[1],line,n);
			n = read(fd2[0],line,MAXLINE);
			line[n] = '\0';
			fputs(line,stdout);
		}
	}
	exit(0);
}
