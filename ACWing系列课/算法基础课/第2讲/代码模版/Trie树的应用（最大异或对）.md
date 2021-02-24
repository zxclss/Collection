

```C++
#include <iostream>
#include <cmath>
using namespace std;

const int N = 3e6 + 10;
int son[N][2], idx;

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; --i) {
        int u = x >> i & 1;
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
}
int query(int x) {
    int p = 0, res = 0;
    for (int i = 30; i >= 0; --i) {
        int u = x >> i & 1;
        if (son[p][!u]) {			//不能用～u代替  !1 == 0;	~1 = 11111111111111111111111111111110
            res += 1 << i;
            p = son[p][!u];
        } else {
            p = son[p][u];
        }
    }
    return res;
}

int main() {
    int n, res = 0;
    scanf("%d", &n);
    while (n--) {
        int x;
        scanf("%d", &x);
        insert(x);
        res = max(res, query(x));
    }
    printf("%d\n", res);
    return 0;
}

```

