#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/msg.h>
#define  MAXLINE 1000
#define  SA struct sockaddr
struct msg_st
{
	long mtype;
	char text[MAXLINE];
};
int main()
{
// 	int running = 1;
//	int msgid;
//	struct msg_st data;
//	long mtype = 0;
//
//	msgid = msgget(1234,0666|IPC_CREAT);
	printf("%d",0666);

    return 0;
}
