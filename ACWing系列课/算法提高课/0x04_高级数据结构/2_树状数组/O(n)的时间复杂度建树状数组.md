# 第一种 $O(n\log n)$

```c++
for (int i = 1; i <= n; ++i)
	add(a[i], 1);
```



# 第二种 $O(n)$

```c++
for (int i = 1; i <= n; ++i)
{
    s[i] = a[i] + s[i - 1];
    tr[i] = s[i] - s[i - lowbit(i)];
}
```



# 第三种 $O(n)$

```c++
for (int x = 1; x <= n; ++i)
    for (int i = x - 1; i >= x - lowbit(x) + 1; i -= lowbit(i))
        tr[x] += tr[i];
```

