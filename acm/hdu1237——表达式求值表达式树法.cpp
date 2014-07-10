#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
const int N = 3010;
using namespace std;
int lch[N],rch[N];char op[N];
double opn[N];
int nc;
bool isNum(char *s,int l,int r)
{
	for(int i = l;i < r; i++)
		if(!isdigit(s[i]))return 0;
	return 1;
}
double get(char *s,int l,int r)
{
	double sum = 0;
	for(int i = l;i < r;i ++)
	{
		sum *= 10;
		sum += s[i] - '0';
	}
	return sum;
}
int build(char *s,int x,int y)
{
	int  c1 = -1,c2 = -1,p = 0;
	int u;
	if(isNum(s,x,y))
	{
		u = ++nc;
		lch[u] = rch[u] = 0;opn[u] = get(s,x,y);
		return u;
	}
	for(int i = x;i < y;i ++)
	{
		switch(s[i])
		{
			case '(':p++;break;
			case ')':p--;break;
			case '+':case '-':if(!p) c1 = i;break;
			case '*':case '/':if(!p) c2 = i;break;
		}
	}
	if(c1 < 0)c1 = c2;
	if(c1 < 0)return build(s,x+1,y-1);
	u = ++nc;
	lch[u] = build(s,x,c1);
	rch[u] = build(s,c1+1,y);
	op[u] = s[c1];
	return u;
}
double cal(int rt)
{
	if(lch[rt] == 0&&rch[rt] == 0)
	return opn[rt];
	double a = cal(lch[rt]);
	double b = cal(rch[rt]);
	switch(op[rt])
	{
		case '+': return a + b;
		case '-':return a - b;
		case '/':return a/b;
		case '*':return a*b;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	char s[210];
	while(gets(s))
	{
		if(s[0] == '0'&&s[1] == '\0')break;
		int r = 0;
		for(int i = 0;s[i];i ++)
			if(s[i] != ' ')
				s[r++] = s[i];
		int l = 0;nc = 0;
		build(s,l,r);
		printf("%.2f\n",cal(1));
	}
	return 0;
}
	