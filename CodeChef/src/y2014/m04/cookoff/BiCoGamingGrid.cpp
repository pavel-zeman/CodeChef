// Find the number in current column, which is lower than or equal to g
// http://www.codechef.com/COOK45/problems/BICO
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100

long long int data[MAX_N][MAX_N];

long long int result[MAX_N];
int resCount = 0;

char c = 0;
long long int getInt() {
    long long int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}


int main(void) {
    FOR(i, MAX_N) {
        data[i][0] = 1;
        data[i][i] = 1;
        FORE(j, 1, i) data[i][j] = data[i - 1][j - 1] + data[i - 1][j];
    }

    int t = getInt();
    FOR(tt, t) {
        getInt();
        int c = getInt();
        long long int g = getInt();
        resCount = 0;

        while (g > 0) {
            int r = c;
            while (r < MAX_N && data[r][c] <= g) r++;
            r--;
            result[resCount++] = data[r][c];
            g -= data[r][c];
            c--;
        }
        printf("%d\n", resCount);
        FOR(i, resCount) printf("%lld ", result[i]);
        printf("\n");
    }
}
