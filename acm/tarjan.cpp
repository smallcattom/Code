struct edge
{
    int u,v,next;
}g[M];
int h[N],eg, n;
int st[N],top,dfn[N],tn,low[N];
bool vis[N];
int id[N],ssc;
void init()
{
    memset(h,-1,sizeof(h));
    eg = 0;
}
void add(int u,int v)
{
     edge e = {u,v,h[u]};
    g[eg] = e;
    h[u] = eg++;
}
void dfs(int u,int fa)
{
    st[++top] = u;
    vis[u] = 1;
    dfn[u] = low[u] = ++tn;
    bool f = true;
    for(int i = h[u];~i;i = g[i].next)
    {
        int v = g[i].v;
       // if( v == fa && f){f = 0;continue;}  used in indirected graph
        if(!dfn[v])
        {
            dfs(v,u);
            low[u] = min(low[u],low[v]);
        }else if(vis[v])low[u] = min(low[u],dfn[v]);
    }

    if(low[u] == dfn[u])
    {
        ssc ++;
        int v;
        do
        {
            v = st[top--];
            vis[v] = 0;
            id[v] = ssc;
        }while(u != v);
    }
}

void tarjan()
{
    memset(vis,0,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    tn = ssc = 0;top = -1;
    for(int i = 1;i <= n;i ++)
    if(!dfn[i])dfs(i,-1);
}
void build()
{
    int tot = eg;
    init();
    for(int i = 0;i < tot;i++ )
    {
        int u = g[i].u,v = g[i].v;
        if(id[u] != id[v])add(id[u],id[v]);//printf("%d %d\n",id[u],id[v]);
    }
}