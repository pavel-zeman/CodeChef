// Just simple brute-force solution
// http://www.codechef.com/FEB14/problems/LMATRIX
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 230

int data[MAX_N][MAX_N];

int n, m;

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


int main(void) {
    n = getInt();
    m = getInt();

    int total = 0;
    FOR(i, n) FOR(j, m) {
        data[i][j] = getInt();
        total += data[i][j];
    }
    printf("%d\n", total);
    FOR(i, n) FOR(j, m) {
        if (data[i][j] == 1) {
            printf("%d %d %d %d\n", i + 1, j + 1, i + 1, j + 1);
        }
    }
}