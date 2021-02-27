```c++
#include <iostream>
#include <cstring>
#include <deque>

#define x first
#define y second

using namespace std;


typedef pair<int,int> PII;

const int N = 510;

int T, n, m;
char g[N][N];
int dist[N][N];
bool st[N][N];


void bfs() {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    deque<PII> deq;
    deq.push_back({0, 0});
    dist[0][0] = 0;
    
    char state[5] = {"\\/\\/"}; //顺序 ↘↗↖↙
    int dx[] = {1, -1, -1, 1}, dy[] = {1, 1, -1, -1};
    int ix[] = {0, -1, -1, 0}, iy[] = {0, 0, -1, -1};   //点的坐标 -> 图中每个通道的坐标
    //每个点的坐标对应使用的通道都是其右下角的那个
    
    while (!deq.empty()) {
        PII t = deq.front();
        deq.pop_front();
        
        if (st[t.x][t.y]) continue;
        if (t.x == n && t.y == m) return;
        st[t.x][t.y] = true;
        
        for (int i = 0; i < 4; ++i) {
            int x = t.x + dx[i], y = t.y + dy[i];
            if (x < 0 || x > n || y < 0 || y > m) continue;     //终点是(n,m)因此点在边界上也要考虑进去
            int w = g[t.x + ix[i]][t.y + iy[i]] != state[i];    //不相等，则需要额外花费一体力调整轨道
            int d = dist[t.x][t.y] + w;
            if (dist[x][y] > d) {
                dist[x][y] = d;
                if (w == 0) deq.push_front({x, y});
                else if (w == 1) deq.push_back({x, y});
            }
        }
    }
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) scanf("%s", g[i]);
        
        //每次移动，横纵坐标会同时变1，因此i+j的奇偶性始终不变，起点是偶点，因此终点必须是偶点才能到达
        if (n + m & 1) puts("NO SOLUTION");
        else {
            bfs();
            printf("%d\n", dist[n][m]);
        }
    }
    return 0;
}
```

