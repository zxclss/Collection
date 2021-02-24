```c++
#include <iostream>
#include <unordered_map>
#include <queue>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, string> PIS;
//Dijkstra算法是A-start算法的简化版
//A-star算法是通过估计函数f(n)来判断到达终点的最短路

//估计函数f(n)的限制: f(i) <= 起点到i的最短距离

//这个估计函数可以极大的减少bfs的多余遍历，但是对于f(n)函数的构造是需要大量的积累和能力的
//A-star的别名叫做“启发式搜索”

//估计函数f(n)，本题采用的策略是“每个点到达他的正确位置的曼哈顿距离之和”
int f(string str) {
    int res = 0;
    for (int i = 0; i < 9; ++i) {
        if (str[i] != 'x') {
            int t = str[i] - '1';
            res += abs(t / 3 - i / 3) + abs(t % 3 - i % 3);
        }
    }
    return res;
}

void astar(string start) {
    string end = "12345678x";
    char op[5] = {"ruld"};
    unordered_map<string, int> dist;
    unordered_map<string, pair<char, string>> prev;
    priority_queue<PIS, vector<PIS>, greater<PIS>> heap;
    dist[start] = 0;
    heap.push({f(start), start});

    int dx[] = {0, -1, 0, 1};
    int dy[] = {1, 0, -1, 0};

    while (!heap.empty()) {
        PIS t = heap.top();
        heap.pop();

        if (t.y == end) break;

        //找到x在序列中的位置
        int a, b;
        for (int i = 0; i < 9; ++i)
            if (t.y[i] == 'x') {
                a = i / 3;
                b = i % 3;
                break;
            }
        for (int i = 0; i < 4; ++i) {
            int x = a + dx[i], y = b + dy[i];
            if (x < 0 || x >= 3  || y < 0 || y >= 3) continue;

            string temp = t.y;
            swap(temp[x * 3 + y], temp[a * 3 + b]);

            int d = dist[t.y] + 1;
            if (!dist.count(temp) || dist[temp] > d) {
                dist[temp] = d;
                prev[temp] = {op[i], t.y};
                heap.push({dist[temp] + f(temp), temp});    //估计值是距离累加上f(n)的
            }
        }
    }
    string path;
    while (end != start) {
        path += prev[end].x;
        end = prev[end].y;
    }
    reverse(path.begin(), path.end());
    cout << path << endl;
}
int main() {
    string x, start, seq;
    while (cin >> x){
        start += x;
        if (x != "x") seq += x;
    }
    //左右移动不改变逆序对数，上下移动每次都会改变2个逆序对数(+2, -2, -1+1, +1-1)
    //因此八数码的操作是不会改变棋盘中逆序对的奇偶性的
    //而我们的终点state “12345678”的逆序对数是0
    //如果我们的起点state 的逆序对数非偶数，可以直接输出 unsolvable
    int t = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = i + 1; j < 8; ++j)
            if (seq[j] > seq[i])
                ++t;
    if (t & 1) puts("unsolvable");
    else astar(start);
    return 0;
}
```

