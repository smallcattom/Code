#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
/*当正常返回的时候，waitpid返回收集到的子进程的进程ID； 
 如果设置了选项WNOHANG，而调用中waitpid发现没有已退出的子进程可收集，则返回0； 
 如果调用中出错，则返回-1，这时errno会被设置成相应的值以指示错误所在； */
int main()
{
	pid_t pc,pr;
	pc = fork();//对于子进程pc=0,对于父进程pc等于该进程子进程的pid
	if(pc == 0){
		sleep(5);
		exit(0);
	}

	while((pr = waitpid(pc,NULL,WNOHANG)) == 0){
		if(pr == 0){//没有已经退出的子进程收集
			printf("no child process exist!\n");
			sleep(1);
		}
	}
	if(pr == pc)
		printf("success get child %d\n",pr);	
    return 0;
}
