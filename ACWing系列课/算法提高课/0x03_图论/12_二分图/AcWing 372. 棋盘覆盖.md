> 方格建图 + 二分图求最大匹配
```c++
#include <iostream>
#include <cstring>

#define x first
#define y second

using namespace std;

//本题关键在于发现在棋盘上放1x2的方格是一个最大匹配的问题
//把棋盘上的每一个方格看做一个点
//相邻两个方格之间要么是"放置-空"的状态，要么是"禁止放置-空"的状态
//就变成了二分图啦
//这里把横坐坐标之和看做点的id，即id = i + j
//所有的偶点视作一类，奇点视作一类
//然后用匈牙利算法求最大匹配即可


typedef pair<int, int> PII;
const int N = 110;
int n, m;
PII match[N][N];
bool g[N][N], st[N][N];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

bool find(int i, int j) {
    for (int d = 0; d < 4; ++d) {
        int x = i + dx[d], y = j + dy[d];
        //越界判断
        if (x <= 0 || x > n || y <= 0 || y > n) continue;
        //放置可行性判断（是否是坏格 || 有没有被放过）
        if (g[x][y] || st[x][y]) continue;
        
        st[x][y] = true;
        PII t = match[x][y];
        //如果新点是空的 || 新点是已被放置的，但是和他放置的另外一个点可以再找一个匹配
        if (t.x == -1 || find(t.x, t.y)) {
            match[x][y] = t;
            return true;
        }
    }
    return false;
}
int main() {
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a][b] = true;
    }
    //标准匈牙利算法
    memset(match, -1, sizeof match); //空匹配状态-1
    int res = 0;    //记录最大匹配
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if ((i + j) % 2 && !g[i][j]) {
                memset(st, 0, sizeof st);
                if (find(i, j)) ++res;
            }
    cout << res << endl;
    return 0;
}
```