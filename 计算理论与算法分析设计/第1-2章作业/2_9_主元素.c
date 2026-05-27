/**
 * 2-9 寻找主元素 (Majority Element)
 *
 * 问题：数组T[0:n-1]共n个元素。对元素x，S(x)={i | T[i]=x}。
 * 当|S(x)|>n/2时，称x为主元素。设计线性时间算法判断是否存在主元素。
 *
 * 思路：Boyer-Moore多数投票算法。
 * Phase 1：扫描数组，维护候选candidate和计数器count。
 *   - count==0时，将当前元素设为候选
 *   - 当前元素==candidate，count++
 *   - 当前元素!=candidate，count--
 * Phase 2：验证候选元素是否确实出现次数>n/2。
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */
#include <stdio.h>

#define MAX_N 100000

int T[MAX_N];

/**
 * 寻找主元素。若存在则返回主元素值，否则返回-1。
 */
int findMajority(int T[], int n) {
    /* Phase 1: 找候选元素 */
    int candidate = 0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (count == 0) {
            candidate = T[i];
            count = 1;
        } else if (T[i] == candidate) {
            count++;
        } else {
            count--;
        }
    }

    /* Phase 2: 验证候选元素 */
    int occurrences = 0;
    for (int i = 0; i < n; i++) {
        if (T[i] == candidate)
            occurrences++;
    }

    if (occurrences > n / 2)
        return candidate;
    else
        return -1; /* 不存在主元素 */
}

int main() {
    int n;
    printf("请输入数组长度n: ");
    scanf("%d", &n);

    printf("请输入%d个整数:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &T[i]);

    int result = findMajority(T, n);

    if (result != -1)
        printf("主元素为: %d\n", result);
    else
        printf("不存在主元素\n");

    return 0;
}
