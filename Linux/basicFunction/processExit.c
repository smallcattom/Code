#include <stdio.h>
#include <stdlib.h>
void func1(void)
{
	printf("func1\n");
}

void func2(void)
{
	printf("func2\n");
}
void test()
{
	atexit(func1);//不论在哪里注册都是推出主函数后才调用
}
int main()
{
  /*
   * atexit 由exit函数调用，即在main函数执行完后调用，
   * 而且根据注册的逆序调用，最多注册32个函数，并且重复注册重复执行。
   *
   *
   */
	test();
	if ( atexit(func2) != 0)perror("func2 can't register");
	if ( atexit(func2) != 0)perror("func2 can't register");
	if ( atexit(func1) != 0)perror("func1 can't register");
	printf("main end\n");
    return 0;
}
