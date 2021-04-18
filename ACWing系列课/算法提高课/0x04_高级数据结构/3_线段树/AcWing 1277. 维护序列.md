本题**懒标记**合并公式推导

$ (s \cdot mul + add) \cdot mul' + add' = (s \cdot mul \cdot mul') + (add \cdot mul' + add') $

$ newmul = mul \cdot mul' $

$ newadd = add \cdot mul' + add' $

```c++
#include <iostream>
#include <cstring>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 10;

int n, m, p;
int w[N];
struct Node
{
    int l, r;
    int sum, add, mul;
}tr[N * 4];

void pushup(int u)
{
    tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum) % p;
}
void eval(Node &root, int a, int m)
{
    root.sum = ((LL)root.sum * m + (LL)(root.r - root.l + 1) * a) % p;
    root.add = ((LL)root.add * m + a) % p;
    root.mul = ((LL)root.mul * m) % p;
}
void pushdown(int u)
{
    eval(tr[u << 1], tr[u].add, tr[u].mul);
    eval(tr[u << 1 | 1], tr[u].add, tr[u].mul);
    tr[u].add = 0, tr[u].mul = 1;
}
void build(int u, int l, int r)
{
    if (l == r) tr[u] = {l, r, w[r], 0, 1};
    else
    {
        tr[u] = {l, r, 0, 0, 1};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
void modify(int u, int l, int r, int a, int m)
{
    if (l <= tr[u].l && tr[u].r <= r) eval(tr[u], a, m);
    else
    {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, a, m);
        if (r > mid) modify(u << 1 | 1, l, r, a, m);
        pushup(u);
    }
}
int query(int u, int l, int r)
{
    if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
    
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    int res = 0;
    if (l <= mid) res = query(u << 1, l, r);
    if (r > mid) res = (res + query(u << 1 | 1, l, r)) % p;
    return res;
}

int main()
{
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    build(1, 1, n);
    scanf("%d", &m);
    while (m -- )
    {
        int t, l, r, c;
        scanf("%d%d%d", &t, &l, &r);
        if (t == 1)
        {
            scanf("%d", &c);
            modify(1, l, r, 0, c);
        }
        else if (t == 2)
        {
            scanf("%d", &c);
            modify(1, l, r, c, 1);
        }
        else
        {
            printf("%d\n", query(1, l, r));
        }
    }
    return 0;
}
```