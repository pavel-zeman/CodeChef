// Brute force algorithm, which checks all the elementary squares 
// http://www.codechef.com/COOK42/problems/CAKE1AM
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_X 1002

bool cake[MAX_X][MAX_X];

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
    int t = getInt();
    FOR(tt, t) {
        FOR(i, MAX_X) FOR(j, MAX_X) cake[i][j] = true;

        int total = 0;
        int x1 = getInt();
        int y1 = getInt();
        int x2 = getInt();
        int y2 = getInt();
        FORE(i, x1, x2) FORE(j, y1, y2) { cake[i][j] = false; }
        total = (x2 - x1) * (y2 - y1);

        x1 = getInt();
        y1 = getInt();
        x2 = getInt();
        y2 = getInt();
        FORE(i, x1, x2) FORE(j, y1, y2) if (cake[i][j]) { cake[i][j] = false; total++;}

        printf("%d\n", total);
    }
}

