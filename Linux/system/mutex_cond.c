#include <pthread.h>
#include <stdio.h>
int count;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cod = PTHREAD_COND_INITIALIZER;
void fun()
{
	pthread_mutex_lock(&mutex);
	printf("count:%d\n",count);
	pthread_cond_wait(&cod,&mutex);
	count++;
	printf("1 thread id:%u   %d\n",(unsigned int)pthread_self(), count);
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}
int main()
{
	pthread_t pd;
	count = 0;
	pthread_create(&pd,NULL,(void*)fun,NULL);
	sleep(1);
	printf("2 thread %u  count: %d\n",(unsigned int)pthread_self(), count);
	pthread_cond_signal(&cod);
	sleep(1);
	printf("3 thread %u  count: %d\n",(unsigned int)pthread_self(), count);
	pthread_join(pd,NULL);
	return 0;
}
