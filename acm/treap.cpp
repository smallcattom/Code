#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>
const int N = 10010;
struct node
{
    int l,r;
    int val,w;
};
class Treap
{
public:
    node p[N];
    int size,root;
      Treap(){
        srand(time(0));
        size = -1;
        root = -1;
    }
    void rl(int &x){int y = p[x].r;p[x].r = p[y].l;p[y].l = x;x = y;}
    void rr(int &x){int y = p[x].l;p[x].l = p[y].r;p[y].r = x;x = y;}
    void insert(int &x,int key){
            if(x == -1){
                x = ++size; p[x].l = p[x].r= -1;
                p[x].val = key; p[x].w = rand();
            }else if(key < p[x].val){
                insert(p[x].l,key);
                if(p[p[x].l].w < p[x].w)rr(x);
            }
            else{
                insert(p[x].r,key);
                if(p[p[x].r].w < p[x].w)rl(x);
            }
        }
    void remove(int &k,int val){
        if(k == -1)return;
        if(val < p[k].val)
            remove(p[k].l,val);
        else if(val > p[k].val)
            remove(p[k].r,val);
        else{
            if(p[k].l - p[k].r == 0)
                k = -1;
            else if(p[k].l == -1)
                k = p[k].r;
            else if(p[k].r == -1)
                k = p[k].l;
            else if(p[p[k].l].w < p[p[k].r].w){rl(k);remove(p[k].l,val);}
            else {rr(k); remove(p[k].r,val);}
        }
    }           
    bool find(int rt,int val)
    {
        if(rt == -1)return 0;
        if(val == p[rt].val)return 1;
        else if(val < p[rt].val)return find(p[rt].l,val);
        else return find(p[rt].r,val);
    }
    void print(int k)
    {
        if(k == -1)return;
        if(p[k].l != -1)print(p[k].l);
        printf("val:%d w:%d\n",p[k].val,p[k].w);
        if(p[k].r != -1)
            print(p[k].r);
    }
}Tre;
int main()
{
    srand(time(NULL));
    puts("hello");
    int x = -1;
    for(int i = 0;i < 5;i ++)
       Tre.insert(x,i); 
    Tre.remove(x,3);
    Tre.print(x);
    Tre.insert(x,3);
    Tre.print(x);
    for(int i = 0;i < 5;i ++)
        if(Tre.find(x,i))puts("Yes");
        else puts("NO");
    return 0;
}
