/**
 * 2-8 查找固定点 (T[i] = i)
 *
 * 问题：n个不同整数排好序后存于T[1:n]中。
 * 若存在下标i(1≤i≤n)使得T[i]=i，设计O(log n)算法找到该下标。
 *
 * 思路：二分查找变体。
 * - 若T[mid]==mid，找到目标。
 * - 若T[mid]>mid，右侧所有元素T[j]≥T[mid]+(j-mid)>mid+(j-mid)=j，
 *   故右侧不可能存在T[j]=j，搜索左半部分。
 * - 若T[mid]<mid，左侧所有元素T[j]≤T[mid]-(mid-j)<mid-(mid-j)=j，
 *   故左侧不可能存在T[j]=j，搜索右半部分。
 *
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)
 */
#include <stdio.h>

/**
 * 在有序数组T[left..right]中查找下标i使得T[i]==i
 * 返回值：若存在返回下标，否则返回-1
 * 注意：此处使用1-based下标（与题目一致），调用时传入(1, n)
 */
int findFixedPoint(int T[], int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (T[mid] == mid) {
            return mid;
        } else if (T[mid] > mid) {
            /* T[mid] > mid，右侧不可能有T[j] == j */
            right = mid - 1;
        } else {
            /* T[mid] < mid，左侧不可能有T[j] == j */
            left = mid + 1;
        }
    }
    return -1; /* 不存在 */
}

int main() {
    int n;
    printf("请输入数组长度n: ");
    scanf("%d", &n);

    int T[n + 1]; /* 1-based, T[0]不用 */
    printf("请输入%d个排好序的不同整数:\n", n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &T[i]);

    int result = findFixedPoint(T, 1, n);

    if (result != -1)
        printf("找到固定点: T[%d] = %d\n", result, T[result]);
    else
        printf("不存在固定点\n");

    return 0;
}
