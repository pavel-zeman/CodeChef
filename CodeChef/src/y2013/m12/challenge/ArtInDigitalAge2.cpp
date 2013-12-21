// The same algorithm as for the previous version, but additionally tries all four possible rotations (and then starts the search from the top left corner)
// http://www.codechef.com/DEC13/problems/SMPAINT
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1010

int colorSource[MAX_N][MAX_N];

int colorTemp[MAX_N][MAX_N];
int color[MAX_N][MAX_N];

int n;

struct ResultItem {
    int c;
    int u, d, l, r;
} result[4][MAX_N * MAX_N];

int resultSize[4];

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

void rotate(int count, int *i, int *j) {
    //printf("Rotating %d %d %d times\n", *i, *j, count);
    FOR(c, count) {
        int a = *j;
        int b = n - *i - 1;
        *i = a;
        *j = b;
    }
    //printf("Rotating result: %d %d\n", *i, *j);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void addResult(int r, int c, int u, int d, int l, int rr) {
    int size = resultSize[r];
    result[r][size].c = c;
    result[r][size].u = u;
    result[r][size].d = d;
    result[r][size].l = l;
    result[r][size].r = rr;
    rotate(r, &result[r][size].u, &result[r][size].l);
    rotate(r, &result[r][size].d, &result[r][size].r);
    if (result[r][size].u > result[r][size].d) swap(&result[r][size].u, &result[r][size].d);
    if (result[r][size].l > result[r][size].r) swap(&result[r][size].l, &result[r][size].r);

    resultSize[r]++;
}

void rotate(int count) {
    FOR(c, count) {
        FOR(i, n) FOR(j, n) colorTemp[i][j] = color[i][j];
        FOR(i, n) FOR(j, n) color[i][j] = colorTemp[j][n - i - 1];
    }
}

int main(void) {
    n = getInt();
    FOR(i, n) FOR(j, n) {
        colorSource[i][j] = getInt();
    }
    FOR(r, 4) {
        resultSize[r] = 0;
        FOR(i, n) FOR(j, n) color[i][j] = colorSource[i][j];
        rotate(r);

        FOR(i, n) FOR(j, n) {
            if (color[i][j] != 0) {
                int c = color[i][j];
                int maxSize = 0;
                int maxWidth = 0;
                int maxHeight = 0;
                int maxY = j;
                while (maxY < n && color[i][maxY] == c) maxY++;

                int x = i;
                while (x < n && color[x][j] == c) {
                    int y = j;
                    while (y < maxY && color[x][y] == c) y++;
                    if (y < maxY) maxY = y;
                    int size = (y - j) * (x - i + 1);
                    if (size > maxSize) {
                        maxSize = size;
                        maxWidth = y - j;
                        maxHeight = x - i + 1;
                    }
                    x++;
                }
                FOR(k, maxHeight) FOR(l, maxWidth) color[i + k][j + l] = 0;
                addResult(r, c, i, i + maxHeight - 1, j, j + maxWidth - 1);
            }
        }
    }

    int minSize = resultSize[0] + 1;
    int minR = -1;
    FOR(r, 4) {
        if (resultSize[r] < minSize) minSize = resultSize[r], minR = r;
    }

    //printf("Min R: %d\n", minR);
    printf("%d\n", resultSize[minR]);
    FOR(i, resultSize[minR]) printf("%d %d %d %d %d\n", result[minR][i].c, result[minR][i].u + 1, result[minR][i].d + 1, result[minR][i].l + 1, result[minR][i].r + 1);
    /*FOR(i, n) FOR(j, n) if (color[i][j] != 0) {
        printf("%d %d %d %d %d\n", color[i][j], i + 1, i + 1, j + 1, j + 1);
    }*/
}

