### 版本1

​	当我们将区间`[l, r]`划分成`[l, mid]`和`[mid + 1, r]`时，其更新操作是`r = mid`或者`l = mid + 1`

​	计算mid时不需要加1。

```C++
bool check(int x) {/* ... */} // 检查x是否满足某种性质

int binary_search_left(int list [], int left, int right) {
    while (left < right) {
        int mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }
    return left;
}
```



### 版本2

​	当我们将区间`[l, r]`划分成`[l, mid - 1]`和`[mid, r]`时，其更新操作是`r = mid - 1`或者`l = mid`

​	此时为了防止死循环，计算mid时需要加1。

```C++
bool check(int x) {/* ... */} // 检查x是否满足某种性质

int binary_search_right(int list [], int left, int right) {
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }
    return left;
}
```



