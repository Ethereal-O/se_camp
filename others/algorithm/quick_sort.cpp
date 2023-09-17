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