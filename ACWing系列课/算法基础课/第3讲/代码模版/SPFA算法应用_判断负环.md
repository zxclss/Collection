

```C++
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N = 10010;
int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bool st[N];
int cnt[N];  //cnt[]统计每个点最短路径所经过的边数

bool spfa() {
  //此处不初始化dist数组，因为并不是求距离的绝对值
  //如果存在负环的话dist[j] > dist[t] + w[i]会恒成立因为在没有初始化的dist数组中:
  //dist[j] = 0, dist[t] = 0,但是w[i] < 0。
  //因此会在这个地方无限循环，直到cnt == n时退出循环，告知存在负环
    queue<int> q;
    for (int i = 1; i <= n; ++i) st[i] = true, q.push(i);
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                //一旦有一个点的最短路径经过n条边，（一共只有n-1条）则必存在负环。
                if (cnt[j] >= n) return true;	
                if (!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    return false;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        e[idx] = b, ne[idx] = h[a], h[a] = idx, w[idx++] = c;
    }
    if (spfa()) puts("Yes");
    else puts("No");
    return 0;
}
```

