```c++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 2510, M = 2 * 6200 + 10;
int n, m, S, E;
int h[N], e[M], ne[M], w[M], idx;
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
void spfa() {
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    int hh = 0, tt = 1;
    q[0] = S, st[S] = true;
    
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
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m >> S >> E;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    spfa();
    cout << dist[E] << endl;
    return 0;
}
```

