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
#include <pthread.h>
pthread_t ntid;
void printids(const char*s)
{
	pid_t pid;
	pthread_t tid;
	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
			(unsigned int)tid,(unsigned int)tid);
}
void  thr_fn(char *arg)
{
	printids(arg);
//	return ((void *)0);
//	return NULL;
}
int main()
{
	int err;
	char *str = "new thread: ";
	err = pthread_create(&ntid, NULL,(void*)thr_fn, (void*)str);
	if (err != 0)
		printf("can't create thread: %s\n", strerror(err));
	printids("main thread:");
	sleep(3);
	exit(0);
    return 0;
}
