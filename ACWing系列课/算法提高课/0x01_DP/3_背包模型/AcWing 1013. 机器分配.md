```c++
#include <iostream>
#include <vector>
using namespace std;

const int N = 12, M = 17;
int n, m;
int w[N][M];
int f[N][M];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> w[i][j];
        }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 0; k <= j; ++k) {
                f[i][j] = max(f[i][j], f[i - 1][j - k] + w[i][k]);
            }
        }
    }
    cout << f[n][m] << endl;
    vector<int> path;
    for (int i = n, j = m; i; --i) {
        for (int k = 0; k <= j; ++k) {
            if (f[i][j] == f[i - 1][j - k] + w[i][k]) {
                path.push_back(k);
                j -= k;
                break;
            }
        }
    }
    for (int i = path.size() - 1, k = 1; i >= 0; --i, ++k) cout << k << " " << path[i] << endl;
    return 0;
}
```

