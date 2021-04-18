> 离散化预处理 + 并查集检查约束条件
```c++
#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int N = 1000010;
int T, n, m;
int p[N];
unordered_map<int,int> S;
struct Query
{
    int a, b, c;
}qs[N];

int get(int x)
{
    if (!S.count(x)) S[x] = ++m;
    return S[x];
}
int find(int x)  // 并查集
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    scanf("%d", &T);
    while (T--) {
        m = 0;
        S.clear();
        
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            qs[i] = {get(a), get(b), c};    //这题数据分散，需要额外做离散化
        }
        for (int i = 1; i <= m; ++i) p[i] = i;
        
        //先检查所有相等的约束
        for (int i = 0; i < n; ++i)
        {
            if (qs[i].c == 0) continue;
            int pa = find(qs[i].a), pb = find(qs[i].b);
            if (pa != pb) p[pa] = pb;
        }
        //再通过不想等的约束检查是否连通
        bool flag = true;
        for (int i = 0; i < n; ++i) {
            if (qs[i].c) continue;
            int pa = find(qs[i].a), pb = find(qs[i].b);
            if (pa == pb)
            {
                flag = false;
                break;
            }
        }
        if (flag) puts("YES");
        else puts("NO");
    }
    return 0;
}
```