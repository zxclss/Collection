```c++
#include <iostream>
#include <cstring>

using namespace std;

/*
这题就是“没有上司的舞会”
f(i,0)表示第i个城市不放哨兵
f(i,1)表示第i个城市放哨兵
没有"上司的舞会"要求是：
    f(u, 1) += f(j, 0)
    f(u, 0) += max(f(j, 0), f(j, 1));
    选了父结点，就禁止选子结点；没选父结点，在选/不选子结点的方案里取最大值
"战略游戏"要求是：
    f(u, 0) += f(j, 1)
    f(u, 1) += min(f(j, 0), f(j, 1));
    没选父结点，就必须把所有子结点点亮；选了父结点，就在选/不选子结点的方案里取最小值
*/
const int N = 1510;
int n;
int h[N], e[N], ne[N], idx;
int f[N][2];
bool st[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int u) {
    f[u][1] = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        dfs(j);

        f[u][0] += f[j][1];
        f[u][1] += min(f[j][1], f[j][0]);
    }
}
int main() {
    while (scanf("%d", &n) != -1) {
        memset(f, 0, sizeof f);
        memset(h, -1, sizeof h);
        memset(st, 0, sizeof st);
        idx = 0;

        for (int i = 0; i < n; ++i) {
            int id, m;
            scanf("%d:(%d)", &id, &m);
            while (m--) {
                int ver;
                scanf("%d", &ver);
                add(id, ver);
                st[ver] = true;
            }
        }
        int root = 0;
        while (st[root]) ++root;
        dfs(root);
        cout << min(f[root][0], f[root][1]) << endl;
    }

    return 0;
}
```

