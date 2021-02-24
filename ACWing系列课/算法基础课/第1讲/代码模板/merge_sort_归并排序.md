```C++
void merge_sort(int list [], int left, int right) {
    //terminator
    if (left == right) return;
    int midIndex = left + right >> 1;
    //drill down
    merge_sort(left, midIndex);
    merge_sort(midIndex + 1, right);
    //merge sorted array
    int i1 = left, i2 = midIndex + 1, k = 0;
    while (i1 <= midIndex && i2 <= right) {
        if (list[i1] <= list[i2]) temp[k++] = list[i1++];
        else temp[k++] = list[i2++];
    }
    while (i1 <= midIndex) temp[k++] = list[i1++];
    while (i2 <= right) temp[k++] = list[i2++];
    //replace
    for (int i = 0; i < k; ++i) list[left + i] = temp[i];
    return;
}
```

