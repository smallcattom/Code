#include <sys/types.h>
#include <errno.h>
#include <signal.h>
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
int main(int argc,char *argv[])
{
	int 	sockfd = socket(AF_INET,SOCK_STREAM,0);
	socklen_t	len;
	size_t	block_len;
	int		complete;
	ssize_t send_l,recv_l;
	struct sockaddr_in	serv,cli;
	char buf[MAXLINE];
	char filename[100];
	FILE *fp;
	bzero(&serv,sizeof(serv));
	serv.sin_family = AF_INET;

	if (argv[1] == NULL)
		argv[1] = "5001";

	serv.sin_port = htons(atoi(argv[1]));
	serv.sin_addr.s_addr = htonl(0);

	bind(sockfd,(SA*)&serv,sizeof(serv));
	listen(sockfd,2);
//	for( ; ; )
	{
		len = sizeof(cli);
		complete = accept(sockfd,(SA*)&cli,&len);
		//发送文件名列表
		fp = popen("ls","r");
		while( fgets(buf,MAXLINE,fp) != NULL)
		{
			send(complete,buf,strlen(buf),0);
		}
		strcpy(buf,"input file name\n");
		send(complete,buf, strlen(buf),0);
		puts("send list success");
		pclose(fp);
//exit(0);		
		//获取文件名
		while( (recv_l = recv(complete,filename,sizeof(filename),0) ) > 0)
		{
			filename[recv_l] = '\0';
			if ((fp = fopen(filename,"rb")) == NULL)
			{
				strcpy(buf,"filename error please input again");
				puts("filename error");
				send(complete,buf,strlen(buf),0);
			}else{
				puts("get filename success");
				break;
			}
		}
		//文件名对了
		strcpy(buf,"success");
		send(complete,buf,strlen(buf),0);
		puts("get correct filename");
		//传文件

		while((block_len = fread(buf,sizeof(char),MAXLINE,fp)) > 0)
		{
			if (send(complete, buf,block_len,0) < 0)
			{
				perror("send");
				exit(1);
			}
		}
		printf("%s Tranfer finished\n",filename);
		fclose(fp);
		close(complete);
	}
	return 0;
}
