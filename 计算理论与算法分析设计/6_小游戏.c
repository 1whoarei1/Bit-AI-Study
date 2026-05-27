/**
 * 树上的策略游戏（最小顶点覆盖）
 *
 * 说明：在树上放置士兵，士兵可覆盖其相邻的所有边。
 *      要求覆盖树上所有边，求最少士兵数。
 *
 * 等价问题：树的最小顶点覆盖。
 *
 * 状态定义：
 * dp0[u]：以 u 为根的子树中，当 u 不选时的最少士兵数
 * dp1[u]：以 u 为根的子树中，当 u 选时的最少士兵数
 */
#include <stdio.h>

#define MAX_N 1500
#define MAX_EDGE (2 * MAX_N)
#define BUFFER_SIZE (1 << 16)

/* 邻接表：head[u] 指向 u 的第一条边下标 */
static int head[MAX_N];
/* to[e] 表示第 e 条边的终点 */
static int to[MAX_EDGE];
/* next_edge[e] 表示同一出发点的下一条边 */
static int next_edge[MAX_EDGE];
static int edge_count;
/* 树形 DP 数组 */
static int dp0[MAX_N];
static int dp1[MAX_N];

/* 快速输入缓冲 */
static char buffer[BUFFER_SIZE];
static int buffer_pos = 0;
static int buffer_len = 0;

/* 从缓冲区读取一个字符，必要时刷新缓冲区 */
static int read_char(void) {
    if (buffer_pos >= buffer_len) {
        buffer_len = (int)fread(buffer, 1, BUFFER_SIZE, stdin);
        buffer_pos = 0;
        if (buffer_len == 0) {
            return EOF;
        }
    }
    return (unsigned char)buffer[buffer_pos++];
}

/* 读取下一个整数（跳过非数字字符），成功返回 1，失败返回 0 */
static int next_int(int *value) {
    int c = read_char();
    int sign = 1;
    int result = 0;

    while (c != EOF && (c < '0' || c > '9') && c != '-') {
        c = read_char();
    }
    if (c == EOF) {
        return 0;
    }

    if (c == '-') {
        sign = -1;
        c = read_char();
    }

    while (c >= '0' && c <= '9') {
        result = result * 10 + (c - '0');
        c = read_char();
    }

    *value = sign * result;
    return 1;
}

/* 求最小值 */
static int min_int(int a, int b) {
    return a < b ? a : b;
}

/* 初始化图：将邻接表头设置为 -1 */
static void init_graph(int n) {
    edge_count = 0;
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
}

/* 加一条无向边（调用两次构成双向） */
static void add_edge(int u, int v) {
    to[edge_count] = v;
    next_edge[edge_count] = head[u];
    head[u] = edge_count++;
}

/* 树形 DP：以 parent 为父节点进行深度优先遍历 */
static void dfs(int u, int parent) {
    /* 不选 u，则必须选所有子节点才能覆盖边 (u, v) */
    dp0[u] = 0;
    /* 选 u，则子节点可选可不选，取更小的 */
    dp1[u] = 1;

    for (int e = head[u]; e != -1; e = next_edge[e]) {
        int v = to[e];
        if (v == parent) {
            continue;
        }

        dfs(v, u);
        dp0[u] += dp1[v];
        dp1[u] += min_int(dp0[v], dp1[v]);
    }
}

int main(void) {
    int n;

    /* 输入格式可能包含括号、冒号等符号，next_int 会自动跳过非数字字符 */
    while (next_int(&n)) {
        init_graph(n);

        /* 读取每个节点的邻接信息，构建无向树 */
        for (int i = 0; i < n; i++) {
            int u;
            int degree;

            next_int(&u);
            next_int(&degree);

            for (int j = 0; j < degree; j++) {
                int v;

                next_int(&v);
                add_edge(u, v);
                add_edge(v, u);
            }
        }

        /* 默认以 0 号点为根进行 DP */
        dfs(0, -1);
        /* 根选或不选取最小值 */
        printf("%d\n", min_int(dp0[0], dp1[0]));
    }

    return 0;
}
