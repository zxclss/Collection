> 差分约束
```c++
#include <iostream>
#include <cstring>
using namespace std;

/*
num[i]表示i时刻有多少人申请上岗，x[i]为i时刻实际上岗的人数，s为x的前缀和数组。
(1)上岗人数不能负数，即 s[i]−s[i−1]>=0
(2)实际上岗人数不能超过申请人数，即 s[i]−s[i−1]<=num[i]
(3)i时刻所在人数，即[i−7,i]区间内的上岗人数 >= 最小需求 R
    当 i >= 8 时，s[i]−s[i−8]>=R[i]
    当 i <= 7 时，s[i]+s[24]−s[16+i]>=R[i]
就有了差分约束：
(1)s[i] >= s[i-1]
(2)s[i-1] >= s[i] - num[i]
(3)s[i] >= s[i-8] + R[i]
   s[i] >= s[16+i] + R[i] - s[24]

对于最后一个不等式中的s[24]，我们把它看做常数c，在数据范围内暴力枚举就好了
s[24] == c: s[24] >= s[0] + c 且 s[24] <= s[0] + c -> s[0] >= s[24] - c
*/
const int N = 30, M = 100;
int T, n;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], cnt[N], q[N];
bool st[N];
int R[N], num[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void build(int c) {
    memset(h, -1, sizeof h);
    idx = 0;
    
    add(0, 24, c), add(24, 0, -c);
    for (int i = 1; i <= 24; ++i) {
        add(i, i - 1, -num[i]);
        add(i - 1, i, 0);
    }
    for (int i = 8; i <= 24; ++i) add(i - 8, i, R[i]);
    for (int i = 1; i <= 7; ++i) add(i + 16, i, R[i] - c);
}
bool spfa(int c) {
    build(c);
    
    memset(dist, -0x3f, sizeof dist);
    memset(cnt, 0, sizeof cnt);
    memset(st, 0, sizeof st);
    
    int hh = 0, tt = 1;
    q[0] = 0;
    dist[0] = 1, st[0] = true;
    
    while (tt != hh) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;
        
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                
                if (cnt[j] >= 25) return false;
                
                if (!st[j]) {
                    st[j] = true;
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                }
            }
        }
    }
    return true;
}
int main() {
    cin >> T;
    while(T--) {
        for (int i = 1; i <= 24; ++i) cin >> R[i];  //为了与前缀和下标一致，整体向后移一位
        cin >> n;
        memset(num, 0, sizeof num);
        for (int i = 0; i < n; ++i) {
            int t;
            cin >> t;
            ++num[t + 1];
        }
        
        //暴力枚举s24的值
        bool flag = false;
        for (int c = 0; c <= 1000; ++c) {
            if (spfa(c)) {
                cout << c << endl;
                flag = true;
                break;
            }
        }
        if (!flag) puts("No Solution");
    }
    return 0;
}

```
