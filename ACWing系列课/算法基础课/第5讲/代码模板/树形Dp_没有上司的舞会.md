这题是树形Dp，要用到两个状态数组
`f[i][0]`集合表示：以i为根结点的子树，不算i的快乐指数最大值
`f[i][1]`集合表示：以i为根结点的子树，算上i的快乐指数最大值
集合的属性：最大值

集合划分：
    ｜子结点child1的子树的最大值: `max(f[child1][0], f[child1[1])`
    ｜子结点child2的子树的最大值: `max(f[child2][0], f[child2[1])`
    ｜......
状态转移方程：
    `f[i][0] = sum{f[child][1]}`
    `f[i][1] = happy[i] + sum{f[child][0]}`

```c++
#include <iostream>
#include <cstring>
using namespace std;

const int  N = 6010;
int n;
int happy[N];
int h[N], e[N], ne[N], idx;
int f[N][2];
bool has_father[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int root) {
    f[root][1] = happy[root];
    
    for (int i = h[root]; i != -1; i = ne[i]) {
        int j = e[i];
        dfs(j);
        f[root][1] += f[j][0];
        f[root][0] += max(f[j][0], f[j][1]);
    }
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &happy[i]);
    }
    for (int i = 1; i < n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        has_father[a] = true;
        add(b, a);
    }
    //寻找根结点
    int root = 1;
    while (has_father[root]) ++root;
    //树形Dp
    dfs(root);
    //计算最终答案
    int res = max(f[root][0], f[root][1]);
    cout << res << endl;
    return 0;
}
```