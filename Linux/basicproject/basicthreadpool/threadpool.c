#include "threadpool.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//线程存活标志
static int alive = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void thread_work_func(Thread_Pool *trp)
{
	while(alive)
	{
		if(sem_wait(&trp->info)){
			perror("thread_work_func");
			exit(1);
		}

		if(alive)
		{
			void* (*func)(void*);
			void *arg;
			Thread_Job* job;
			pthread_mutex_lock(&mutex);    //lock
				job = pop(trp);
			printf("job out thread id:%d\n",(int)pthread_self());
			func = job->func;
			arg = job->arg;
			pthread_mutex_unlock(&mutex);    //unlock
			printf("work Job in thread:%d\n",(int)pthread_self());
				func(arg);
			free(job);
		}else return;
	}
}
Thread_Job* pop(Thread_Pool *trp)
{
	trp->Job_num--;
	Thread_Job* ret = trp->Que;
	trp->Que = trp->Que->next;
	return ret;
}
void push(Thread_Pool *trp,void*(*func)(void*),void* arg)
{
	Thread_Job *job = (Thread_Job*)malloc(sizeof(Thread_Job));
	job->func = func;
	job->arg = arg;
	job->next = NULL;

	pthread_mutex_lock(&mutex);
	printf("all job number is %d\n",trp->Job_num);
	
	if(trp->Job_num == 0){
		trp->tail = trp->Que = job;
	}else{
		trp->tail->next = job;
		trp->tail = job;
	}
	trp->Job_num++;
	sem_post(&trp->info);
	pthread_mutex_unlock(&mutex);

}
Thread_Pool* thread_init(int Num)
{
	Thread_Pool *ret = (Thread_Pool*)malloc(sizeof(Thread_Pool));
	ret->thread = (pthread_t*)malloc(Num*(sizeof(pthread_t))); 
	ret->Job_num = 0;
	ret->numOfthread = Num;
	ret->tail = ret->Que = NULL;
	sem_init(&ret->info,0,0);
	int i;
	for(i = 0;i < Num;i ++)
	{
		printf("Created thread %d in pool \n", i);
		pthread_create(&(ret->thread[i]),NULL,(void*)thread_work_func,(void*)ret);
	}
	return ret;
}

void delete_ThreadPool(Thread_Pool *trp)
{
	int i = 0;
	alive = 0;
	//解除所有信号量阻塞
	for(;i < trp->numOfthread;i ++)
	{
		sem_post(&trp->info);
	}
	//释放信号量空间
	sem_destroy(&trp->info);
//等待所有正在运行的线程结束	
	for(i = 0;i < trp->numOfthread ;i ++)
		pthread_join(trp->thread[i],NULL);

	//释放线程池的线程
		free(trp->thread);
	//释放任务队列
	while(trp->Que){
		Thread_Job* cur = trp->Que;
		trp->Que= trp->Que->next;
		free(cur);
	}
	trp->tail = NULL;
	free(trp);
}
