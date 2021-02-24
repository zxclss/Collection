```c++
#include <iostream>
#include <vector>
using namespace std;

const int N = 11;
int f[N][N];

void init() {
    for (int i = 0; i <= 9; ++i) f[1][i] = i != 4;
    
    for (int i = 2; i < N; ++i)
        for (int j = 0; j <= 9; ++j) {
            if (j == 4) continue;
            for (int k = 0; k <= 9; ++k) {
                if (k == 4 || k == 2 && j == 6) continue;
                f[i][j] += f[i - 1][k];
            }
        }
}
int dp(int n) {
    if (!n) return 1;
    vector<int> num;
    while (n) num.push_back(n % 10), n /= 10;
    
    int res = 0;
    int last = 0;
    
    for (int i = num.size() - 1; i >= 0; --i) {
        int x = num[i];
        for (int j = 0; j < x; ++j) {
            if (j == 4 || j == 2 && last == 6) continue;
            res += f[i + 1][j];
        }
        if (x == 4 || x == 2 && last == 6) break;
        last = x;
        
        if (!i) ++res;
    }
    return res;
}
int main() {
    init();
    int l, r;
    while (cin >> l >> r, l || r) cout << dp(r) - dp(l - 1) << endl;
    return 0;
}
```

