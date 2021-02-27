```c++
#include <iostream>
using namespace std;

const int N = 1010;
int n, m, k;
int w[N][N];
int row_min[N][N], row_max[N][N];
int q[N];

void get_min(int a[], int b[], int t) {
    int hh = 0, tt = -1;
    for (int i = 1; i <= t; ++i) {
        if (hh <= tt && q[hh] <= i - k) ++hh;
        while (hh <= tt && a[q[tt]] >= a[i]) --tt;
        q[++tt] = i;
        b[i] = a[q[hh]];
    }
}
void get_max(int a[], int b[], int t) {
    int hh = 0, tt = -1;
    for (int i = 1; i <= t; ++i) {
        if (hh <= tt && q[hh] <= i - k) ++hh;
        while (hh <= tt && a[q[tt]] <= a[i]) --tt;
        q[++tt] = i;
        b[i] = a[q[hh]];
    }
}
int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &w[i][j]);
    //先对每一行求出n区间内的最小/大值
    for (int i = 1; i <= n; ++i) {
        get_min(w[i], row_min[i], m);
        get_max(w[i], row_max[i], m);
    }
    //再对每一行n区间最值计算，求出每一列n区间内的最小/大值
    int res = 1e9;
    int a[N], b[N], c[N]; //用数组a进行备份，用于把原来的“列”转换为计算机可以计算的“行”
    //b，c分别用来存列向的最大/最小值
    for (int i = k; i <= m; ++i) {  //i从k开始迭代，因为前k列的最大值存到第k列中了，前面已经失去意义了
        for (int j = 1; j <= n; ++j) a[j] = row_min[j][i];
        get_min(a, b, n);
        
        for (int j = 1; j <= n; ++j) a[j] = row_max[j][i];
        get_max(a, c, n);
        
        for (int j = k; j <= n; ++j) res = min(res, c[j] - b[j]);
    }
    printf("%d\n", res);
    return 0;
}
```

