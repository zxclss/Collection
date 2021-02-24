> 最小生成树的虚拟源点问题
```c++
#include <iostream>
#include <cstring>

using namespace std;

//最小生成树的虚拟源点问题
//每个井口建立发电站的行为，看做从一个虚拟的起点连接一条边
//边的权值就是建发电站的费用
//这样所有供电的井口就是在连通块内部的点

const int N = 310;
int n;
int g[N][N];
int dist[N];
bool st[N];

int prim() {
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0;
    
    int res = 0;
    for (int i = 0; i <= n; ++i) {
        int t = -1;
        for (int j = 0; j <= n; ++j)
            if (!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        st[t] = true;
        res += dist[t];
        
        for (int j = 0; j <= n; ++j) dist[j] = min(dist[j], g[t][j]);
    }
    return res;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> g[0][i], g[i][0] = g[0][i];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> g[i][j];
    cout << prim() << endl;
    return 0;
}
```