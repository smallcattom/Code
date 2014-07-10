#include <cstdio>
typedef long long ll;
using namespace std;
int mod = 1000000000;
ll exgcd(ll a,ll b,ll &x,ll &y)
{
  if(b == 0)
  {
    x = 1;
    y = 0;
    return a;
  }
  ll t = exgcd(b,a%b,x,y);
  ll d = x;
  x = y;
  y = d - a/b*y;
  return t;
}
bool solve(ll &m1,ll &a1,ll m2,ll a2)
{
  ll x,y;
  ll c = a2 - a1;
  ll d = exgcd(m1,m2,x,y);
  if(c%d)
    return 0;
  x *= c/d;
  x %= m2/d;//get value of k1

  a1 = a1 + x*m1;//get value of X
  m1 *= m2/d;
  a1 %= m1;
  if(a1 < 0)a1 += m1;
  return 1;
}
void work(int n)
{
  ll m1,a1;m1 = 1;a1 = 0;
  bool f = 1;
  for(int i = 0;i < n;i ++)
  {
    ll a2,m2;
    cin >> m2 >> a2;
    if(solve(m1,a1,m2,a2) == 0)
      {f = 0;}
  }
  if(f)cout<<(a1%m1 + m1)%m1<<endl;
  else puts("-1");
}
int main()
{
   freopen("in.txt","r",stdin);
   int n;
   while(cin >> n)
   work(n);
    return 0;
}
