```c++
#include <iostream>
using namespace std;

//不同于最长上升子序列
//最大上升子序列和的集合的属性是：以a[i]结尾的上升子序列的和的最大值
//所以状态转移方程需要修改为: f[i] = max(f[i], f[j] + a[i]); 当(a[i] > a[j])时

const int N = 1010;
int n;
int a[N];
int f[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    
    for (int i = 1; i <= n; ++i) {
        f[i] = a[i];
        for (int j = 1; j < i; ++j) {
            if (a[i] > a[j]){
                f[i] = max(f[i], f[j] + a[i]);
            }
        }
    }
    
    int res = 0;
    for (int i = 1; i <= n; ++i) res = max(res, f[i]);
    printf("%d\n", res);
    
    return 0;
}
```

