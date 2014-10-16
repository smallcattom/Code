#include <stdio.h>
#include <string.h>
#include <mcheck.h>// mtrace 所在头文件
void get(char **p,int num)
{
	*p = (char*)malloc(sizeof(char)*num);
}
/*
 * 需要在shell终端设置环境变量MALLOC_TRACE=/home/userid/output
 * 用于定位输出文件位置
 * gcc file.c -g   生成可执行文件a.out
 * mtrace a.out output 会输出泄露在代码第几行，具体信息输出到文件output
 */
int main()
{
   char *p = NULL;
   mtrace();//开始追踪
   get(&p,100);
   muntrace();//停止追踪
    return 0;
}
