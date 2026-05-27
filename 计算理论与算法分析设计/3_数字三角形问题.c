/**
 * 数字三角形问题 - 动态规划
 *
 * 问题：给定n行数字三角形，从顶至底找一条路径使数字和最大。
 * 每次只能向下走到正下方或右下方。
 *
 * 解：自底向上DP。dp[i][j] = a[i][j] + max(dp[i+1][j], dp[i+1][j+1])
 * 由于只需要上一行数据，可以原地修改三角形数组，空间O(n^2)或压缩为O(n)。
 */
#include <stdio.h>

#define MAX_N 100

int a[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            scanf("%d", &a[i][j]);

    /* 初始化最底层 */
    for (int j = 0; j < n; j++)
        dp[n - 1][j] = a[n - 1][j];

    /* 自底向上递推 */
    for (int i = n - 2; i >= 0; i--)
        for (int j = 0; j <= i; j++)
            dp[i][j] = a[i][j] + max(dp[i + 1][j], dp[i + 1][j + 1]);

    printf("%d\n", dp[0][0]);

    return 0;
}
