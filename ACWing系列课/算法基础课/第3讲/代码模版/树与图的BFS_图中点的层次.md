

```C++
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e5 + 10;

int g[N];
int e[N], ne[N], idx;
int d[N];
int n, m;

int bfs() {
    queue<int> q;
    d[1] = 0, q.push(1);
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (int i = g[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (d[j] == -1) {
                d[j] = d[t] + 1;
                q.push(j);
            }
        }
    }
    return d[n];
}
int main() {
    memset(g, -1, sizeof g);
    memset(d, -1, sizeof d);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        e[idx] = b, ne[idx] = g[a], g[a] = idx ++;
    }
    cout << bfs() << endl;
    return 0;
}

```

