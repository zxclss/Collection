```c++
#include <iostream>
#include <cstring>
using namespace std;

/*
因为数字i的约束之和是一个确定的数字，我们可以观察到一个树的模型
数字i有唯一的父结点，就是他的约束之和sum[i]
因此我们可以通过建树的方式来求这一题，做一条从sum[i]到i的边
最终我们会得到一个“森林”，存在一些不能连到一起的树

这样求“最长变换步数”就变成了求森林中最大的树的直径

我们在递归的时候用d1, d2分别记录从根结点到叶结点的最长路径和次长路径，d1 + d2就是树的直径了
*/

const int N = 50010;
int n;
int h[N], e[N], ne[N], idx;
int sum[N]; //sum[i]存储i的约数之和
int res = 0;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfs(int u) {
    int d1 = 0, d2 = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        int dist = dfs(j) + 1;

        if (dist >= d1) d2 = d1, d1 = dist;
        else if (dist > d2) d2 = dist;
    }
    res = max(res, d1 + d2);
    return d1;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= n / i; ++j) {
            sum[i * j] += i;
        }
    }
    //1的约束之和是0，但是本题讨论的是正整数转换，因此0不参与
    for (int i = 2; i <= n; ++i)
        //该数的约数之和必须小于该数（题目要求）
        if (sum[i] < i)
            add(sum[i], i);
        //从约束之和向原数添加一条有向边
    for (int i = 1; i <= n; ++i) dfs(i);
    cout << res << endl;

    return 0;
}
```

