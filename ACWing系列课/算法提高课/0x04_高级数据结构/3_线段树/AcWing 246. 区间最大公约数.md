$gcd(a, b, c) = gcd(a, b - a, c - b)$

$gcd(a_1, a_2, ... , a_n) = gcd(a_1, a_2 - a_1, a_3 - a_2, ... , a_n - a_{n - 1})$

> 很好证明，具体详见 [AcWing 246. 区间最大公约数（算法提高课）](https://www.acwing.com/video/650/)

本题用线段树维护差分数组，完成`区间修改` + 求区间最大公约数。

```c++
#include <iostream>

using namespace std;

const int N = 500010;

typedef long long LL;

int n, m;
LL w[N];
struct Node
{
    int l, r;
    LL sum, gcd;
}tr[N * 4];

LL gcd(LL a, LL b)
{
    return b ? gcd(b, a % b) : a;
}

void pushup(Node &u, Node &l, Node &r)
{
    u.sum = l.sum + r.sum;
    u.gcd = gcd(l.gcd, r.gcd);
}
void pushup(int u)
{
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}
void build(int u, int l, int r)
{
    if (l == r)
    {
        LL d = w[r] - w[r - 1];
        tr[u] = {r, r, d, d};
    }
    else
    {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
void modify(int u, int x, LL v)
{
    if (tr[u].l == tr[u].r)
    {
        LL b = tr[u].sum + v;
        tr[u] = {x, x, b, b};
    }
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}
Node query(int u, int l, int r)
{
    if (l <= tr[u].l && tr[u].r <= r) return tr[u];
    int mid = tr[u].l + tr[u].r >> 1;
    if (r <= mid) return query(u << 1, l, r);
    if (l > mid) return query(u << 1 | 1, l, r);
    else {
        auto left = query(u << 1, l, r);
        auto right = query(u << 1 | 1, l, r);
        Node res;
        pushup(res, left, right);
        return res;
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%lld", &w[i]);
    build(1, 1, n);
    
    char op[2];
    int l, r;
    LL c;
    while (m -- )
    {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'C')
        {
            scanf("%lld", &c);
            modify(1, l, c);
            if (r + 1 <= n) modify(1, r + 1, -c);   //防止越界
        }
        else
        {
            auto left = query(1, 1, l);
            Node right = {0, 0, 0, 0};
            if (l + 1 <= r) right = query(1, l + 1, r);
            printf("%lld\n", abs(gcd(left.sum, right.gcd)));
        }
    }
    return 0;
}
```