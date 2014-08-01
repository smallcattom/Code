#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
int main()
{
	pid_t pc,pr;
	pc = fork();
	if(pc < 0)perror("sorry");
	else if( pc == 0){
		printf("This child process with pid of %d fa:%d\n",getpid(),getppid());
		sleep(1);
		exit(3);
	}else {
		int pd;
		pr = wait(&pd);
		if(WIFEXITED(pd))
		printf("%d\n",	WEXITSTATUS(pd));
		printf("current father process pid:%d\n",getpid());
		printf("catch a child process with pid of %d \n",pr);
	}
	
    return 0;
}
