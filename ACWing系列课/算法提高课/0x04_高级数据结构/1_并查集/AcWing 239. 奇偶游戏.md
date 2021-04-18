> 解法一：维护点到根距离的相对长度表示点和根的关系
> 解法二：利用并查集扩展域，分类同类集合和异类集合

![Xnip2021-04-12_15-43-31.jpg](https://cdn.acwing.com/media/article/image/2021/04/12/55909_a8a7a0649b-Xnip2021-04-12_15-43-31.jpg) 

# 1. 用点到根结点距离维护点与点之间的关系（异或写法）
```
#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

const int N = 20010;
int n, m;
unordered_map<int,int> S;
int p[N], d[N];

int get(int a) {
    if (!S.count(a)) S[a] = n++;
    return S[a];
}
int find(int u) {
    if (p[u] != u) {
        int t = find(p[u]);
        d[u] ^= d[p[u]];
        p[u] = t;
    }
    return p[u];
}
int main() {
    cin >> n >> m;
    n = 0;
    
    for (int i = 0; i < N; ++i) p[i] = i;
    int res = m;
    
    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        string str;
        cin >> a >> b >> str;
        a = get(a - 1), b = get(b); //前缀和Sr - Sl-1，所以需要a-1而非a
        
        int t = (str == "odd");
        int pa = find(a), pb = find(b);
        
        //还没有建立联系，则建立两者的联系
        if (pa != pb)
        {
            p[pa] = pb;
            d[pa] = d[a] ^ d[b] ^ t;
        }
        //已经建立联系，则检查联系
        else
        {
            if (d[a] ^ d[b] != t)
            {
                res = i - 1;
                break;
            }
        }
    }
    printf("%d\n", res);
    return 0;
}

```

# 2. 用点到根结点距离维护点与点之间的关系（模运算写法）
```
#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

const int N = 20010;
int n, m;
unordered_map<int,int> S;
int p[N], d[N];

int get(int a) {
    if (!S.count(a)) S[a] = n++;
    return S[a];
}
int find(int u) {
    if (p[u] != u) {
        int t = find(p[u]);
        d[u] = (d[u] + d[p[u]]) % 2;
        p[u] = t;
    }
    return p[u];
}
int main() {
    cin >> n >> m;
    n = 0;
    
    for (int i = 0; i < N; ++i) p[i] = i;
    int res = m;
    
    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        string str;
        cin >> a >> b >> str;
        a = get(a - 1), b = get(b); //前缀和Sr - Sl-1，所以需要a-1而非a
        
        int t = (str == "odd");
        int pa = find(a), pb = find(b);
        
        //还没有建立联系，则建立两者的联系
        if (pa != pb)
        {
            p[pa] = pb;
            d[pa] = (d[b] - d[a] + t) % 2;  //d[a] + d[pa] + t = d[b] mod 2
        }
        //已经建立联系，则检查联系
        else
        {
            if (((d[a] + d[b]) % 2 + 2) % 2 != t)   //因为求d[pa]用到了减法，可能出先负数问题
            {
                res = i - 1;
                break;
            }
        }
    }
    printf("%d\n", res);
    return 0;
}

```

# 3.扩展域并查集写法

> $p[x]$表示x是偶数，$p[x + Base]$表示x是奇数

```c++
#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

const int N = 40010, Base = N / 2;
int n, m;
unordered_map<int,int> S;
int p[N], d[N];

int get(int a) {
    if (!S.count(a)) S[a] = n++;
    return S[a];
}
int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}
int main() {
    cin >> n >> m;
    n = 0;
    
    for (int i = 0; i < N; ++i) p[i] = i;
    int res = m;
    
    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        string str;
        cin >> a >> b >> str;
        a = get(a - 1), b = get(b); //前缀和Sr - Sl-1，所以需要a-1而非a
        
        //a和b一奇一偶
        if (str == "odd")
        {
            if (find(a) == find(b))
            {
                res = i - 1;
                break;
            }
            p[find(a)] = find(b + Base);
            p[find(a + Base)] = find(b);
        }
        //a和b同奇偶
        else
        {
            if (find(a + Base) == find(b))
            {
                res = i - 1;
                break;
            }
            p[find(a)] = find(b);
            p[find(a + Base)] = find(b + Base);
        }
    }
    printf("%d\n", res);
    return 0;
}

```