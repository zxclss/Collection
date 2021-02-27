```c++
#include <iostream>
using namespace std;

const int N = 1010, M = 110;
int m, n;
int w[M], v[M];
int f[N];

int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= v[i]; --j) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    cout << f[m] << endl;
    return 0;
}

```

