## 并查集

### 操作：
1. `合并`两个集合
2. `查询`某个元素的`祖宗`结点

### 拓展应用：
1. 记录每个`集合的大小` -> 绑定到`根结点`上
2. 记录每个`点到根结点的距离` -> 绑定到`每个元素`上 ([AcWing 240.食物链](https://www.acwing.com/problem/content/242/))

### 本题代码
```c++
#include <iostream>
using namespace std;

const int N = 40010;
int n, m;
int p[N];

int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
//get完成二维数组到一维数组的映射
int get(int x, int y) {
    return x * n + y;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n * n; ++i) p[i] = i;
    int res = 0;
    for (int i = 1; i <= m; ++i) {
        int x, y;
        char op;
        cin >> x >> y >> op;
        int a = get(--x, --y);
        int b;
        if (op == 'D') b = get(x + 1, y);
        else b = get(x, y + 1);
        
        if (find(a) != find(b)) p[find(a)] = p[b];
        else {
            res = i;
            break;
        }
    }
    if (!res) puts("draw");
    else cout << res << endl;
    return 0;
}
```