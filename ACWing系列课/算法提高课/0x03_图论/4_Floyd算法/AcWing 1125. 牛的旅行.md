```c++
#include <iostream>
#include <queue>
#include <cmath>

#define x first
#define y second

using namespace std;

/*
求连接两个连通块后，所有连通块的直径中最大值的最小情况
首先计算出没连接之前，所有连通块内各个点i的最远直径dmax[i]

分析，连接两个连通块后，直径的改变
    情况1）合并的新连通块的直径，仍然不经过新添加的边，那就意味着，新直径是原来两个连通块的直径的最大值
        直接用res枚举所有点的最远直径即可，res = max(res, dmax[i]);
    情况2）合并的新连通块的直径经过新添加的边，那这条直径的计算方式：
        第一个连通块的最远距离 + 新添加的边 + 第二个连通块的最远距离
        d = dmax[i] + get_dist(i, j) + dmax[j]
枚举所有不连通的连通块的点两两相连的所有情况，计算最终的答案
*/
typedef pair<double,double> PDD;
const int N = 155;
const double INF = 1e20;
int n;
char g[N][N];
PDD pos[N];
double dist[N][N];
double dmax[N];

double get_dist(PDD a, PDD b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> pos[i].x >> pos[i].y;
    for (int i = 0; i < n; ++i) cin >> g[i];
    
    //初始化距离矩阵，把不能相连的两点初始化为正无穷
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j)
                if (g[i][j] == '1') dist[i][j] = get_dist(pos[i], pos[j]);
                else dist[i][j] = INF;
    
    //先计算所有连通块内部，点两两之间距离，用floyd完成
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    //计算情况1:每个点在其连通块内部的最远距离
    double res1 = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] < INF) {
                dmax[i] = max(dmax[i], dist[i][j]);
            }
        }
        res1 = max(res1, dmax[i]);  //这里把计算dmax和计算res1放在一个循环里了
    }
    //计算情况2:新直径经过新边
    double res2 = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            //不同连通块肯定是不相连的
            if (dist[i][j] >= INF) {
                double new_d = dmax[i] + get_dist(pos[i], pos[j]) + dmax[j];
                res2 = min(res2, new_d);
            }
        }
    }
    printf("%.6lf\n", max(res1, res2));
    return 0;
}
```

