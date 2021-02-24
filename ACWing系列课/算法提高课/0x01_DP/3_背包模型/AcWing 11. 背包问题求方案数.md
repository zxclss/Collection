```c++
#include <iostream>
using namespace std;

const int N = 1010, mod = 1e9 + 7;
int n, m;
int f[N], g[N];

int main() {
    cin >> n >> m;
    g[0] = 1;

    for (int i = 1; i <= n; ++i) {
        int v, w;
        cin >> v >> w;
        for (int j = m; j >= v; --j) {
            int maxv = f[j], cnt = 0;
            maxv = max(f[j], f[j - v] + w);
            if (maxv == f[j]) cnt += g[j];
            if (maxv == f[j - v] + w) cnt += g[j - v];
            g[j] = cnt % mod;
            f[j] = maxv;
        }
    }
    // cout << f[m] << endl;
    int res = 0;
    for (int i = 1; i <= m; ++i) {
        if (f[i] == f[m])
            res = (res + g[i]) % mod;
    }
    cout << res << endl;
    return 0;
}
```

