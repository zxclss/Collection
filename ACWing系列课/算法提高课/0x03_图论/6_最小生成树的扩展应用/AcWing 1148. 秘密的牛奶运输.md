> 次小生成树的求解
```c++
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

/*
求一棵树的次小生成树方法
（1）先求最小生成树，再枚举删去最小生成树中的边再求一遍最小生成树。O(mlogm+nm)
（2）先求最小生成树，然后依次枚举非树边，然后将该边加入树中，同时从树中去掉一条边，
使得最终的图仍是一棵树，则一定可以求出最小生成树。

步骤：
1、求最小生成树，标记每条是树边还是非树边；同时把最小生成树建图
2、预处理最小生成树中任意两点之间的边权最大值dist(a,b)
3、依次枚举所有非树边，求min(sum + w - dist(a,b))，满足 w > dist(a -> b)
*/
typedef long long LL;
const int N = 510, M = 1e4 + 10;
int n, m;
struct Edge{
    int a, b, c;
    bool is_tree;
    bool operator< (const Edge& t) const {
        return c < t.c;
    }
}edges[M];
int h[N], e[2 * N], w[2 * N], ne[2 * N], idx;
int p[N];
int dist1[N][N], dist2[N][N];
//由于这一题要求是严格次小生成树
//因此如果最小生成树中的最长边和要加入进来的边相等，则可以用环里的次长边代替最长边删掉

int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int u, int father, int dmax1, int dmax2, int d1[], int d2[]) {
    d1[u] = dmax1, d2[u] = dmax2;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        
        //temp_dmax1存储从i（没写错，i是一开始调用的那个点）到j的最长的边，temp_dmax2存储次长的边
        //这样加入新边的时候，就可以通过dist[a][b]直接获得最小生成树中a-b的路径上最长的边，然后把它删掉了
        int temp_dmax1 = dmax1, temp_dmax2 = dmax2;
        if (w[i] > temp_dmax1) temp_dmax2 = temp_dmax1, temp_dmax1 = w[i];
        else if (w[i] < temp_dmax1 && w[i] > temp_dmax2) temp_dmax2 = w[i];
        dfs(j, u, temp_dmax1, temp_dmax2, d1, d2);
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) p[i] = i;
    for (int i = 0; i < m; ++i) cin >> edges[i].a >> edges[i].b >> edges[i].c;
    sort(edges, edges + m);
    
    memset(h, -1, sizeof h);
    LL sum = 0; //存储最小生成树的权值之和，方便后面比较次小生成树
    //kruskal先求出最小生成树
    for (int i = 0; i < m; ++i) {
        int a = edges[i].a, b = edges[i].b, c = edges[i].c;
        if (find(a) != find(b)) {
            edges[i].is_tree = true;
            p[find(a)] = find(b);
            sum += c;
            add(a, b, c), add(b, a, c); //作为已经存在于最小生成树中的边，建图，方便后续找环删最长边
        }
    }
    
    //预处理最小生成树中，任意两点之间路径中的最长边的长度
    for (int i = 1; i <= n; ++i) dfs(i, -1, 0, 0, dist1[i], dist2[i]);
    
    LL res = 1e18;
    //枚举加进来的非树边
    for (int i = 0; i < m; ++i) {
        if (!edges[i].is_tree) {
            int a = edges[i].a;
            int b = edges[i].b;
            int c = edges[i].c;
            
            int d = dist1[a][b];
            if (d == c) d = dist2[a][b];
            //因为是严格次小生成树，因此删去和添加的边长不能相等，不然就没变化
            res = min(res, sum - d + c);
        }
    }
    cout << res << endl;
    
    return 0;
}
```