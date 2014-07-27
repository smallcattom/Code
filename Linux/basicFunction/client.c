#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define MAXLINE 101
#define SA struct sockaddr
int main(int argc,char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;
	if(argc != 2){
		puts("usage:a.out ipaddress");
	}

	if( (sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		puts("socket error");

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port  = htons(13);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		printf("inet_pton error for %s",argv[1]);

	if (connect(sockfd, (SA*) &servaddr, sizeof(servaddr)) < 0)
		puts("connect error");

	while( (n = read(sockfd,recvline,MAXLINE)) > 0){
		recvline[n] = 0;
		if(fputs(recvline, stdout) == EOF)
			puts("fputs error");
	}
	if (n < 0)
		puts("read error");

    return 0;
}

