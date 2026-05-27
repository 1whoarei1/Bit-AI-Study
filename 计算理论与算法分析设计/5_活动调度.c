/**
 * 活动调度（最少教室数）
 *
 * 每个活动是一个半开区间 [S, F)，表示从 S 开始到 F 结束（不含 F）。
 * 任意时刻同时进行的活动数 = 需要的教室数。
 * 因此答案 = 最大重叠数。
 *
 * 做法：
 * 1) 分别排序所有开始时间和结束时间。
 * 2) 双指针扫描：
 *    - 若下一次开始时间 < 当前最早结束时间，说明新活动开始，教室数 +1。
 *    - 否则说明有活动结束，教室数 -1，结束指针右移。
 * 3) 扫描过程中记录教室数的最大值。
 ### 输入样例

```
11
1 4
3 5
0 6
5 7
3 8
5 9
6 10
8 11
8 12
2 13
12 14
```

### 输出样例

```
5
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

/* starts[i] 记录第 i 个活动的开始时间 */
static int starts[MAX_N];
/* finishes[i] 记录第 i 个活动的结束时间 */
static int finishes[MAX_N];

/* qsort 比较函数：从小到大排序 */
static int compare_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

int main(void) {
    int n;

    /* 读取活动数 n */
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    /* 读入每个活动的起止时间 */
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &starts[i], &finishes[i]);
    }

    /* 分别排序所有开始时间和结束时间 */
    qsort(starts, n, sizeof(starts[0]), compare_int);
    qsort(finishes, n, sizeof(finishes[0]), compare_int);

    /* 双指针扫描：i 指向下一次开始，j 指向下一次结束 */
    int i = 0;
    int j = 0;
    /* rooms 为当前占用教室数，answer 记录最大值 */
    int rooms = 0;
    int answer = 0;

    /* 扫描所有开始时间，更新最大并发数 */
    while (i < n) {
        if (starts[i] < finishes[j]) {
            /* 有新活动开始，占用一个教室 */
            rooms++;
            if (rooms > answer) {
                answer = rooms;
            }
            i++;
        } else {
            /* 有活动结束，释放一个教室 */
            rooms--;
            j++;
        }
    }

    /* 输出最少教室数 */
    printf("%d\n", answer);

    return 0;
}
