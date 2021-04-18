> 线段树：扫描线法
> 无法拓展到一般情况，扫描线法请自觉背出
```c++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int n;
vector<double> ys;  //离散化映射
struct Segment
{
    double x, y1, y2;
    int v;
    bool operator< (const Segment& t) const
    {
        return x < t.x;
    }
}seg[N * 2];
struct Node
{
    int l, r;
    //线段树[l,r]维护的是ys[r+1] ~ ys[l]的区间【重点】
    //换而言之，[l,l]的叶结点表示的区间是ys[l+1]~ys[l]
    int cnt;       //当前区间被覆盖的次数
    double len;    //子区间总共被覆盖的长度
}tr[N * 8];

int find(double y)
{
    return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
}
void pushup(int u)
{
    if (tr[u].cnt) tr[u].len = (ys[tr[u].r + 1] - ys[tr[u].l]);
    else if (tr[u].l != tr[u].r)
    {
        tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
    }
    else tr[u].len = 0;
}
void build(int u, int l, int r)
{
    tr[u] = {l, r, 0, 0};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}
void modify(int u, int l, int r, int v)
{
    if (l <= tr[u].l && tr[u].r <= r)
    {
        tr[u].cnt += v;
        pushup(u);
    }
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, v);
        if (r > mid) modify(u << 1 | 1, l, r, v);
        pushup(u);
    }
}

int main()
{
    int T = 0;
    while (scanf("%d", &n), n)
    {
        ys.clear();
        double x1, y1, x2, y2;
        for (int i = 0, j = 0; i < n; ++i)
        {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            seg[j++] = {x1, y1, y2,  1};
            seg[j++] = {x2, y1, y2, -1};
            ys.push_back(y1);
            ys.push_back(y2);
        }
        
        n *= 2;
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        
        sort(seg, seg + n);
        build(1, 0, ys.size() - 2);
        
        double res = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i) res += tr[1].len * (seg[i].x - seg[i - 1].x);
            modify(1, find(seg[i].y1), find(seg[i].y2) - 1, seg[i].v);
        }
        printf("Test case #%d\n", ++T);
        printf("Total explored area: %.2lf \n\n", res);
    }
    return 0;
}
```