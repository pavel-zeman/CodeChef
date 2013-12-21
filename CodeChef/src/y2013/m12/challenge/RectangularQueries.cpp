// For each cell calculate counts of each number in the rectangle between top-left corner and the cell. Then simply subtract these counts.
// http://www.codechef.com/DEC13/problems/RECTQUER
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 302
#define MAX_A 11

int counts[MAX_N][MAX_N][MAX_A];

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

void copy(int *dst, int *src) {
    memcpy(dst, src, MAX_A * sizeof(int));
}

void copy(int *dst, int *src, int *add) {
    FOR(i, MAX_A) dst[i] = src[i] + add[i];
}

void add(int *dst, int *src) {
    FOR(i, MAX_A) dst[i] += src[i];
}

void sub(int *dst, int *src) {
    FOR(i, MAX_A) dst[i] -= src[i];
}

int main(void) {
    int n = getInt();
    FOR(r, n) {
        int row[MAX_A];
        memset(row, 0, sizeof(row));
        FOR(c, n) {
            row[getInt()]++;
            if (r == 0) {
                copy(counts[r][c], row);
            } else {
                copy(counts[r][c], counts[r - 1][c], row);
            }
        }
    }

    int q = getInt();
    FOR(i, q) {
        int x1 = getInt() - 1, y1 = getInt() - 1, x2 = getInt() - 1, y2 = getInt() - 1;
        int result[MAX_A];
        copy(result, counts[x2][y2]);
        if (x1 > 0) sub(result, counts[x1 - 1][y2]);
        if (y1 > 0) sub(result, counts[x2][y1 - 1]);
        if (x1 > 0 && y1 > 0) add(result, counts[x1 - 1][y1 - 1]);
        int c = 0;
        FOR(i, MAX_A) c += result[i] > 0;
        printf("%d\n", c);
    }
}
