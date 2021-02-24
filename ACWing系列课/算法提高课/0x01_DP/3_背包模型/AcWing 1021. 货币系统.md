```c++
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 3010;

int n, m;
LL f[N];

int main() {
    f[0] = 1;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int v;
        cin >> v;
        for (int j = v; j <= m; ++j)
            f[j] += f[j - v];
    }
    cout << f[m] << endl;
    return 0;
}
```

