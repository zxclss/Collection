

```C++
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
//构成Trie树的非常重要的两点，指向子结点的指针son，还有表示当前存储字符串结束的标记**cnt**
int son[N][26], idx, cnt[N];
char str[N];

void insert(char str[]) {
    int p = 0;
    for (int i = 0; str[i]; ++i) {
        int u = str[i] - 'a';
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
    ++cnt[p];
}
int query(char str[]) {
    int p = 0;
    for (int i = 0; str[i]; ++i) {
        int u = str[i] - 'a';
        if (!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        char op[2];
        scanf("%s%s", op, str);
        if (*op == 'I') insert(str);
        else printf("%d\n", query(str));
    }
    return 0;
}
```

