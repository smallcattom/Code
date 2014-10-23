#include <sys/types.h>
#include <limits.h>
#include <errno.h>
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
#include <sys/stat.h>
#define  MAXLINE 1000
#define  SA struct sockaddr
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
void client(int,int),server(int,int);
int main(int argc,char *argv[])
{
	int		readfd, writefd;
	pid_t	childpid;

	if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))
		perror("exit");
	mkfifo(FIFO2,FILE_MODE);
	if ( (childpid = fork()) == 0){
		readfd = open(FIFO1, O_RDONLY, 0);
		writefd = open(FIFO2, O_WRONLY, 0);

		server(readfd, writefd);
		exit(0);
	}

	writefd = open(FIFO1, O_WRONLY, 0);
	readfd = open(FIFO2, O_RDONLY, 0);

	client(readfd, writefd);

	waitpid(childpid, NULL, 0);
	close(readfd);
	close(writefd);
	unlink(FIFO1);
	unlink(FIFO2);
	exit(0);
}
void server(int readfd,int writefd )
{
	int 	fd;
	ssize_t n;
	char	buff[MAXLINE];

	if ((n = read(readfd, buff, MAXLINE)) == 0)
		perror("read");

	buff[n] = '\0';

	if ( (fd = open(buff, O_RDONLY)) < 0){

		snprintf(buff + n, sizeof(buff) - n, ":can't open,%s\n",strerror(errno));
		n = strlen(buff);
		write(writefd, buff, n);
	}else {
		while ( ( n = read(fd, buff, MAXLINE)) > 0)
			write (writefd, buff, n);
		close(fd);
	}
}
void client(int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	char buf[MAXLINE];
	fgets(buf, MAXLINE, stdin);
	len = strlen(buf);
	if (buf[len - 1] == '\n')
		len--;

	write(writefd, buf, len);

	while( (n = read(readfd, buf, MAXLINE)) > 0)
		write(STDOUT_FILENO, buf, n);
}
