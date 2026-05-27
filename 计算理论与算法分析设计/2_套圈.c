/**
 * 套圈问题 - 最近点对问题
 *
 * 问题：给定平面上N个点，求最大半径的圆，使得该圆恰好包含一个点。
 *
 * 解：最大半径 = 最近点对距离 / 2
 * 使用分治法在O(N log N)时间内找到最近点对距离。
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_N 100000

typedef struct {
    double x, y;
} Point;

Point pts[MAX_N];
Point temp[MAX_N];

int cmp_x(const void *a, const void *b) {
    double diff = ((Point *)a)->x - ((Point *)b)->x;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

int cmp_y(const void *a, const void *b) {
    double diff = ((Point *)a)->y - ((Point *)b)->y;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

double dist(const Point *a, const Point *b) {
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    return sqrt(dx * dx + dy * dy);
}

/* 暴力计算小规模点集的最短距离 */
double brute_force(Point p[], int left, int right) {
    double min_d = DBL_MAX;
    for (int i = left; i < right; i++) {
        for (int j = i + 1; j <= right; j++) {
            double d = dist(&p[i], &p[j]);
            if (d < min_d) min_d = d;
        }
    }
    return min_d;
}

/* 计算跨越中线的最近点对距离 */
double strip_closest(Point strip[], int size, double d) {
    double min_d = d;
    qsort(strip, size, sizeof(Point), cmp_y);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min_d; j++) {
            double dist_ij = dist(&strip[i], &strip[j]);
            if (dist_ij < min_d) min_d = dist_ij;
        }
    }
    return min_d;
}

/* 分治求最近点对距离 */
double closest_pair(int left, int right) {
    if (right - left + 1 <= 3)
        return brute_force(pts, left, right);

    int mid = left + (right - left) / 2;
    Point mid_pt = pts[mid];

    double d_left = closest_pair(left, mid);
    double d_right = closest_pair(mid + 1, right);
    double d = d_left < d_right ? d_left : d_right;

    /* 收集距离中线小于d的点 */
    int j = 0;
    for (int i = left; i <= right; i++) {
        if (fabs(pts[i].x - mid_pt.x) < d)
            temp[j++] = pts[i];
    }

    return strip_closest(temp, j, d);
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        for (int i = 0; i < n; i++)
            scanf("%lf %lf", &pts[i].x, &pts[i].y);

        qsort(pts, n, sizeof(Point), cmp_x);
        double min_dist = closest_pair(0, n - 1);

        printf("%.2f\n", min_dist / 2.0);
    }
    return 0;
}
