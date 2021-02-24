

```C++
#include <iostream>
#include <cstring>
using namespace std;
const int N = 210, M = 20010, INF = 0x3f3f3f3f;
int n, m, k;
int g[N][N];

void floyd() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                g[j][k] = min(g[j][k], g[j][i] + g[i][k]);
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) g[i][j] = 0;
            else g[i][j] = INF;
        }
    }
    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = min(g[a][b], c);
    }
    floyd();
    while (k--) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (g[a][b] > INF / 2) puts("impossible");
        else printf("%d\n", g[a][b]);
    }
    return 0;
}
```

