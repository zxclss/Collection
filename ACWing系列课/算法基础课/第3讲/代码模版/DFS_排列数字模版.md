

```C++
#include <iostream>
using namespace std;
const int N = 10;
int path[N];
bool vis[N];
int n;
void dfs(int u) {
    if (u == n) {
        for (int i = 0; i < n; ++i) printf("%d ", path[i]);
        puts("");
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            vis[i] = true;
            path[u] = i;
            dfs(u + 1);
            // path[u] = 0;
            vis[i] = false;
        }
    }
}
int main() {
    scanf("%d", &n);
    dfs(0);
    return 0;
}
```

