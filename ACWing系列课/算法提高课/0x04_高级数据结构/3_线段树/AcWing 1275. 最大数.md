```c++
#include <iostream>

using namespace std;

const int N = 2e5 + 10;

int m, p;
struct Node {
    int l, r;
    int v;  //区间的最大值
}tr[N * 4];

void pushup(int u) {
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}
void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}
int query(int u, int l, int r) {
    if (l <= tr[u].l && tr[u].r <= r) return tr[u].v; //区间完全包含在内部

    int mid = tr[u].l + tr[u].r >> 1;
    int v = 0;
    if (l <= mid) v = query(u << 1, l, r);
    if (r > mid) v = max(v, query(u << 1 | 1, l, r));
    return v;
}
void modify(int u, int x, int v) {
    if (tr[u].l == tr[u].r) tr[u].v = v;
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}
int main() {
    int n = 0, last = 0;
    scanf("%d%d", &m, &p);
    build(1, 1, m);

    char op[2];
    int a;
    while (m--) {
        scanf("%s%d", op, &a);
        if (*op == 'Q') {
            last = query(1, n - a + 1, n);
            printf("%d\n", last);
        } else {
            modify(1, n + 1, (a + last) % p);
            ++n;
        }
    }
    return 0;
}
```

