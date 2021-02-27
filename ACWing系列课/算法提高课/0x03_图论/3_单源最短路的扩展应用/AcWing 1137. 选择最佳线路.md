```c++
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<int, int> PII;
//建立虚拟源点0
const int N = 1010, M = 40010, INF = 0x3f3f3f3f;
int n, m, s;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 0});
    dist[0] = 0;
    while (!heap.empty()) {
        PII t = heap.top();
        heap.pop();
        
        int ver = t.second;
        if (st[ver]) continue;
        st[ver] = true;
        
        for (int i = h[ver]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
    if (dist[s] == INF) return -1;
    return dist[s];
}
int main() {
    while (~scanf("%d%d%d", &n, &m, &s)) {
        memset(h, -1, sizeof h);
        idx = 0;
        
        int x;
        while (m--) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c);
        }
        scanf("%d", &x);
        while (x--) {
            int stop;
            scanf("%d", &stop);
            add(0, stop, 0);
        }
        cout << dijkstra() << endl;
    }
    return 0;
}
```

