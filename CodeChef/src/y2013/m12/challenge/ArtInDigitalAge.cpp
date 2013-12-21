// "Hungry" algorithm - tries to find the largest rectangles starting from the top left corner
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

int color[MAX_N][MAX_N];

int n;

struct ResultItem {
    int c;
    int u, d, l, r;
} result[MAX_N * MAX_N];

int resultSize = 0;

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

void addResult(int c, int u, int d, int l, int r) {
    result[resultSize].c = c;
    result[resultSize].u = u + 1;
    result[resultSize].d = d + 1;
    result[resultSize].l = l + 1;
    result[resultSize].r = r + 1;
    resultSize++;
}

int main(void) {
    n = getInt();
    int num = 0;
    FOR(i, n) FOR(j, n) {
        if ((color[i][j] = getInt()) != 0) num++;
    }
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
            addResult(c, i, i + maxHeight - 1, j, j + maxWidth - 1);
        }
    }


    printf("%d\n", resultSize);
    FOR(i, resultSize) printf("%d %d %d %d %d\n", result[i].c, result[i].u, result[i].d, result[i].l, result[i].r);
    /*FOR(i, n) FOR(j, n) if (color[i][j] != 0) {
        printf("%d %d %d %d %d\n", color[i][j], i + 1, i + 1, j + 1, j + 1);
    }*/
}

