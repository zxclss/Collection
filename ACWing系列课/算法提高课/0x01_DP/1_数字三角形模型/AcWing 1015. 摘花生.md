```c++
#include <iostream>
using namespace std;

const int N = 110;

int T, n, m;
int w[N][N];
int f[N][N];

int main() {
    scanf("%d", &T);
    while (T--) {
        //in
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &w[i][j]);
            }
        }
        //dp
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                f[i][j] = max(f[i - 1][j], f[i][j - 1]) + w[i][j];
            }
        }
        //out
        printf("%d\n", f[n][m]);
    }
    return 0;
}
```