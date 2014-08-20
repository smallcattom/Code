#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAXLINE 1024
#define  SA struct sockaddr
#define LISTENQ 1024
/*
struct in_addr {
	in_addr_t s_addr;
};

struct sockaddr_in {
	uint8_t sin_len;
	sa_family_t sin_family;
	in_port_t sin_port;

	struct in_addr sin_addr;

	char  sin_zero[8];
};
 */
void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];
again:
	while ( (n = read(sockfd, buf, MAXLINE)) > 0)
		write(sockfd, buf, n);

	if (n < 0 && errno == EINTR)
		goto again;
	else if(n < 0)
		perror("str_echo: read error");
}
int main()
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	listenfd = socket(AF_INET,SOCK_STREAM, 0);
	bzero(&servaddr,sizeof(servaddr));
 	servaddr.sin_family = AF_INET;	
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(9877);
	bind(listenfd, (SA*) &servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);
	for(; ;)
	{
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (SA *) &cliaddr, &clilen);
		if ( (childpid = fork()) == 0){
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
    return 0;
}
