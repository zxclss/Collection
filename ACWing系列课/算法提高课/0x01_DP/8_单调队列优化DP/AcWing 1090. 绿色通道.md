```c++
#include <iostream>
using namespace std;

const int N = 5e4 + 10;
int n, m;
int w[N];
int q[N], f[N];

bool check(int limit) {
    //初始队列压入f[0] = 0
    int tt = 0, hh = 0;
    for (int i = 1; i <= n; ++i) {
        //最远的位置是和当前位置之间有limit个空格的位置，还远就g了
        if (q[hh] < i - limit - 1) ++hh;
        f[i] = f[q[hh]] + w[i];
        while (hh <= tt && f[q[tt]] >= f[i]) --tt;
        q[++tt] = i;
    }
    for (int i = n - limit; i <= n; ++i)
        if (f[i] <= m) return true;
    return false;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    
    int l = 0, r = n;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << r << endl;
    return 0;
}
```

