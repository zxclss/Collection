`a[p] ^ a[p+1] ^ ... ^ a[N] ^ x = s[p-1] ^ s[N] ^ x`

```c++
#include <iostream>

using namespace std;

const int N = 6e5 + 10, M = N * 24;
int n, m;
int root[N]; //记录版本号
int tr[M][2], idx; //trie树
int max_id[M]; //记录每个trie树结点对应的子树中的最大版本号
int s[N]; //前缀和

//i是当前正在操作的版本号,k是当前正在处理的是第k位,prev是上一个版本,curr是当前版本
void insert(int i, int k, int prev, int curr)
{
    if (k < 0)
    {
        max_id[curr] = i;
        return;
    }
    int v = s[i] >> k & 1;
    //如果上个版本的当前节点存在，就把他其他子树拷贝过来
    if (prev) tr[curr][v ^ 1] = tr[prev][v ^ 1];
    tr[curr][v] = ++ idx;
    insert(i, k - 1, tr[prev][v], tr[curr][v]);
    max_id[curr] = max(max_id[tr[curr][0]], max_id[tr[curr][1]]);
}
int query(int root, int L, int C)
{
    int p = root;
    for (int i = 23; i>= 0; -- i)
    {
        int v = C >> i & 1;
        if (max_id[tr[p][v ^ 1]] >= L) p = tr[p][v ^ 1];
        else p = tr[p][v];
    }
    return C ^ s[max_id[p]];
}
int main()
{
    scanf("%d%d", &n, &m);
    
    max_id[0] = -1; //初始是最小的版本号
    root[0] = ++ idx;
    insert(0, 23, 0, root[0]);
    
    for (int i = 1; i <= n; ++ i)
    {
        scanf("%d", &s[i]);
        s[i] ^= s[i - 1];
        root[i] = ++ idx;
        insert(i, 23, root[i - 1], root[i]);
    }
    char op[2];
    int l, r, x;
    while (m -- )
    {
        scanf("%s", op);
        if (*op == 'A')
        {
            scanf("%d", &x);
            s[ ++ n] = x;
            s[n] ^= s[n - 1];
            root[n] = ++ idx;
            insert(n, 23, root[n - 1], root[n]);
        }
        else
        {
            scanf("%d%d%d", &l, &r, &x); //l-1 <= p-1 <= r-1
            printf("%d\n", query(root[r - 1], l - 1, x ^ s[n]));
        }
    }
    return 0;
}

```