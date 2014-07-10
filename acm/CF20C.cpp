#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;
typedef pair<long long,int> pii;
const long long INF = 1e18;
vector<vector<int> > g,w;
vector<long long> d;
vector<int> p,ans;
priority_queue<pii,vector<pii>, greater<pii> > q;
int n,m;
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&n,&m);
	g.resize(n+1);
	w.resize(n+1);
	for (int i=0; i<m; i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		a;b;
		g[a].push_back(b);
		g[b].push_back(a);
		w[a].push_back(c);
		w[b].push_back(c);
	}
	d.resize(n+1,INF);
	p.resize(n+1);
	d[1]=0;
	p[1]=-1;
	q.push(pii(0,1));
	while (!q.empty())
	{
		int v=q.top().second;
		int cur_d=q.top().first;
		q.pop();
		if (d[v] < cur_d)continue;
		for (int i=0; i<g[v].size(); i++)
		{
			int u=g[v][i];
			if (d[u]>d[v]+w[v][i])
			{
				d[u]=d[v]+w[v][i];
				p[u]=v;
				q.push(pii(d[u],u));
			}
		}
	}
	if (d[n]==INF)
	{
		printf("-1\n");
		return 0;
	}
	for (int i=n; i!=-1; i=p[i])
		ans.push_back(i);
	for (int i=ans.size()-1; i>=0; i--)
		printf("%d ",ans[i]);
	printf("\n");
	return 0;
}