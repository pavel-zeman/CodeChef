#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXC 1001

char c = 0;
int getInt() {
    int r = 0;
    while (c < '0' || c > '9') c = getc(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc(stdin);
    }
    return r;
}

double comb[MAXC][MAXC];

double calc(int s, int n, int m, int k) {
    if (k > m - 1) return 0;
    if (n - k - 1 > s - m) return 0;
    return comb[m - 1][k] * comb[s - m][n - k - 1] / comb[s - 1][n - 1];
}

int main(void) {
    FOR(i, MAXC) {
        comb[i][i] = comb[i][0] = 1;
        FORE(j, 1, i) comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }

    int t = getInt();
    FOR(i, t) {
        int s = getInt();
        int n = getInt();
        int m = getInt();
        int k = getInt();

        double res = 0;
        FORE(j, k, n) res += calc(s, n, m, j);
        printf("%.10lf\n", res);
    }
}
