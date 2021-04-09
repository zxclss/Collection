# **判断存在`欧拉回路`的方法**
1. **`无向`图**
   1. 所有点的`度数`必须是`偶数`
   2. 所有边连通
2. **`有向`图**
   1. 所有点的`入度`等于`出度`
   2. 所有边连通

## 模板题
Code：
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 10, M = 4e5 + 10;
int n, m, type;
int h[N], e[M], ne[M], idx;
bool used[M]; //记录当前路径是否用过，剪枝用的
int ind[N], outd[N];
int path[M], cnt;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void dfs(int u) {
    for (int &i = h[u]; ~i; ) {
        //如果这条边被用过了，就把它删去
        if (used[i]) {
            i = ne[i];
            continue;
        }
        used[i] = true; //标记为true，便于其他的点也把这条路删掉
        if (type == 1) used[i ^ 1] = true; //无向图要删来去两条路
        
        int t;
        if (type == 1) {
            t = i / 2 + 1; //无向图的边是两个两个存的
            if (i & 1) t = -t; //奇数边存的是反向边
        } else t = i + 1; //有向图直接得出
        
        int j = e[i];
        i = ne[i];
        dfs(j);
        
        path[++cnt] = t;
    }
}
int main() {
    memset(h, -1, sizeof h);
    cin >> type >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        if (type == 1) add(b, a); //无向边的读入
        ++ind[b], ++outd[a];
    }
    //检查无向图（所有点度数必须是偶数）
    if (type == 1) {
        for (int i = 1; i <= n; ++i) {
            if (ind[i] + outd[i] & 1) {
                puts("NO");
                return 0;
            }
        }
    }
    //检查有向图（所有点入度等于出度）
    if (type == 2) {
        for (int i = 1; i <= n; ++i) {
            if (ind[i] != outd[i]) {
                puts("NO");
                return 0;
            }
        }
    }
    //寻找欧拉回路
    for (int i = 1; i <= n; ++i)
        if (h[i] != -1) {  //非孤立点，找出他的欧拉回路
            dfs(i);
            break;
        }
    //有不在答案上的边，就说明不存在欧拉回路
    if (cnt < m) {
        puts("NO");
        return 0;
    }
    puts("YES");
    for (int i = cnt; i; --i) cout << path[i] << " ";
    cout << endl;
    return 0;
}
```