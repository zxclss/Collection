> 树状数组维护`原始数组`：`区间查询`$O(\log n)$，`单点修改`改$O(\log n)$
> 树状数组维护`差分数组`：`单点查询`$O(\log n)$，`区间修改`$O(\log n)$
```c++
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int n, m;
int a[N], tr[N];

int lowbit(int x)  // 返回末尾的1
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
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    //构造差分数组
    for (int i = 1; i <= n; ++i) tr[i] = a[i] - a[i - 1];
    //O(n)建树状数组
    for (int x = 1; x <= n; ++x)
        for (int i = x - 1; i >= x - lowbit(x) + 1; i -= lowbit(i))
            tr[x] += tr[i];
    while (m -- )
    {
        string op;
        int l, r, c;
        cin >> op;
        if (op == "C")
        {
            cin >> l >> r >> c;
            add(l, c), add(r + 1, -c);
        }
        else
        {
            cin >> c;
            printf("%d\n", query(c));
        }
    }
    
    return 0;
}
```

