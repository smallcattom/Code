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
	int 					sockfd = socket(AF_INET,SOCK_STREAM,0);    
	int 					complete;
	struct 					sockaddr_in cli;
	ssize_t 				recv_l;
	socklen_t				len; 
	FILE* 					fp;
	char					buf[MAXLINE];
	char 					filename[MAXLINE];
	cli.sin_family = AF_INET;
	cli.sin_port = htons(5001);
	inet_pton(AF_INET,"172.16.41.222",&cli.sin_addr.s_addr);
	bind(sockfd,(struct sockaddr*)&cli,sizeof(cli));
	if(connect(sockfd,(struct sockaddr*)&cli,sizeof(cli)) == -1){
		perror("connect");
		close(sockfd);
		exit(1);
	}
	
	recv_l = recv(sockfd,filename,MAXLINE,0);
	if (recv_l < 0){
		perror("recv");
		close(sockfd);
		exit(1);
	}
	filename[recv_l] = '\0';
	if( (fp = fopen(filename,"wb+") ) == NULL){
		perror("open file");
		exit(1);
	}
	while((recv_l = recv(sockfd,buf,sizeof(buf),0)) )
	{
		if( recv_l < 0){
			perror("recv");
			exit(1);
		}
		fwrite(buf,sizeof(char),recv_l,fp);
	}
	fclose(fp);
	close(sockfd);
	return 0;
}
