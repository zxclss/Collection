> 用树状数组动态维护区间
>
> 从前往后求出大于`a[i]`的数的个数，在从后往前求出大于`a[i]`的数的个数
>
> 两者相乘，就可以获得以`a[i]`为低端的 `V`型 出现的个数

```c++
#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;

const int N = 200010;

int n;
int a[N], tr[N];
int gt[N], lw[N];

int lowbit(int x)
{
    return x & -x;
}
void add(int x, int v)
{
    for (int i = x; i <= n; i += lowbit(i))
        tr[i] += v;
}
int query(int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        res += tr[i];
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    
    //求第i个数之前1~i-1个数中比a[i]小的数的个数，和比a[i]大的数的个数
    for (int i = 1; i <= n; ++i)
    {
        int &t = a[i];
        gt[i] = query(n) - query(t);
        lw[i] = query(t - 1);
        add(t, 1);
    }
    //再从后往前，求第i个数之后i+1~n个数中比a[i]大的数的个数，以及小的个数
    memset(tr, 0, sizeof tr);
    LL res1 = 0, res2 = 0;
    for (int i = n; i; --i)
    {
        int &t = a[i];
        res1 += (LL)(query(n) - query(t)) * gt[i];
        res2 += (LL)query(t - 1) * lw[i];
        add(t, 1);
    }
    printf("%lld %lld\n", res1, res2);
    return 0;
}
```

