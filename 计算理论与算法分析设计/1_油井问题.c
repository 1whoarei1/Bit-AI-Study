/**
 * 油井问题 - 使用线性时间选择算法求中位数
 *
 * 问题：主油管道为东西向，确定主油管道的南北位置(Y坐标)，
 * 使南北向油井喷油管道距离和最小。
 *
 * 解：Y坐标的中位数即为最优位置。使用快速选择算法(Quickselect)
 * 在O(n)时间内找到第k小的元素。
 *
 * 注意：不允许使用快速排序，必须线性时间完成。
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 2000000

int y[MAX_N];

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/* 三数取中划分，返回pivot的最终位置 */
int partition(int arr[], int left, int right) {
    int mid = left + (right - left) / 2;
    if (arr[left] > arr[mid]) swap(&arr[left], &arr[mid]);
    if (arr[left] > arr[right]) swap(&arr[left], &arr[right]);
    if (arr[mid] > arr[right]) swap(&arr[mid], &arr[right]);

    int pivot = arr[mid];
    swap(&arr[mid], &arr[right]);

    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]);
    return i;
}

/* 快速选择：在arr[left..right]中查找第k小的元素（k从0开始） */
int quickselect(int arr[], int left, int right, int k) {
    while (left <= right) {
        if (left == right) return arr[left];

        int pivot_idx = partition(arr, left, right);

        if (k == pivot_idx)
            return arr[k];
        else if (k < pivot_idx)
            right = pivot_idx - 1;
        else
            left = pivot_idx + 1;
    }
    return arr[left];
}

int main() {
    int x, y_val;
    int n = 0;

    while (scanf("%d,%d", &x, &y_val) != EOF) {
        y[n++] = y_val;
    }

    if (n == 0) return 0;

    /* 中位数索引：若n为奇数，中位数为第n/2个(0-based)；
       若n为偶数，题目要求输出最小值，输出第n/2-1个 */
    int k = (n - 1) / 2;
    int result = quickselect(y, 0, n - 1, k);

    printf("%d\n", result);

    return 0;
}
