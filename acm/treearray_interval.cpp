#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<cmath>
#include<set>

#define mp make_pair
#define pb push_back

using namespace std;

typedef long long big;

const int N=4002000;
struct TR
{
	int n;
	big a[N],b[N];
	void add(int x,big c)
	{
		int i;
		for(i=x;i<=n;i+=i&(-i))
			a[i]+=x*c;
		for(i=x;i<=n;i+=i&(-i))
			b[i]+=c;
	}
	void ADD(int l,int r,big c)
	{
		add(r,c);
		if(l>1)add(l-1,-c);
	}
	big get(int x)
	{
		big s1=0,s2=0;
		int i;
		for(i=x;i;i-=i&(-i))
			s1+=a[i];
		for(i=n;i;i-=i&(-i))
			s2+=b[i];
		for(i=x;i;i-=i&(-i))
			s2-=b[i];
		return s1+s2*x;
	}
	big GET(int l,int r)
	{
		return get(r)-get(l-1);
	}
}tx,ty;
int n,m,w;
int main()
{
	int i,op,x1,x2,y1,y2,c;
	big all=0;
	scanf("%d%d%d",&n,&m,&w);
	tx.n=n;
	ty.n=m;
	while(w--)
	{
		scanf("%d",&op);
		if(!op)
		{
			scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&c);
			all+=1ll*(y2-y1+1)*(x2-x1+1)*c;
			tx.ADD(x1,x2,1ll*c*(y2-y1+1));
			ty.ADD(y1,y2,1ll*c*(x2-x1+1));
		}
		else
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			printf("%I64d\n",tx.GET(x1,x2)+ty.GET(y1,y2)-all);
		}
	}
}
