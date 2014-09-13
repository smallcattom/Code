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
#define  MAXLINE  1001
#define  SA struct sockaddr
int main(int argc,char *argv[])
{
	int		sockfd = socket(AF_INET,SOCK_STREAM,0);
	int		complete;
	struct  sockaddr_in	cli;
	ssize_t	recv_l,send_l;
	size_t block_len;
	socklen_t	len;
	char buf[MAXLINE];
	char filename[MAXLINE];
	FILE *fp;
	bzero(&cli,sizeof(cli));
	cli.sin_family = AF_INET;
	if (argv[1] == NULL)
		argv[1] = "127.0.0.1";

	cli.sin_port = htons(5001);
	inet_pton(AF_INET,argv[1],&cli.sin_addr.s_addr);
	bind(sockfd,(struct sockaddr*)&cli,sizeof(cli));
	if (connect(sockfd,(SA*)&cli,sizeof(cli)) == -1)
	{
		perror("connect");
		close(sockfd);
		exit(1);
	}
	//接收文件名列表	
	while((recv_l = recv(sockfd,buf,sizeof(buf),0)) > 0)
	{
		buf[recv_l] = '\0';
		fputs(buf,stdout);
		if(strcmp(buf+recv_l-5,"name\n") == 0)
			break;
	}
//	exit(0);
	while(gets(filename) != NULL)
	{
		puts(filename);
		send_l  = send(sockfd,filename, strlen(filename),0);
		recv_l = recv(sockfd,buf, sizeof(buf),0);
		buf[recv_l] = '\0';
		puts(buf);
		if (strcmp(buf,"success") == 0)
			break;
		fputs(buf,stdout);
	}
	puts("filename send success");
	//接收文件
	if ((fp = fopen(filename,"wb")) == NULL)
	{
		perror("fopen");
		exit(1);
	}
	while((recv_l = recv(sockfd,buf,sizeof(buf),0)))
	{
		if (recv_l < 0){
			perror("recv");
			exit(1);
		}
		fwrite(buf,sizeof(char),recv_l,fp);
	}
	puts("file receive success");
	fclose(fp);
	close(sockfd);
	return 0;
}
