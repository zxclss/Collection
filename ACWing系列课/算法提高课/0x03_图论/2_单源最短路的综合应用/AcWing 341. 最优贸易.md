```c++
#include <iostream>
#include <cstring>

/*
	这条路线可以看作存在一个分界点k属于[1,n]，把该路线切割成 1 -> k -> n
	在[1,k]的点里，可以进行买入操作；在[k,n]的点里，可以进行卖出操作
	而我们要做的就是让买入价格dmin最低，卖出价格dmax最高
	dmin[k] = min{w[1], w[2]  , ..., w[k]} = min{dmin[k - 1], w[k]};
	dmax[k] = min{w[n], w[n-1], ..., w[k]} = min{dmin[k + 1], w[k]};

    这题存在环（路线可以是1->2->1->...）因此不能采用dp的方法来推导
    这题也不能使用dijkstra，因为比如w[2]=5,w[3]=4,（2->3->2->...）的路线，2会被再次更新最小值
但Dijkstra每个点出队时，必须得是最小值，因此dijkstra失效
    按照这题的性质，可以使用spfa：spfa可以处理环存在的情况（负环才会失效）
    这题还有一个问题就是，所有的边权都是记录在点上的点权，Dijkstra处理不了，而spfa是不区分边
和点的，spfa非常适用这一题
    
    先从起点1开始做一遍spfa，求出所有点1～k的最小买入点dmin
    再从终点n开始反向做spfa，求出所有点k～n的最大卖出点dmax
    最后枚举k的位置，计算出答案即可
    
    由于需要反向做最短路算法，因此我们需要额外开一个rh[]，来存储反向的边的邻接表
*/

using namespace std;

const int N = 100010, M = 1000010;
int n, m;
int h[N], rh[N], e[M], ne[M], idx;
int w[N];
int dmax[N], dmin[N];
int q[N];
bool st[N];

void add(int h[], int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void spfa(int h[], int dist[], int type) {
    int hh = 0, tt = 1;
    if (type == 1) {
        memset(dmin, 0x3f, sizeof dmin);    //求最小值初始化为正无穷
        q[0] = 1, st[1] = true;
        dist[1] = w[1];
    } else {
        memset(dmax, -0x3f, sizeof dmax);   //求最大值初始化为负无穷
        q[0] = n, st[n] = true;
        dist[n] = w[n];
    }
    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) hh = 0;
        st[t] = false;
        
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (type == 1 && dist[j] > min(dist[t], w[j]) || type == 2 && dist[j] < max(dist[t], w[j])) {
                if (type == 1) dist[j] = min(dist[t], w[j]);
                else dist[j] = max(dist[t], w[j]);
                
                if (!st[j]) {
                    st[j] = true;
                    q[tt++] = j;
                    if (tt == N) tt = 0;
                }
            }
        }
    }
}
int main() {
    memset(h, -1, sizeof h);
    memset(rh, -1, sizeof rh);
    
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);
    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(h, a, b), add(rh, b, a);
        if (c == 2) add(h, b, a), add(rh, a, b);
    }
    spfa(h, dmin, 1);
    spfa(rh, dmax, 2);
    
    int res = 0;
    //k是可以等于边界的，也就是一开始就买入或卖出，或者结束的时候买入或卖出
    for (int k = 1; k <= n; ++k)
        res = max(res, dmax[k] - dmin[k]);
    printf("%d\n", res);
    
    return 0;
}
```

