# include <stdio.h>
# include <stdlib.h>
# include <time.h>


# define M 4
# define G 200


double Pc = 1.0 ;
double Pm = 1.0 ;
/*
* Pc：交叉发生的概率
* Pm：变异发生的概率
* M：种群规模
* G：终止进化的代数
*/

int n, ans ;
int g[30][30] ;


int Pop[M], newPop[M], F[M] ;


int Value(int x) //适应度函数 
{
    int i, j, rtn = 0 ;
    for (i = 0 ; i < n ; i++)
        for(j = i+1 ; j< n ; j++)
            if (((x>>i)&1) !=((x>>j)&1)) rtn += g[i][j] ;
    if (rtn > ans) ans = rtn ;
    return rtn ;
}


double random_0_1() //生成0-1之间的一个随机数 
{
    return rand()*1.0 / RAND_MAX ;
}


int Choose()
{
    int i, sum = 0 ;
    double r = random_0_1(), m ;
    
    for (i = 0 ; i < M ; i++)
        sum += F[i] ;
    for (i = 0 ; i < M ; i++)
    {
        m += F[i]*1.0 / sum ;
        if (m>=r) return Pop[i] ;
    }
    return Pop[0] ;
}


void Cross(int *p1, int *p2)
{
    int pos = rand() % n + 1 ;
    int x1 = *p1, x2 = *p2 ;
    int tmp1 = x1 & ((1<<pos)-1), tmp2 = x2 & ((1<<pos)-1) ;
    
    x1 = ((x1>>pos)<<pos) | tmp2 ;
    x2 = ((x2>>pos)<<pos) | tmp1 ;
    
    *p1 = x1, *p2 = x2 ;
}


void Mutation (int *p)
{
    int pos = rand() % n ;
    *p = ((*p) ^ (1<<pos)) ;
}


int gao()
{
    int i, j, g, x1, x2 ;
    for (i = 0 ; i < M ; i++)
        Pop[i] = i ; //初始化，随意了 
    ans = 0 ;
    for(g = 0 ; g < G ; g++) //繁殖代数 
    {
    //    printf ("G = %d, ans = %d\n", g, ans) ;
        for(i = 0 ; i < M ; i++)
            F[i] = Value(Pop[i]) ;
        for (j = 0 ;j < M ; j+=2)
        {
            x1 = Choose(), x2 = Choose() ;
            if (random_0_1() < Pc)
            {
                Cross(&x1, &x2) ;
            }
            if (random_0_1() < Pm)
            {
                Mutation(&x1) ;
                Mutation(&x2) ;
            }
            //此处可以修改 
            newPop[j] = x1, newPop[j+1] = x2 ;
        }
        for (i = 0 ; i < M ; i++)
            if (Value (newPop[i]) > F[i])
                Pop[i] = newPop[i] ;
    }
    return ans ;
}


int dfs ()
{
    int i, buff ;
    ans = 0 ;
    for (i = 0 ; i < (1<<n) ; i++)
    {
        buff = Value(i) ;
        if (buff > ans) ans = buff ;
    }
    return ans ;
}


int main ()
{
    int i, j ;
    while (~scanf ("%d", &n))
    {
        for(i = 0 ; i < n ; i++)
            for(j = 0 ; j < n ;j++)
                scanf ("%d", &g[i][j]) ;
        if (n < 20) printf ("%d.\n", dfs()) ;
        else printf ("%d.\n", gao()) ;
    }
    return 0 ;
}