

```C++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 510, M = 10010;
int n, m, k;
struct{
    int a, b, w;
}edges[M];
int dist[N];
int backup[N];

int bellman_ford() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    for (int i = 0; i < k; ++i) {
        memcpy(backup, dist, sizeof dist);
        for (int j = 0; j < m; ++j) {
            auto t = edges[j];
            dist[t.b] = min(dist[t.b], backup[t.a] + t.w);
        }
    }
    if (dist[n] > 0x3f3f3f3f / 2) return -1;
    else return dist[n];
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edges[i] = {a, b, c};
    }
    int t = bellman_ford();
    if (t == -1) cout << "impossible" << endl;
    else cout << t << endl;
    return 0;
}
```

