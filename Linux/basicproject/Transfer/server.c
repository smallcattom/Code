#include <sys/types.h>
#include <time.h>
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

int main(int argc,char** argv)
{
	int 				sockfd = socket(AF_INET,SOCK_STREAM,0);
	int					complete;
	struct 				sockaddr_in serv,cli;
	socklen_t 			len;
	ssize_t 			send_l;
	char 				buf[MAXLINE];
	FILE*				fp = NULL;
	double s;
	if(argc < 2)return 0;
	bzero(&serv,sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(5001);
	serv.sin_addr.s_addr= htonl(0);
	bind(sockfd,(struct sockaddr*)&serv,sizeof(serv));

	listen(sockfd,2);
//	for(; ;)
	{
		len = sizeof(cli);
		complete = accept(sockfd,(struct sockaddr*)&cli,&len);
		s = clock();
		buf[0] = '\0';
		strcpy(buf,argv[1]);
		send_l = send(complete,buf,strlen(argv[1]),0);
		if (send_l < 0){
			perror("send file name");
			exit(1);
		}
		
		//send file content
		if ( (fp = fopen(argv[1],"rb") ) == NULL){
			printf("file not exist or open error!");
		}else{
			int block_len;
			while((block_len = fread(buf,sizeof(char),MAXLINE,fp)) > 0)
			{
				if (send(complete,buf,block_len,0) < 0){
					perror("send");
					exit(1);
				}
			}
			fclose(fp);
			printf("Tranfer finished!\n");
		}
		close(complete);
	}
	close(sockfd);
    return 0;
}
