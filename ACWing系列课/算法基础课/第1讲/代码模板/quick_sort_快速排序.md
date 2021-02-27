```C++
//mid取左边界的代码
void quick_sort(int list [], int left, int right) {
    if (left >= right) return;
    int mid = list[left + right >> 1];
    int pleft = left - 1, pright = right + 1;
    while (pleft < pright) {
        do ++pleft; while (list[pleft] < mid);
        do --pright; while (list[pright] > mid);
        if (pleft < pright) swap(list[pleft], list[pright]);
    }
    quick_sort(left, pright);
    quick_sort(pright + 1, right);
}
```



```C++
//mid取右边界的代码
void quick_sort(int list [], int left, int right) {
    if (left >= right) return;
    int mid = list[left + right + 1 >> 1];  //额外加1，防止死循环
    int pleft = left - 1, pright = right + 1;
    while (pleft < pright) {
        do ++pleft; while (list[pleft] < mid);
        do --pright; while (list[pright] > mid);
        if (pleft < pright) swap(list[pleft], list[pright]);
    }
    quick_sort(left, pleft - 1);  //防止取到右边界，死循环
    quick_sort(pleft, right);
}
```





https://www.acwing.com/problem/content/787/

# 787. 快速排序

给定你一个长度为n的整数数列。

请你使用快速排序对这个数列按照从小到大进行排序。

并将排好序的数列按顺序输出。

#### 输入格式

输入共两行，第一行包含整数 n。

第二行包含 n 个整数（所有整数均在1~109109范围内），表示整个数列。

#### 输出格式

输出共一行，包含 n 个整数，表示排好序的数列。

#### 数据范围

${1 \leq n \leq 100000}$

#### 输入样例：

```
5
3 1 2 4 5
```

#### 输出样例：

```
1 2 3 4 5
```

