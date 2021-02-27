

```C++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e5 + 10, M = 2 * N;
int g[N];
bool st[N];
int e[M], ne[M], idx;
int n;
int ans = N;

void add(int a, int b) {
    e[idx] = b, ne[idx] = g[a], g[a] = idx++;
}
int dfs(int u) {
    st[u] = true;
    if (g[u] == -1) {
        return 0;
    }
    int sum = 1, res = 0;
    for (int i = g[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            int s = dfs(j);
            res = max(res, s);
            sum += s;
        }
    }
    res = max(res, n - sum);
    ans = min(ans, res);
    return sum;
}

int main() {
    memset(g, -1, sizeof g);
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    dfs(1);
    cout << ans << endl;
    return 0;
}
```

