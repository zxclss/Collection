```c++
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<int, int> PII;
const int N = 50010, M = 2e5, INF = 0x3f3f3f3f;
int n, m;
int source[6];
int dist[6][N];
int h[N], e[M], w[M], ne[M], idx;
bool st[N];
int res = INF;

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void dijkstra(int start, int dist[]) {
    memset(dist, 0x3f, N * 4);
    memset(st, 0, sizeof st);
    dist[start] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, start});
    
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
}
void dfs(int u, int sum, int curr) {
    if (u > 5) {
        res = min(res, sum);
        return;
    }
    
    for (int i = 1; i <= 5; ++i) {
        if (st[i]) continue;
        
        int next = source[i];
        if (dist[curr][next] == INF) continue;
        
        st[i] = true;
        dfs(u + 1, sum + dist[curr][next], i);
        st[i] = false;
    }
}
int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    source[0] = 1;
    for (int i = 1; i <= 5; ++i) cin >> source[i];
    
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    for (int i = 0; i < 6; ++i)
        dijkstra(source[i], dist[i]);
    
    memset(st, 0, sizeof st);
    dfs(1, 0, 0);
    cout << res << endl;
    
    return 0;
}
```

