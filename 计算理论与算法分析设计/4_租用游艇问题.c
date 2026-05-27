/**
 * 租用游艇问题 - 动态规划（DAG最短路径）
 *
 * 问题：长江上有n个游艇出租站，从站i到站j租金为r(i,j)，i<j。
 * 求从站1到站n的最少租金。
 *
 * 解：dp[j] = min(dp[i] + r(i,j)) for all i < j
 * 其中dp[1]=0，表示从起点出发不花钱。
 * 这是DAG上的最短路径问题，按拓扑序递推即可。
 * 时间复杂度O(n^2)，空间复杂度O(n^2)。
 */
#include <stdio.h>
#include <limits.h>

#define MAX_N 200
#define INF INT_MAX

int r[MAX_N + 1][MAX_N + 1];
int dp[MAX_N + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            scanf("%d", &r[i][j]);
        }
    }

    dp[1] = 0;
    for (int i = 2; i <= n; i++)
        dp[i] = INF;

    for (int j = 2; j <= n; j++) {
        for (int i = 1; i < j; i++) {
            if (dp[i] != INF && r[i][j] != 0)
                dp[j] = min(dp[j], dp[i] + r[i][j]);
        }
    }

    printf("%d\n", dp[n]);

    return 0;
}
