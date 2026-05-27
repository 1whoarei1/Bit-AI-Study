/**
 * 矩阵链乘问题 - 动态规划
 *
 * 问题：给定N个矩阵的维度序列p[0..N]（第k个矩阵为p[k-1]×p[k]），
 * 求最优加括号方式使乘法代价最小。
 *
 * 解：m[i][j] = min(m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j])  i<=k<j
 * s[i][j]记录分割点用于重构括号方案。
 * 时间复杂度O(N^3)，空间复杂度O(N^2)。
 */
#include <stdio.h>
#include <limits.h>

#define MAX_N 100

/* p[0..N] 存矩阵维度序列：第 i 个矩阵 A_i 为 p[i-1] x p[i] */
int p[MAX_N + 1];
/* m[i][j] 表示 A_i..A_j 的最小乘法代价（标量乘法次数） */
long long m[MAX_N + 1][MAX_N + 1];
/* s[i][j] 记录使 m[i][j] 取最小的分割点 k */
int s[MAX_N + 1][MAX_N + 1];

void print_paren_inner(int i, int j) {
    if (i == j) {
        printf("A%d", i);
        return;
    }
    /* 递归按最优分割点 s[i][j] 输出括号结构 */
    printf("(");
    print_paren_inner(i, s[i][j]);
    print_paren_inner(s[i][j] + 1, j);
    printf(")");
}

void print_paren(int i, int j) {
    if (i == j) {
        printf("(A%d)", i);
        return;
    }
    print_paren_inner(i, j);
}

int main() {
    int N;
    /* 输入矩阵个数 N */
    scanf("%d", &N);

    /* 输入维度序列 p[0..N] */
    for (int i = 0; i <= N; i++)
        scanf("%d", &p[i]);

    /* m[i][i] = 0，单个矩阵无需乘法 */
    for (int i = 1; i <= N; i++)
        m[i][i] = 0;

    /* 按区间长度 len 从小到大进行动态规划 */
    for (int len = 2; len <= N; len++) {
        /* 枚举区间起点 i，终点 j = i + len - 1 */
        for (int i = 1; i <= N - len + 1; i++) {
            int j = i + len - 1;
            /* 初始化为无穷大，便于取最小值 */
            m[i][j] = LLONG_MAX;
            /* 尝试所有分割点 k，将区间 [i, j] 分为 [i, k] 和 [k+1, j] */
            for (int k = i; k < j; k++) {
                /* 代价 = 左区间 + 右区间 + 合并代价 */
                long long cost = m[i][k] + m[k + 1][j]
                    + (long long)p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    /* 输出最小代价 */
    printf("%lld\n", m[1][N]);
    /* 输出对应的最优括号方案 */
    print_paren(1, N);
    printf("\n");

    return 0;
}
