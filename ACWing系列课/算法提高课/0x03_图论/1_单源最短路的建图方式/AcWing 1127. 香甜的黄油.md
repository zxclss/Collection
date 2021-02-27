```c++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 810, M = 3000, INF = 0x3f3f3f3f;
int n, p, c;
int id[N];
int h[N], e[M], ne[M], w[M], idx;
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
int spfa(int S) {
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    q[0] = S, st[S] = true;
    int hh = 0, tt = 1;
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;
        
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    st[j] = true;
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (dist[id[i]] == INF) return INF;
        else res += dist[id[i]];
    }
    return res;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> p >> c;
    for (int i = 0; i < n; ++i) cin >> id[i];
    while (c--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    int res = INF;
    for (int i = 1; i <= p; ++i) res = min(res, spfa(i));
    
    cout << res << endl;
    
    return 0;
}
```

