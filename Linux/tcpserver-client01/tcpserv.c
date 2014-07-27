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
//#include <unp.h>
#define MAXLINE 1024
#define  SA struct sockaddr
#define LISTENQ 1024
//void err_sys(const char *fmt, ...)
//{
//	va_list ap;
//	char buf[MAXLINE];
//	va_start(ap, fmt);
//	vsprintf(buf,fmt,ap);
//	va_end(ap);
//	exit(1);
//}
void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];
again:
	while ( (n = read(sockfd, buf, MAXLINE)) > 0)
		Writen(sockfd, buf, n);

	if (n < 0 && errno == EINTR)
		goto again;
	else if(n < 0)
		err_sys("str_echo: read error");
}
int main()
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	listenfd = Socket(AF_INET,SOCK_STREAM, 0);
	bzero(&servaddr,sizeof(servaddr));
 	servaddr.sin_family = AF_INET;	
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(9877);
	Bind(listenfd, (SA*) &servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);
	for(; ;)
	{
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
		if( (childpid = Fork())){
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		Close(connfd);
	}
    return 0;
}
