> Kruskal解决网格最小生成树问题
```c++
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010, M = N * N;
int n, m;
int ids[N][N]; //idx负责把二维坐标映射成一维的id，这是一个网格图论题的常见手段
int p[M];
struct Edge{
    int a, b, w;
    bool operator< (const Edge& t) const {
        return w < t.w;
    }
}edges[2 * M];
int cnt;

int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
void get_edges() {
    //一般的Kruskal算法需要对所有边按边权从小到大排序
    //这一题所有的边的边权要么是1，要么是2
    //因此在生成边的时候我们只需先把所有是1的边加入，在加入2的边
    //这样就在线性的时间复杂度内生成一个有序的“边表”
    //这是针对这中题目的优化
    int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, dw[] = {1, 2, 1, 2};
    for (int z = 0; z < 2; ++z) {
        //z = 0的时候，只插入边权为1的边，z = 1的时候才插入边权为2的边
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                for (int d = 0; d < 4; ++d) {
                    if ((d & 1) == z) {
                        int x = i + dx[d], y = j + dy[d], w = dw[d];
                        if (x && x <= n && y && y <= m) {
                            int a = ids[i][j], b = ids[x][y];
                            //同一条边会从一端到另一端加两次，我们只需一条即可
                            if (a < b) edges[cnt++] = {a, b, w};
                        }
                    }
                }
            }
        }
    }
}
int kruskal() {
    int res = 0;
    for (int i = 0; i < cnt; ++i) {
        int a = find(edges[i].a), b = find(edges[i].b), w = edges[i].w;
        if (a != b) {
            p[a] = b;
            res += w;
        }
    }
    return res;
}
int main() {
    int res = 0;
    cin >> n >> m;
    for (int i = 1; i <= n * m; ++i) p[i] = i;
    //初始化ids
    for (int i = 1, t = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j, ++t)
            ids[i][j] = t;
    //读入已有的边
    int x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        int a = ids[x1][y1];
        int b = ids[x2][y2];
        p[find(a)] = find(b);
    }
    //建出网格中的所有边
    get_edges();
    
    //kruskal
    res = kruskal();
    
    cout << res << endl;
    return 0;
}
```