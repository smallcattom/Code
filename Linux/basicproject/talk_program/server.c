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
	int listsock = socket(AF_INET,SOCK_STREAM,0),complete;     
	struct sockaddr_in client,serve;
	fd_set rst;
	int maxfp1 , retval;
	struct timeval tv;
	char buffer[MAXLINE];

	ssize_t len;
	socklen_t length;
	bzero(&serve,sizeof(serve));
	serve.sin_family = AF_INET;
	serve.sin_port = htons(5001);
	serve.sin_addr.s_addr = htonl(0);

	bind(listsock,(struct sockaddr*)&serve,sizeof(serve));
	listen(listsock,2);
	for ( ; ; )
	{
		printf("wait for a new connection……\n");
		length = sizeof(client);
		complete = accept(listsock,(struct sockaddr *)&client,&length);
		if (complete == -1){
			perror("connect");
			continue;
		}
		puts("connect successfully!");

		while(1)
		{
			FD_ZERO(&rst);
			FD_SET(0,&rst);
			FD_SET(complete,&rst);
			maxfp1 = complete + 1;
			tv.tv_sec = 1;
			tv.tv_usec = 0;
			retval = select(maxfp1,&rst,NULL,NULL,&tv);
			if ( retval == -1){
				perror("select error");
				continue;
			}else if (retval == 0){
				continue;
			}else {
				if (FD_ISSET(complete,&rst)){
					bzero(buffer,sizeof(buffer));
					len = recv(complete,buffer,sizeof(buffer), 0 );
					if (len > 0){
						printf("client send information:\n%s",buffer);
					}else {
						if (len < 0)
							perror("send failure");
						else 
							puts("client exit");
						break;
					}
				}
				if (FD_ISSET(0,&rst)){
					fgets(buffer,sizeof(buffer),stdin);
					len = send(complete,buffer,sizeof(buffer), 0 );
					if (len > 0){
						puts("send successfully!");
					}else{
						perror("send:");
						break;
					}
				}
			}
		}
		close(complete);
	}
	close(listsock);
	return 0;
}
