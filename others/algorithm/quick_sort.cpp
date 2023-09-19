void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
void quickSort(int a[], int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = right;
    while (i < j)
    {
        while (j > i && a[j] >= a[left])
            j--;
        while (i < j && a[i] <= a[left])
            i++;
        swap(a[i], (i == j) ? a[left] : a[j]); // i和j相遇则与枢轴元素交换，否则a[i]与a[j]交换
    }
    quickSort(a, left, i - 1);
    quickSort(a, j + 1, right);
}
// 数组直到下标为k（包括k）即最大的
void quickSortTopK(int a[], int left, int right, int k)
{
    if (left >= right)
        return;
    int i = left, j = right;
    while (i < j)
    {
        while (j > i && a[j] >= a[left])
            j--;
        while (i < j && a[i] <= a[left])
            i++;
        swap(a[i], (i == j) ? a[left] : a[j]); // i和j相遇则与枢轴元素交换，否则a[i]与a[j]交换
    }
    if (i == k)
        return;
    else if (i > k)
        quickSortTopK(a, left, i - 1, k);
    else
        quickSortTopK(a, j + 1, right, k);
}