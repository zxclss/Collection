```c++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 70;
int n, sum, length;
int w[N];
bool st[N];

bool dfs(int group, int cur, int start) {
    if (group * length == sum) return true;
    if (cur == length) return dfs(group + 1, 0, 0);
    for (int i = start; i < n; ++i) {
        if (st[i] || cur + w[i] > length) continue;
        
        st[i] = true;
        if (dfs(group, cur + w[i], i)) return true;
        st[i] = false;
        
        //第一个或最后一个没有匹配上的话，直接剪枝
        //最后一个通过交换，等价于第一个
        //如果第一个没有匹配上，那么当前木棍放到后面任何一组中都无法匹配
        //这里直接剪掉这个长枝
        if (!cur || cur + w[i] == length) return false;
        
        //如果当前点的权值和下一个相同，那也会匹配失败
        //直接跳过
        int j = i;
        while (j < n && w[j] == w[i]) ++j;
        i = j - 1;
    }
    return false;
}
int main() {
    while (cin >> n, n) {
        memset(st, 0, sizeof st);
        sum = 0;
        for (int i = 0; i < n; ++i) cin >> w[i], sum += w[i];
        
        sort(w, w + n);
        reverse(w, w + n);
        
        length = 1;
        while (true) {
            if (sum % length == 0 && dfs(0, 0, 0)) {
                printf("%d\n", length);
                break;
            }
            ++length;
        }
    }
    return 0;
}

```

