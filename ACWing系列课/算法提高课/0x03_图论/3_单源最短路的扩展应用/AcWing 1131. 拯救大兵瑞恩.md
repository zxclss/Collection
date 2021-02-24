```c++
#include <iostream>
#include <deque>
#include <cstring>
#include <set>

#define x first
#define y second
/*
状态表示f[x][y][state]
    集合：所有从起点走到(x,y)这个格子，且当前已经拥有的钥匙是state的所有路线的集合
    属性：最短距离
状态计算
    1、(x,y)这里有一些钥匙，那么可以直接将所有钥匙拿起(state|key)
        d[x][y][state|key] = min(d[x][y][state|key], d[x][y][state])
    2、向上下左右四个方向走（1）没有门和墙（2）有门，且有匹配的钥匙
        d[a][b][state] = min(d[a][b][state], d[x][y][state] + 1);
对于边权只有0和1的图，我们采用双端队列bfs来解决
*/

using namespace std;

typedef pair<int, int> PII;

const int N = 11, M = 400;
int n, m, p, k;
int h[N * N], e[M], w[M], ne[M], idx;
int dist[N * N][1 << N];
int st[N * N][1 << N];
int g[N][N], key[N * N];

set<PII> edges; //方便在bfs的时候查表，来看走下一步会不会撞墙

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
void build() {
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            //枚举g[i][j]的四个方向，对于能走的方向，建一条边
            for (int d = 0; d < 4; ++d) {
                int x = i + dx[d], y = j + dy[d];
                if (x < 1 || x > n || y < 1 || y > m) continue;
                //二维映射为一维
                int a = g[i][j], b = g[x][y];
                //如果没有墙，畅通无阻，则建一条边
                if (!edges.count({a, b}))
                    add(a, b, 0);
            }
        }
    }
}
int bfs() {
    memset(dist, 0x3f, sizeof dist);
    dist[g[1][1]][0] = 0;
    deque<PII> q;
    q.push_front({g[1][1], 0});   //起点信息，一维坐标g[1][1]，钥匙状态0
    
    while (!q.empty()) {
        PII t = q.front();
        q.pop_front();
        
        int ver = t.x, state = t.y;
        if (st[ver][state]) continue;
        st[ver][state] = true;
        
        //双端BFS搜到的第一个终点就是最短路
        if (ver == g[n][m]) return dist[ver][state];
        
        //检查该位置有没有钥匙，有就考虑要不要拿起来
        if (key[ver]) {
            if (dist[ver][state | key[ver]] > dist[ver][state] + 0) {
                dist[ver][state | key[ver]] = dist[ver][state] + 0;
                q.push_front({ver, state | key[ver]});
            }
        }
        //然后考虑往能走的方向走（无权边可以直接走，有权边需要检查当前钥匙是否满足要求）
        for (int i = h[ver]; ~i; i = ne[i]) {
            int j = e[i];
            //没有门 或者 有门且当且有这个门对应的钥匙
            if (!w[i] || (state >> w[i]) & 1) {
                if (dist[j][state] > dist[ver][state] + 1) {
                    dist[j][state] = dist[ver][state] + 1;
                    q.push_back({j, state});
                }
            }
        }
    }
    return -1;
}
int main() {
    cin >> n >> m >> p >> k;
    memset(h, -1, sizeof h);
    //初始化，构建二维矩阵 —> 一维数组的映射关系
    for (int i = 1, t = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j, ++t) {
            g[i][j] = t;
        }
    }
    //读入所有的墙
    while (k--) {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        int a = g[x1][y1], b = g[x2][y2];
        //用打表的方式标记所有不能走的墙，方便初始化的是否快速找到所有畅通的路
        edges.insert({a, b}), edges.insert({b, a});
        //未来有钥匙后能走的路建一条有权重的边，权重是钥匙的类型
        if (c) add(a, b, c), add(b, a, c);
    }
    //初始化地图，把所有能走的路都建一条边
    build();
    // 读入所有的钥匙
    int s;
    cin >> s;
    while (s--) {
        int x, y, c;
        cin >> x >> y >> c;
        key[g[x][y]] |= 1 << c;
    }
    //目前为止，所有的数据预处理都完成了
    //对于所有可以走的路（不含任何门和墙）都建立了一条边权为0的边
    //对于所有需要钥匙才能走过去的路，建立了一条边权为钥匙类型的边
    //剩下的工作的就bfs了
    cout << bfs() << endl;
    return 0;
}
```

