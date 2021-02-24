```c++
#include <iostream>
using namespace std;

const int N = 31;
int n;
int w[N];
int f[N][N];
int g[N][N];
//g(l, r)用于记录(l, r)区间内的根结点

void dfs(int left, int right) {
    if (left > right) return;
    int root = g[left][right];
    //前序遍历，根-左-右
    cout << root << " ";
    dfs(left, root - 1);
    dfs(root + 1, right);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> w[i];

    for (int i = 1; i <= n; ++i) f[i][i] = w[i], g[i][i] = i;
    //叶结点的权值是本身，这是题目规定的
    //初始化f和g
    //当然这个可以写进循环里，特判len==1的情况，我这样写是便于理解
    //具体代码可以看我在寒假每日一题中加分二叉树题目的打卡

    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            for (int k = l; k <= r; ++k) {
                int l_tr = k == l ? 1 : f[l][k - 1];
                int r_tr = k == r ? 1 : f[k + 1][r];
                int score = l_tr * r_tr + w[k];
                if (score > f[l][r]) {
                    f[l][r] = score;
                    g[l][r] = k;
                }
            }
        }
    }
    cout << f[1][n] << endl;
    dfs(1, n);

    return 0;
}
```

