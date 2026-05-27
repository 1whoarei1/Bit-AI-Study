/**
 * 石子合并问题 - 动态规划（环形区间DP）
 *
 * 问题：圆形操场四周摆放n堆石子，每次合并相邻两堆，得分为合并后的石子数。
 * 求合并成一堆的最小得分和最大得分。
 *
 * 解：将环形转换为长度为2n的线性数组（破环成链），
 * dp_min[i][j]和dp_max[i][j]表示合并区间[i..j]的最小/最大得分。
 * dp[i][j] = min/max(dp[i][k] + dp[k+1][j] + sum[i..j]), i <= k < j
 * 最终答案为 min/max(dp[i][i+n-1]), i = 0..n-1。
 * 时间复杂度O(N^3)，空间复杂度O(N^2)。
 */
#include <stdio.h>
#include <limits.h>

#define MAX_N 100

/* a[0..2n-1] 复制一份线性序列，用来模拟环形 */
int a[2 * MAX_N];
/* sum[i] = a[0] + ... + a[i-1]，用于快速求区间和 */
int sum[2 * MAX_N + 1];
/* dp_min[i][j]：合并区间[i..j]的最小得分 */
int dp_min[2 * MAX_N][2 * MAX_N];
/* dp_max[i][j]：合并区间[i..j]的最大得分 */
int dp_max[2 * MAX_N][2 * MAX_N];

/* 简单封装，便于阅读转移方程 */
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int main() {
    int n;
    /* 输入石子堆数量 n */
    scanf("%d", &n);

    /* 读入并复制一份，a[i+n] = a[i] 将环摊平成链 */
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i + n] = a[i];
    }

    int m = 2 * n;
    /* 构建前缀和，sum[i] 表示前 i 个元素之和 */
    sum[0] = 0;
    for (int i = 1; i <= m; i++)
        sum[i] = sum[i - 1] + a[i - 1];

    /* 初始化：单个石子堆不需要合并，得分为0；其他区间先置为极值 */
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            dp_min[i][j] = (i == j) ? 0 : INT_MAX;
            dp_max[i][j] = 0;
        }
    }

    /* 区间DP：按区间长度递增 */
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < m; i++) {
            int j = i + len - 1;
            /* 区间[i..j]的石子总数，作为本次合并的新增得分 */
            int total = sum[j + 1] - sum[i];
            /* 枚举分割点 k，将[i..j]分为[i..k]与[k+1..j] */
            for (int k = i; k < j; k++) {
                dp_min[i][j] = min(dp_min[i][j],
                    dp_min[i][k] + dp_min[k + 1][j] + total);
                dp_max[i][j] = max(dp_max[i][j],
                    dp_max[i][k] + dp_max[k + 1][j] + total);
            }
        }
    }

    /* 在所有长度为 n 的区间中取最小/最大值作为环形答案 */
    int ans_min = INT_MAX, ans_max = 0;
    for (int i = 0; i < n; i++) {
        ans_min = min(ans_min, dp_min[i][i + n - 1]);
        ans_max = max(ans_max, dp_max[i][i + n - 1]);
    }

    /* 输出最小得分和最大得分 */
    printf("%d\n%d\n", ans_min, ans_max);

    return 0;
}
