#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
#include<functional>
using namespace std;
#define bit(x, i) ((x)>>(i)&1)
// 13C
#define DBG 0
#define sz(c) ((int)(c).size())
#define   forl(i, a, b) for(int i = (a); i <  (b); ++i)
#define  forle(i, a, b) for(int i = (a); i <= (b); ++i)
#define   forg(i, a, b) for(int i = (a); i >  (b); --i)
#define  forge(i, a, b) for(int i = (a); i >= (b); --i)
#define  forlc(i, a, b) for(int i##_b = (b), i = (a); i <  i##_b; ++i)
#define forlec(i, a, b) for(int i##_b = (b), i = (a); i <= i##_b; ++i)
#define  forgc(i, a, b) for(int i##_b = (b), i = (a); i >  i##_b; --i)
#define forgec(i, a, b) for(int i##_b = (b), i = (a); i >= i##_b; --i)
#define forall(i, v   ) forlc(i, 0,   sz(v))
#define forlla(i, v   ) forge(i, sz(v)-1, 0)
#define  forls(i, n, a, b) for(int i = a; i != b; i = n[i])
#define rep(n)  for(int               repp = 0; repp <    (n); ++repp)
#define repc(n) for(int repp_b = (n), repp = 0; repp < repp_b; ++repp)
#define rst(a, v) memset(a, v, sizeof a)
#define cpy(a, b) memcpy(a, b, sizeof a)
#define rstn(a, v, n) memset(a, v, (n)*sizeof((a)[0]))
#define cpyn(a, b, n) memcpy(a, b, (n)*sizeof((a)[0]))
#define pr(x) #x"=" << (x) << " | "
#define dout  DBG && cerr << __LINE__ << ">>| "
#define mk(x) DBG && cerr << __LINE__ << "**| "#x << endl
#define dlist(args...) DBG && (dout << #args", = ", (void)(dbgr, args), cerr << " |" << endl)
#define ast(b) if(DBG && !(b)) { fprintf(stderr, "%d!!|\n", __LINE__); while(1) getchar(); }
#define pra(arr, a, b) if(DBG) { \
    dout<<#arr"[] | "; \
    forlec(i, a, b) cerr<<"["<<i<<"]="<<arr[i]<<" |"<<((i-(a)+1)%13?" ":"\n"); \
    if(((b)-(a)+1)%13) cerr<<endl; \
  }
#define rd(type, x) type x; cin >> x
inline int     rdi() { int d; scanf("%d", &d); return d; }
inline char    rdc() { scanf(" "); return getchar(); }
inline string  rds() { rd(string, s); return s; }
inline double rddb() { double d; scanf("%lf", &d); return d; }
template<class T> inline bool setmin(T& a, T b) { return a>b? a=b, true: false; }
template<class T> inline bool setmax(T& a, T b) { return a<b? a=b, true: false; }
struct debugger { template<typename T> debugger& operator , (const T& x) { cerr << x << ","; return *this; } } dbgr;

const int S = 128, N = 65536, inf = 0x3f3f3f3f;

int q, d, a[N][5];
map<int, int, less<int>    > mn[S];
map<int, int, less<int>    >::iterator mnit;
map<int, int, greater<int> > mx[S];
map<int, int, greater<int> >::iterator mxit; 

int pnt_val(int i, int mask) {
  int sum = 0;
  forl(j, 0, d) sum += (bit(mask, j)?+1:-1)*a[i][j];
  return sum;
}

int main() {
  while(scanf("%d %d", &q, &d) == 2) {
    forlc(i, 0, 1<<d) mn[i].clear(), mx[i].clear();
    forle(i, 1, q) {
      int ans = -inf, op; scanf("%d", &op);
      if(!op) {
        forl(j, 0, d) scanf("%d", a[i]+j);
        forlc(m, 0, 1<<d) {
          int val = pnt_val(i, m);
          ++mn[m][val];
          ++mx[m][val];
          setmax(ans, mx[m].begin()->first-mn[m].begin()->first);
        }
      }
      else {
        int i; scanf("%d", &i);
        forlc(m, 0, 1<<d) {
          int val = pnt_val(i, m);
          mnit = mn[m].find(val);
          mxit = mx[m].find(val);
          if(!--mnit->second) mn[m].erase(mnit);
          if(!--mxit->second) mx[m].erase(mxit);
          if(sz(mx[m])) setmax(ans, mx[m].begin()->first-mn[m].begin()->first);
        }
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}