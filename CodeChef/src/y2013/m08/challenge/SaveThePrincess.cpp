// Dynamic programming with probability matrix containing probability of sum at least X when starting at position Y
// http://www.codechef.com/AUG13/problems/SHIRO
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 110
#define MAX_TOTAL 5100

double p[MAX_N];
int a[MAX_N];
int n;

double prob[MAX_N][MAX_TOTAL]; // probability, that when starting at position i, the sum will be at least j

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

double calc(int position, int value) {
    if (value <= 0) return 1;
    if (position == n) return 0;
    if (prob[position][value] < 0) {
        prob[position][value] = p[position] * calc(position + 1, value - a[position]) + (1 - p[position]) * calc(position + 1, value);
    }
    return prob[position][value];
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) a[i] = getInt();
        FOR(i, n) p[i] = getInt() / 100.0;

        int total = 0;
        FOR(i, n) total += a[i];
        total = total / 2 + total % 2;
        FOR(i, n) FOR(j, total + 1) prob[i][j] = -1;

        printf("%lf\n", calc(0, total));
    }
}
