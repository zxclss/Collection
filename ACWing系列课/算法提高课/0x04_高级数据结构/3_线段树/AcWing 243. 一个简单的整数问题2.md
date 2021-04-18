> 带懒标记的 线段树：区间修改 + 区间查询
```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 10;
int n, m;
int w[N];
struct Node
{
    int l, r;
    LL sum, add;
}tr[N * 4];

void pushup(int u)
{
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}
void pushdown(int u)
{
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add)
    {
        //传递懒标记，更新子树
        left.add += root.add, left.sum += (LL) (left.r - left.l + 1) * root.add;
        right.add += root.add, right.sum += (LL) (right.r - right.l + 1) * root.add;
        //删除父结点懒标记
        root.add = 0;
    }
}
void build(int u, int l, int r)
{
    if (l == r) tr[u] = {l, r, w[l], 0};
    else
    {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
void modify(int u, int l, int r, int v)
{
    if (l <= tr[u].l && tr[u].r <= r)
    {
        tr[u].sum += (tr[u].r - tr[u].l + 1) * v;
        tr[u].add += v;
    }
    else
    {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, v);
        if (r > mid) modify(u << 1 | 1, l, r, v);
        pushup(u);
    }
}
LL query(int u, int l, int r)
{
    if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
    
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL v = 0;
    if (l <= mid) v = query(u << 1, l, r);
    if (r > mid) v += query(u << 1 | 1, l, r);
    return v;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    build(1, 1, n);
    
    char op[2];
    int l, r, t;
    while (m -- )
    {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'Q') printf("%lld\n", query(1, l, r));
        else
        {
            scanf("%d", &t);
            modify(1, l, r, t);
        }
    }
    return 0;
}

```