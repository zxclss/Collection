> 最小点覆盖
```c++
#include <iostream>
#include <cstring>
using namespace std;

const int N = 1010;
int n, m, k;
int match[N];
bool st[N], g[N][N]; //st是机器b的状态覆盖情况

bool find(int x) {
    for (int i = 0; i < m; ++i) {
        if (!st[i] && g[x][i]) {
            st[i] = true;
            int t = match[i];
            if (t == -1 || find(t)) {
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}
int main() {
    while (cin >> n, n) {
        cin >> m >> k;
        memset(match, -1, sizeof match);
        memset(st, 0, sizeof st);
        memset(g, 0, sizeof g);
        while (k--) {
            int t, a, b;
            cin >> t >> a >> b;
            if (a == 0 || b == 0) continue; //所有能在0模式下完成的都一开始做，不用转换状态
            g[a][b] = true;
        }
        
        int res = 0;
        for (int i = 1; i < n; ++i) {
            memset(st, 0, sizeof st);
            if (find(i)) ++res;
        }
        cout << res << endl;
    }
    return 0;
}
```