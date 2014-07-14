#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
char buffer[80];
/*　函数名: vsprintf
  功 能: 送格式化输出到串中
  返回值: 正常情况下返回生成字串的长度(除去\0),错误情况返回负值
  用 法: int vsprintf(char *string, char *format, va_list param);
  // 将param 按格式format写入字符串string中
  注: 该函数会出现内存溢出情况,建议使用vsnprintf
  */
int vspf(char *fmt, ...)
{
	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vsprintf(buffer, fmt, argptr);
	va_end(argptr);
	puts(buffer);
	return(cnt);
}
int main()
{
	int a = 1,b = 2;
	vspf("%d %d",a,b);    
    return 0;
}
