#include "threadpool.h"
#include <stdio.h>
void task1(int val)
{
	printf("{\n\tthread id: %u\n",(unsigned int)pthread_self());
	printf("\tTask1:hello cat %d\n}\n",val);
	return;
}
void task2()
{
	printf("{\n\tthread id: %u\n",(unsigned int)pthread_self());
	printf("\tTask2:hello dog\n}\n");
	return;
}
int main()
{
	Thread_Pool* thp = thread_init(4);
	int val = 30;
	int i;
	printf("add 6 task to thread pool\n");
	for(i = 0;i < 3;i ++)
	{
		push(thp,(void*)task1,(void*)val);
		push(thp,(void*)task2,NULL);
	}
	printf("clean thread pool\n");
	delete_ThreadPool(thp);
	return 0;
}
