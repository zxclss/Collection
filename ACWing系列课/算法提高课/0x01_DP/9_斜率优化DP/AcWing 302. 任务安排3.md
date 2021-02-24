> 任务安排2 再加上斜率可能出现负数的情况
> 因此不能再纯在队列队头维护一个最小值来完成了
> 先维护一个单调队列，然后对这个队列中所有元素二分即可
```c++
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 3e5 + 10;
int n, s;
LL t[N], c[N];
LL f[N];
int q[N];

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld", &t[i], &c[i]), t[i] += t[i - 1], c[i] += c[i - 1];
    
    f[0] = 0;
    int hh = 0, tt = 0; //入队f[0]
    q[0] = 0;
    
    for (int i = 1; i <= n; ++i) {
        int l = hh, r = tt;
        while (l < r) {
            int mid = l + r >> 1;   //大于当前斜率的最小值，因此枚举的是左端点
            if (f[q[mid + 1]] - f[q[mid]] > (t[i] + s) * (c[q[mid + 1]] - c[q[mid]])) r = mid;
            else l = mid + 1;
        }
        f[i] = f[q[r]] - (t[i] + s) * c[q[r]] + t[i] * c[i] + s * c[n];
        while (hh < tt && (__int128)(f[q[tt]] - f[q[tt - 1]]) * (c[i] - c[q[tt]]) >= (__int128)(f[i] - f[q[tt]]) * (c[q[tt]] - c[q[tt - 1]])) --tt;
        q[++tt] = i;
    }
    printf("%lld\n", f[n]);
    return 0;
}
```