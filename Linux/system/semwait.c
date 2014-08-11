#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#define LEN 1001
sem_t t;
void *th_fun(void *buf)
{
	char *s =(char*) buf;
	//信号量为0所以线程被阻塞
	sem_wait(&t);
	while(strcmp("bye",s))
	{
		int i;
		for(i = 0;s[i];i ++){
			printf("%d\n",s[i]);
		}
		sem_wait(&t);
	}
}
void readline(char *buf,int len)
{
	int i = 0;
	char ch;
	for(;(ch = getchar()) != '\n';)
	{
		if(i < len)buf[i++] = ch;
	}
	buf[i] = '\0';
}
int main()
{
	pthread_t pd;
	char str[LEN] = {'\0'};
	//初始化信号量为0
	sem_init(&t,0,0);
	int err = pthread_create(&pd,NULL,th_fun,str);
	if(err){
		perror("failure");
		exit(1);
	}
	while(strcmp("bye",str))	
	{
		readline(str,LEN);
		//读取一行后信号量加1
		sem_post(&t);
	}
	sem_destroy(&t);
	return 0;
}
