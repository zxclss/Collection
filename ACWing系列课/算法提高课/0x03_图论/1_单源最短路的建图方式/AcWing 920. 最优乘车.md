```c++
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

const int N = 510;
int n, m;
bool g[N][N];
int stop[N];
int dist[N];
int q[N];

void bfs() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    int hh = 0, tt = 0;
    q[0] = 1;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 1; i <= n; ++i) {
            if (g[t][i] && dist[i] > dist[t] + 1) {
                dist[i] = dist[t] + 1;
                q[++tt] = i;
            }
        }
    }
}
int main() {
    cin >> m >> n;
    getchar();
    string line;
    for (int i = 0; i < m; ++i) {
        getline(cin, line);
        stringstream ssin(line);
        int cnt = 0, p;
        while (ssin >> p) stop[cnt++] = p;
        for (int j = 0; j < cnt; ++j)
            for (int k = j + 1; k < cnt; ++k)
                g[stop[j]][stop[k]] = true;
    }
    bfs();
    if (dist[n] == 0x3f3f3f3f) puts("NO");
    else cout << dist[n] - 1 << endl;
    return 0;
}
```

