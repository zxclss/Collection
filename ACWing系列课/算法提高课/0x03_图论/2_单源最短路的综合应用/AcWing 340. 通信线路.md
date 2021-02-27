```c++
#include <iostream>
#include <deque>
#include <cstring>

/*
定义在[0, 1e6 + 1]这个区间中的性质如下；
    对于区间中的某一个点x
求出从1～N，最少经过的长度大于x的边的数量是否小于等于k
【不满足｜满足】
这里我们把右端点设置成1e6+1的原因是：
    首先我们知道这是一个不合法的方案，因为l最大是1e6
    如果起点走不到终点，那么dist[n]一直是INF，更新出来也是一直false
    那么如果最终r==1e6+1，则说明，终点走不到，输出“-1”即可
而把0设置为左端点的原因是：
    如果我们走到终点的路径条数小于k，也就表示运营商帮我们免费支付了，最终花费就是0
    这是合法的左端点

求出从1到N最少经过几条长度大于x的边
可以将所有边分类：如果边长大于x，则边权看成1；否则边权为0
可以用双端队列BFS来求1～N的最短路
*/

using namespace std;
const int N = 1010, M = 20010;
int n, m, k;
int h[N], e[M], ne[M], w[M], idx;
int dist[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
//双向BFS（加速版优先队列Dijkstra）
bool check(int limit) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    deque<int> q;
    q.push_front(1);
    dist[1] = 0;
    while (!q.empty()) {
        int t = q.front();
        q.pop_front();
        
        if (st[t]) continue;
        st[t] = true;
        
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i], v = w[i] > limit;
            if (dist[j] > dist[t] + v) {
                dist[j] = dist[t] + v;
                if (v) q.push_back(j);
                else q.push_front(j);
            }
        }
    }
    return dist[n] <= k;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m >> k;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    int l = 0, r = 1e6 + 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    if (r == 1e6 + 1) puts("-1");
    else cout << r << endl;
    return 0;
}
```

