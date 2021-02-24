

```C++
const int N = 1e5 + 10;
int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dist [N];
bool st[N];     //st数组是用来记录当前这个结点是否已在队列中
								//不是用来记录这个结点最短路径是否已被找到（区别于Dijkstra算法中st的作用）

int spfa() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    st[1] = true;
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        st[t] = false;            //队首出队以后，更新st
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {     //这个更新过的结点是否在队列中？ 如果在就不加了，不在就加进去
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    if (dist[n] == 0x3f3f3f3f) return -1;
    else return dist[n];
}
```

