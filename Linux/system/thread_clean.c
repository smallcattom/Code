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
void cleanup(void *arg)
{
	printf("cleanup: %s\n", (char*)arg);
}
void * thr_fn1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup,"thread 1 second handler");
	printf("thread 1 push complete\n");
	if (arg)
		return ((void*)1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return ((void*)1);
}
void * thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 push complete\n");
	if (arg)
		pthread_exit((void *)2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void*)2);
}
/*
 *如果线程是通过从它的启动例程中返回而终止的话，那么它的清理处理程序就不会被调用，清理处理程序是按照安装时相反的顺序调用的。
 * */
int main()
{
	int err;
	pthread_t tid1, tid2;
	void *tret;
	
	err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	if (err != 0)
		printf("can't create thread 1: %s\n", strerror(err));
	err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
	if (err != 0)
		printf("can't create thread 2: %s\n", strerror(err));
	err = pthread_join(tid1, &tret);
	if (err != 0)
		printf("can't join with thread 1: %s\n",strerror(err));
	printf("thread 1 exit code %d\n",(int)tret);
	err = pthread_join(tid2, &tret);
	if (err != 0)
		printf("can't join with thread 2: %s\n",strerror(err));
	printf("thread 2 exit code %d\n",(int)tret);
	exit(0);
}
