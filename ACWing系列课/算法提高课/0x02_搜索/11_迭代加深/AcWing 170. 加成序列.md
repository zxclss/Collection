```c++
#include <iostream>
using namespace std;

const int N = 110;
int n;
int path[N];

bool dfs(int u, int max_depth) {
    if (u > max_depth) return false;
    if (path[u - 1] == n) return true;
    
    bool st[N] = {0};   //排除等效冗余(“1+3” 和 “2+2” 是等效的)
    //从大到小枚举，优化搜索顺序
    for (int i = u - 1; i >= 0; --i) {
        for (int j = i; j >= 0; --j) {
            int sum = path[i] + path[j];
            if (sum > n || sum <= path[u - 1] || st[sum]) continue;
            
            st[sum] = true;
            path[u] = sum;
            if (dfs(u + 1, max_depth)) return true;
        }
    }
    return false;
}
int main() {
    path[0] = 1;
    while (cin >> n, n) {
        int depth = 1;
        while (!dfs(1, depth)) ++depth;
        for (int i = 0; i < depth; ++i) cout << path[i] << " ";
        cout << endl;
    }
    return 0;
}
```

