#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#define INF 0x3f3f3f3f
const int N = 3010;
using namespace std;
double inline sqr(double x){return x*x;}
struct Point
{
  double x,y,s;
  double get(const Point &a)const
  {
    return sqrt(sqr(a.x - x) + sqr(a.y - y));
  }
  void input(){
    scanf("%lf%lf",&x,&y);
  }
}rec[N],umbre[N];
bool mp[N][N],vis[N];
int dx[N],dy[N],xlink[N],ylink[N],dis;
bool dfs(int u,int m)
{
    for(int v = 1;v <= m;v ++)
    if(mp[u][v] && !vis[v])
    {
      vis[v] = 1;
      if(ylink[v] != -1 && dy[v] == dis)continue;
      if(ylink[v] == -1 || dfs(ylink[v],m))
      {
        xlink[u] = v;
        ylink[v] = u;
        return true;
      }
    }
    return false;
}
bool bfs(int n,int m)
{
  queue<int>Q;
  memset(dx,-1,sizeof(dx));
  memset(dy,-1,sizeof(dy));
  dis = INF;
  for(int i = 1;i <= n;i ++)
    if(xlink[i] == -1)
    {
      Q.push(i);
      dx[i] = 0;
    }
    while(!Q.empty())
    {
      int u = Q.front();Q.pop();
      if(dx[u] > dis)break;
      for(int i = 1;i <= m;i ++)
      {
        if(mp[u][i] && dy[i] == -1)
        {
          dy[i] = dx[u] + 1;
          if(ylink[i] == -1)dis = dy[i];
          else 
          {
            dx[ylink[i]] = dy[i] + 1;
            Q.push(ylink[i]);
          }
        }
      }
    }
    return dis != INF;
}
int MaxMatch(int n,int m)
{
  int ans = 0;
  while(bfs(n,m))
  {
    memset(vis,0,sizeof(vis));
    for(int i = 1;i <= n;i ++)
      if(xlink[i] == -1){
        ans += dfs(i,m);
      }
  }
  return ans;
}
int main()
{
    freopen("in.txt","r",stdin);
    // ios::sync_with_stdio(0);
    int T, n, cas = 1,m,t;
    scanf("%d",&T);
    while(T --)
    {
      printf("Scenario #%d:\n",cas++);
      scanf("%d%d",&t,&n);
      memset(mp,0,sizeof(mp));

       for(int i = 1;i <= n;i ++)
      {
        rec[i].input();
        scanf("%lf",&rec[i].s);
      }
      scanf("%d",&m);
      for(int i = 1;i <= m;i ++)
        umbre[i].input();
      for(int i = 1;i <= n;i ++)
        for(int j = 1;j <= m;j ++)
        {
          if(rec[i].get(umbre[j]) <= t*rec[i].s)
            mp[i][j] = 1;
        }   
        memset(xlink,-1,sizeof(xlink));
        memset(ylink,-1,sizeof(ylink));  
      printf("%d\n\n",MaxMatch(n,m));
    }
    return 0;
}