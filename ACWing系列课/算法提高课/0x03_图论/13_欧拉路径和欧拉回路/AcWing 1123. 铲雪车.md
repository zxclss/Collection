> 引用于"哥尼斯堡七桥问题"，大一研讨课的东西(#^.^#)
1. 对于`无向图`，所有边都是连通的。
   1. 存在`欧拉路径`的`充分必要`条件：`度`数是`奇数`的`点`的个数为`0`或`2`
   2. 存在`欧拉回路`的`充分必要`条件：`度`数是`奇数`的`点`的个数为`0`
2. 对于`有向图`，所有边都是连通的。
   1. 存在`欧拉路径`的`充分必要`条件：要么所有`点`的`出度`均等于`入度`；要么除了`两个点`之外，其余所有点`出度`等于`入度`，剩余的两个点，一个满足`出度`比`入度`多1（`起点`），另一个满足`入度`比`出度`多1（`终点`）
   2. 存在`欧拉回路`的`充分必要`条件：`所有点`的`出度`均等于`入度`。

```c++
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n, m, x1, y1, x2, y2;
    cin >> n >> m;
    
    double sum = 0;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        double dx = x1 - x2;
        double dy = y1 - y2;
        sum += sqrt(dx * dx + dy * dy) * 2;
    }
    int mm = round(sum / 1000 / 20 * 60);
    int hh = mm / 60;
    mm %= 60;
    printf("%d:%02d\n", hh, mm);
    return 0;
}
```