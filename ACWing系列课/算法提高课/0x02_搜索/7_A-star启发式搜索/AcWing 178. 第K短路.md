```c++
#include <iostream>
#include <cstring>
#include <queue>

#define x first
#define y second

//这题的A-star的估计函数设定为到终点的最短距离
//因此我们需要从终点开始先做一遍dijkstra，求出所有点到终点的最短距离

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, pair<int, int>> PIII;

const int N = 1010, M = 2e5 + 10;

int n, m, S, T, K;
int h[N], rh[N], e[M], ne[M], w[M], idx;    //反向边rh用于在反向dijkstra时使用
int dist[N], cnt[N]; //记录当前点是A-star中，第几次被用到
bool st[N];

void add(int h[], int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[T] = 0;
    
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, T});
    
    while (!heap.empty()) {
        PII t = heap.top();
        heap.pop();
        
        int ver = t.y;
        if (st[ver]) continue;
        st[ver] = true;
        
        for (int i = rh[ver]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}
int astar() {
    priority_queue<PIII, vector<PIII>, greater<PIII>> heap;
    heap.push({dist[S], {0, S}});
    while (!heap.empty()) {
        PIII t = heap.top();
        heap.pop();
        
        int ver = t.y.y, distance = t.y.x;
        ++cnt[ver];
        if (cnt[T] == K) return distance;
        
        for (int i = h[ver]; ~i; i = ne[i]) {
            int j = e[i];
            //这一步很重要，第i短路的路径上的点使用次数是一定不会超过i的
            if (cnt[j] < K) {
                int d = distance + w[i];
                heap.push({d + dist[j], {d, j}});
            }
        }
    }
    return -1;
}
int main() {
    memset(h, -1, sizeof h);
    memset(rh, -1, sizeof rh);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(h, a, b, c);
        add(rh, b, a, c);
    }
    scanf("%d%d%d", &S, &T, &K);
    
    if (S == T) ++K;
    
    dijkstra();
    int t = astar();
    cout << t << endl;
    return 0;
}
```

