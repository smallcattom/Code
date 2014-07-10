#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <bitset>
#include <vector>
using namespace std;
const int N = 3010;
typedef long long ll;
bitset<20000>rec[20000];
vector<int>id[17000];
int n;
void dfs(int c)
{
	int len = id[c].size();
	rec[c].set(c);
	for(int i = 0;i < len;i ++)
	{
		int x = id[c][i];
		if(rec[x].none())dfs(x);
		rec[c] |= rec[x];
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int m;
	scanf("%d%d",&n,&m);
	for(int i = 0;i < m;i ++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		id[l].push_back(r);
	}
	for(int i = 0;i < n;i ++)
		if(rec[i].none())//not find 0
			dfs(i);
		
	for(int i = 0;i < n;i ++)
		printf("%d\n",rec[i].count());//count(1)
	 return 0;	
}