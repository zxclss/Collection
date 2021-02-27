

```c++
#include <iostream>
using namespace std;

const int N = 300010;
int n, m;
int s[N], q[N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> s[i], s[i] += s[i - 1];
    
    int res = -1e9;
    int tt = 0, hh = 0; //tt这里写0表示，队列初始有一个s[0]存在
    for (int i = 1; i <= n; ++i) {
        if (hh <= tt && q[hh] < i - m) ++hh;//队列中有m个元素 -> {s[i] - s[i - m]}
        res = max(res, s[i] - s[q[hh]]);
        while (hh <= tt && s[q[tt]] >= s[i]) --tt;//为了让区间和尽可能大，需要队首元素尽可能小，因此维护一个单调递增序列
        q[++tt] = i;
    }
    cout << res << endl;
    return 0;
}
```

