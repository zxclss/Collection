

```C++
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int N = 1e5 + 10;
int n, m;
int h[N], e[N], ne[N], idx;
int res[N], cnt;
int ind[N];  //额外开辟一个ind[]数组来记录每个结点的入度

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    ++ind[b];
}
bool top_sort() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (ind[i] == 0) q.push(i), res[cnt++] = i;
    }
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (--ind[j] == 0) {
                q.push(j);
                res[cnt++] = j;
            }
        }
    }
    return cnt == n;
}
int main()   {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    if (top_sort()) {
        for (int i = 0; i < cnt; ++i) printf("%d ", res[i]);
        puts("");
    } else {
        puts("-1");
    }
    return 0;
}
```

