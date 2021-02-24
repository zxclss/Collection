> 好家伙，这么难

<img src="/Users/zhaoxiucong/Library/Application Support/typora-user-images/image-20210219212628395.png" alt="image-20210219212628395" style="zoom:25%;" />

```c++
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

/*
如果边权非负，那么可以用Dijkstra算法
如果是拓扑图，那么不管边权是正是负，均可按拓扑序扫描，时间复杂度是线性的

而这一题有额外说明，负权边（航线）连接的两个连通分量，除了该负权边以外，没有其他手段可以连接这两个分量
因此这一题采用的方法就是，团内所有的正权边都采用Dijkstra更新
而通过负权边连接的团与团，通过拓扑排序完成更新

处理流程：
    1、先输入所有双向道路，然后dfs出所有连通块，计算两个数组
        id[]存储每个点属于哪个连通块
        vecotr<int> block[]存储每个连通块里有哪些点
    2、输入所有航线，同时统计出每个连通块的入度
    3、按照拓扑序依次处理每个连通块。先将所有入读为0的连通块的编号加入队列中
    4、每次从队头取出一个连通块的编号bid
    5、将该block[id]中的所有点加入堆中，然后对堆中所有点跑Dijkstra算法
    6、每次取出堆中距离最小的点ver
    7、然后遍历ver所有邻点j。
        如果id[ver] == id[j]，那么如果j能被更新，则将j插入堆中
        如果id[ver] != id[j]，则将id[j]这个连通块的入度减1，如果减为0，则将其插入拓扑排序的队列中
*/

using namespace std;

typedef pair<int, int> PII;

const int N = 25010, M = 150010, INF = 0x3f3f3f3f;
int n, mr, mp, S;
int h[N], w[M], ne[M], e[M], idx;
int dist[N];
bool st[N];

int id[N], bcnt;
int indegree[N];
vector<int> block[N];
queue<int> q_top;

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int u, int bid) {
    id[u] = bid;
    block[bid].push_back(u);
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!id[j]) dfs(j, bid);
    }
}
void dijkstra(int bid) {
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    for (auto u: block[bid]) {
        heap.push({dist[u], u});
    }
    while (!heap.empty()) {
        PII t = heap.top();
        heap.pop();
        
        int ver = t.second;
        if (st[ver]) continue;
        st[ver] = true;
        
        for (int i = h[ver]; ~i; i = ne[i]) {
            int j = e[i];
            //如果更新到一个不是在同一个连通分量内部的点的值
            //那么用来更新这个值的边，一定就是我们的负权边了
            //负权边千万不能加到dijkstra的队列中去运算
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                if (bid == id[j]) heap.push({dist[j], j});
            }
            if (bid != id[j] && --indegree[id[j]] == 0) q_top.push(id[j]);
            //如果更新完了这条负权边后，那个被更新的连通分量入度为0，则把他加入到top排序中
        }
    }
}
void topsort() {
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    //找出所有入读为0的团，加入队列开始topsort
    for (int i = 1; i <= bcnt; ++i)
        if (!indegree[i])
            q_top.push(i);
    //团内进行dijkstra
    // cout << q_top.size() << endl;
    while (!q_top.empty()) {
        int t = q_top.front();
        q_top.pop();
        dijkstra(t);
    }
}
int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d%d", &n, &mr, &mp, &S);
    while (mr--) {
        int a, b, c;
        scanf("%d%d%d", &a,  &b, &c);
        add(a, b, c), add(b, a, c);
    }
    for (int i = 1; i <= n; ++i) {
        //对于未加入连通分量的点，额外开一个序号
        //下标从1开始
        if (!id[i]) {
            dfs(i, ++bcnt);
        }
    }
    while (mp--) {
        int a, b, c;
        scanf("%d%d%d", &a,  &b, &c);
        add(a, b, c);
        ++indegree[id[b]];  //连通分量id[b]的入度加1（方便后续的拓扑排序）
    }
    topsort();
    
    for (int i = 1; i <= n; ++i) {
        if (dist[i] > INF / 2) puts("NO PATH");
        else printf("%d\n", dist[i]);
    }
    return 0;
}


```

