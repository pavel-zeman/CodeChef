// Calculate maximum possible gain for each item and choose the first K items with the highest gain
// http://www.codechef.com/FEB14/problems/COLARR
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1002
#define MAX_M 1002

char c = 0;
int getInt() {
    int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int cmp(const void *p1, const void *p2) {
    return (*(int *)p2) - (*(int *)p1);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt(), m = getInt(), k = getInt();
        int a[MAX_N];
        short b[MAX_N][MAX_M];
        int v[MAX_N];

        FOR(i, n) a[i] = getInt() - 1;
        FOR(i, n) FOR(j, m) b[i][j] = getInt();
        FOR(i, n) v[i] = b[i][a[i]];

        int maxGain[MAX_N];
        int total = 0;
        FOR(i, n) {
            int mm = 0;
            total += v[i];
            FOR(j, m) mm = max(mm, b[i][j] - getInt());
            maxGain[i] = max(0, mm - v[i]);
        }

        qsort(maxGain, n, sizeof(maxGain[0]), cmp);
        FOR(i, k) total += maxGain[i];
        printf("%d\n", total);
    }
}
