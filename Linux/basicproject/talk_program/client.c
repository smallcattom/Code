#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define  MAXLINE 1000
#define  SA struct sockaddr

int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	char buffer[MAXLINE];
	struct sockaddr_in cli;
	fd_set rst;
	int bitNum;	
	ssize_t len;
	struct timeval tv;
	bzero(&cli,sizeof(cli));
	cli.sin_family = AF_INET;
	cli.sin_port = htons(5001);
	inet_pton(AF_INET,"127.0.0.1",(struct sockaddr*)&cli.sin_addr.s_addr);
	bind(sockfd,(struct sockaddr*)&cli,sizeof(cli));
	if(connect(sockfd,(struct sockaddr*)&cli,sizeof(cli)) != -1)
	puts("connect successfully!You can send information.");
	else return 0;
	while(1)
	{
		FD_ZERO(&rst);
		FD_SET(0,&rst);
		FD_SET(sockfd,&rst);
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		bitNum = select(sockfd + 1,&rst,NULL,NULL,&tv);
		if (bitNum == -1){
			perror("select");
			continue;
		}else if (bitNum == 0)
			continue;
		else{
			if (FD_ISSET(0,&rst)){
				fgets(buffer,MAXLINE,stdin);
				len = send(sockfd,buffer,MAXLINE,0);
				if (len < 0){
					perror("send");
					break;
				}else 
					puts("send successfully!");
			}

			if (FD_ISSET(sockfd,&rst)){
				len = recv(sockfd,buffer,MAXLINE,0);
				if (len > 0)
					printf("reveive information:\n%s",buffer);
				else {
					perror("recv");
				}
			}
		}
	}
	close(sockfd);
    return 0;
}
