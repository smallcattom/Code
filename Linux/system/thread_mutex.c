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
#define  MAXLINE 1000
#define  SA struct sockaddr
struct foo{
	int f_count;//记录引用数
	pthread_mutex_t f_lock;
};

struct foo* foo_alloc(void)  //函数用以分配对象
{
	struct foo *fp;

	if ((fp = malloc(sizeof(struct foo))) != NULL) {
		fp->f_count = 1;
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
			perror("mutex not init");
			free(fp);
			return NULL;
		}
	}
	return fp;

}
void foo_hold(struct foo * fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}
void foo_rele(struct foo* fp)
{
	pthread_mutex_lock(&fp->f_lock);
	if (--fp->f_count == 0) {
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}else {
		pthread_mutex_unlock(&fp->f_lock);
	}
}
int main()
{
	    
    return 0;
}
