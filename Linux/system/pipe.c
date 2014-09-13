#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define  MAXLINE 1000
#define  SA struct sockaddr
void server(int readfd,int writefd)
{
	int 	fd;
	ssize_t n;
	char buf[MAXLINE];
	
	if ( (n = read(readfd, buf, MAXLINE)) == 0){
		perror("end file");
		exit(0);
	}
	buf[n] = '\0';

	if ( (fd = open(buf, O_RDONLY)) < 0){
		snprintf(buf + n,sizeof(buf) - n,":can't open, %s\n",strerror(errno));
		n = strlen(buf);
		write(writefd, buf, n);
	}else {
		while ( (n = read(fd, buf, MAXLINE)) > 0)
			write(writefd, buf, n);
		close(fd);
	}
}
void client(int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	char buf[MAXLINE];

	fgets(buf,MAXLINE, stdin);
	len = strlen(buf);
	if (buf[len-1] == '\n')
		len--;

	write(writefd,buf, len);

	while(( n = read(readfd, buf, MAXLINE)) > 0)
		write(STDOUT_FILENO, buf, n);
}
int main()
{
   	int pipe1[2],pipe2[2];
	pid_t child;
	pipe(pipe1);
	pipe(pipe2);
	if ( (child = fork()) == 0){
		close(pipe1[1]);
		close(pipe2[0]);

		server(pipe1[0], pipe2[1]);
		exit(0);
	}
	close(pipe1[0]);
	close(pipe2[1]);

	client(pipe2[0],pipe1[1]);

	waitpid(child, NULL, 0);
	exit(0);
    return 0;
}
