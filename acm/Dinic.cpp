#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define INF 0x3f3f3f3f
const int N = 203;
using namespace std;
class Dinic
{
private:
  struct Edge
  {
    int v,c,next;
  }edge[N*N];
  int h[N],d[N],id, s, t;
  void addEdge(int u,int v,int c)
  {
    Edge e = {v,c,h[u]};
    edge[id] = e;
    h[u] = id++;
  }
  bool bfs()
  {
    queue<int>Q;Q.push(s);
    memset(d,-1,sizeof(d));
    d[s] = 0;
    while(!Q.empty())
    {
      int u = Q.front();Q.pop();
      for(int i = h[u];~i;i = edge[i].next)
      {
        int v = edge[i].v;
        if(edge[i].c && d[v] == -1)
        {
          d[v] = d[u] + 1;
          if(v == t)return 1;
          Q.push(v);
        }
      }
    }
    return 0;
  }
  int dfs(int u,int low = INF)
  {
    int c,ans = 0;
    if(u == t)return low;
    for(int i = h[u];~i;i = edge[i].next)
      if(edge[i].c && d[edge[i].v] == d[u] + 1)
      {
        c = dfs(edge[i].v,min(low - ans,edge[i].c));
        edge[i].c -= c;
        edge[i^1].c += c;
        ans += c;
        if(ans == low)break;
      }
    if(!ans)d[u] = -1;
    return ans;
  }
public:
  void init(int a,int b)
  {
    memset(h,-1,sizeof(h));
    id = 0;
    s = a;    t = b;
  } 
  void add(int u,int v,int c)
  {
    addEdge(u,v,c);
    addEdge(v,u,0);
  }
  int Ans()
  {
    int res = 0,c;
    while(bfs())
      res += dfs(s);
    return res;
  }
}cat;
int main()
{
   // freopen("in.txt","r",stdin);
    // ios::sync_with_stdio(0);
    int m, u, v,n,c;
    while(~scanf("%d%d",&m,&n))
    {
      cat.init(1,n);
      for(int i = 0;i < m;i ++)
      {
        scanf("%d%d%d",&u,&v,&c);
        cat.add(u,v,c);
      }
      printf("%d\n",cat.Ans());
    }
    return 0;
}