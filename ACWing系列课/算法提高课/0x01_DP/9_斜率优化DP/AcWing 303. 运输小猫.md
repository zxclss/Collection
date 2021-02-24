```c++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

/*
f[j][i]: j个饲养员，取走前i只小猫的最小花费
f[j][i] = min{f[j-1][k] + a[i]*(i-k) - (s[i] - s[k])};
f[j-1][k] + s[k] = a[i]*k + f[j][i] - a[i] * i + s[i];
        y        = a[i] x + c;
*/

typedef long long LL;
const int N = 1e5 + 10, M = 110;

int n, m, p;
LL d[N], t[N], a[N], s[N];
LL f[M][N];
int q[N];

LL gety(int k, int j) {
    return f[j - 1][k] + s[k];
}
int main() {
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 2; i <= n; ++i) scanf("%d", &d[i]), d[i] += d[i - 1];
    for (int i = 1; i <= m; ++i) {
        int h;
        scanf("%d%lld", &h, &t[i]);
        a[i] += t[i] - d[h];
    }
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; i ++ ) s[i] = s[i - 1] + a[i];
    
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i <= p; ++i) f[i][0] = 0;
    
    for (int j = 1; j <= p; ++j) {
        int hh = 0, tt = 0;
        for (int i = 1; i <= m; ++i) {
            while (hh < tt && gety(q[hh+1], j) - gety(q[hh], j) < a[i] * (q[hh + 1] - q[hh])) ++hh;
            int k = q[hh];
            f[j][i] = f[j-1][k] + s[k] - a[i] * k + a[i] * i - s[i];
            while (hh < tt && (gety(q[tt], j) - gety(q[tt-1], j)) * (i-q[tt]) >= (gety(i, j) - gety(q[tt], j)) * (q[tt] - q[tt-1])) --tt;
            q[++tt] = i;
        }
    }
    cout << f[p][m] << endl;
    return 0;
}
```

