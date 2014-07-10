#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <queue>
#define INF 0x3f3f3f3f
const int N = 203;
using namespace std;
int ax[N],ay[N],bx[N],by[N];
int ia,ib,id;
struct Edge
{
  int u,v,cost,cap,flow,next;
}edge[N*N];
int head[N];
void addEdge(int u,int v,int cost,int cap,int flow)
{
  Edge e = {u,v,cost,cap,flow,head[u]};
  edge[id] = e;
  head[u] = id++;
}
void add(int u,int v,int cost,int cap)
{
  addEdge(u,v,cost,cap,0);
  addEdge(v,u,-cost,0,0);
}
void input(int n, int m)
{
  id = 0;ia= ib = 0;
  getchar();
  for(int i = 0;i < n;i ++)
  {
    for(int j = 0;j < m;j ++)
    {
      char ch;
      scanf("%c",&ch);
      if(ch == 'H')
      {
        bx[++ib] = i;
        by[ib] = j;
      }else if(ch == 'm')
      {
        ax[++ia] = i;
        ay[ia] = j;
      }
    }
    getchar();
  }   
}
bool vis[N];
int pre[N];
int dis[N];
int low[N];
bool spfa(int s,int t)
{
  memset(vis,0,sizeof(vis));
  memset(pre,-1,sizeof(pre));
  memset(dis,INF,sizeof(dis));
  vis[s] = 1;
  dis[s] = 0;
  low[s] = INF;
  queue<int>Q;
  Q.push(s);
  while(!Q.empty())
  {
    int u = Q.front();
    Q.pop();
    vis[u] = 0;
    for(int i = head[u];~i;i = edge[i].next)
    {
      int v = edge[i].v,cost = edge[i].cost,cap = edge[i].cap,flow = edge[i].flow;
      if(flow < cap && dis[u] + cost < dis[v])
      {
        dis[v] = dis[u] + cost;
        pre[v] = i;
        low[v] = min(low[u],cap-flow);
        if(!vis[v])
        {
          vis[v] = 1;
          Q.push(v);
        }
      }
    }
  }
  return dis[t] != INF;
}
void mcmf(int s,int t)
{
  int cost = 0;
  while(spfa(s,t))
  {
    int x = pre[t];
    cost += low[t]*dis[t];
    while(~x){
      edge[x].flow += low[t];
      edge[x^1].flow -= low[t];
      x = pre[edge[x].u];
    }
  }
  printf("%d\n",cost);
}
int main()
{
    freopen("in.txt","r",stdin);
    // ios::sync_with_stdio(0);
    int n, m;
    while(~scanf("%d%d",&n,&m))
    {
      if(n == 0&&m == 0)break;
       input(n,m);
       memset(head,-1,sizeof(head));
       // build graph
       int st = 0,en = ia + ib + 1;
       for(int i = 1;i <= ia;i ++)
          add(st,i,0,1);
       for(int i = 1;i <= ib;i ++)
          add(i+ia,en,0,1);
       for(int i = 1;i <= ia;i ++)
        for(int j = 1;j <= ib;j ++)
          add(i,j + ia,abs(ax[i] - bx[j]) + abs(ay[i] - by[j]),1);
      // get min cost max flow
       mcmf(st,en);
    }
    return 0;
}
