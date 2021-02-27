```c++
#include <iostream>
using namespace std;

//f[i][j]   = f[i-1][j] + f[i-1][j-v] + f[i-1][j-2v] + ...
//f[i][j-v] =             f[i-1][j-v] + f[i-1][j-2v] + ...
//f[i][j] = f[i-1][j] + f[i][j-v]

int n;
int v[] = {0, 10, 20, 50, 100};
int f[1010];

int main() {
    f[0] = 1;
    cin >> n;
    for (int i = 1; i <= 4; ++i) {
        for (int j = v[i]; j <= n; ++j) {
            f[j] += f[j - v[i]];
        }
    }
    cout << f[n] << endl;
    return 0;
}
```

