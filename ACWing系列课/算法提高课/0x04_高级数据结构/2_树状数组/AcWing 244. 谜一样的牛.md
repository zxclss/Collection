> 一个很难看出的树状数组模型
> 本题是完成 `寻找动态第k小的数` + `删除第k小的数`

> 最适合的数据结构应该是平衡树splay，但是介于这是小题目，写个splay写明年去没必要

> 本题还可以采用树状数组来完成：用树状数组维护前缀和数组
> 前缀和数组s[i]表示从$1$ ~ $i$之间，有多少个数字还没有被用过

> 对于`删除第k小的数`的操作很简单，对于树状数组只需add(i, -1)即可完成单点修改
> 对于`寻找动态第k小的数`的操作，需要使用`二分`的思想，找到前缀和小于等于k的左边界即可

```c++
#include <iostream>

using namespace std;

const int N = 1e5 + 10;
int n;
int tr[N], a[N];
int res[N];

int lowbit(int x)
{
    return x & -x;
}
void add(int x, int v)
{
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += v;
}
int query(int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) ++tr[i];
    for (int x = 1; x <= n; ++x)
        for (int i = x - 1; i >= x - lowbit(x) + 1; i -= lowbit(i))
            tr[x] += tr[i];
    
    //从后往前遍历a[i]
    //则对于第i头牛，比他高的牛的个数是a[i]
    //这就表示当前牛的高度是在剩余高度当中的第 a[i] + 1 小的数
    for (int i = n; i; --i)
    {
        int k = a[i] + 1;   //目标是找第k小的数
        int l = 1, r = n;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (query(mid) >= k) r = mid;
            else l = mid + 1;
        }
        //那么二分出的答案就是满足>=k的最小值，也就是k
        res[i] = l;
        //当第k小的数被用过之后，我们需要把它删去
        add(l, -1);
    }
    for (int i = 1; i <= n; ++i) printf("%d\n", res[i]);
    return 0;
}
```

