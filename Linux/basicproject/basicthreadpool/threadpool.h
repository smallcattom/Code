#ifndef _THREADPOOL_
#define _THREADPOOL_
#include <pthread.h>
#include <semaphore.h>
typedef struct Thread_Job
{
	struct	Thread_Job *next;
	void *(*func)(void*);
	void* arg;
}Thread_Job;
typedef struct Thread_Pool
{
	//用于互斥添加删除任务的操作
	pthread_mutex_t mutex;
	//线程队列
	pthread_t *thread;
	//线程总数
	int numOfthread;
	//任务总数
	int Job_num;
	sem_t info;
	//存储任务
	Thread_Job *Que;
	Thread_Job *tail;
}Thread_Pool;
Thread_Pool* thread_init(int Num);
void push(Thread_Pool *trp,void*(*func)(void*),void*arg);
Thread_Job* pop();
void thread_work_func(Thread_Pool *trp);
void delete_ThreadPool(Thread_Pool *trp);
#endif 


