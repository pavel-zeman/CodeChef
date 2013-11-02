//
// http://www.codechef.com/COOK39/problems/PPTEST
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
#define MAX_W 110

int n, w;
int points[MAX_N], time[MAX_N];

int max[MAX_N][MAX_W];

char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}


int find(int pos, int remainingTime) {
    if (pos == n) return 0;
    if (max[pos][remainingTime] != -1) return max[pos][remainingTime];
    int localMax = 0;
    if (remainingTime >= time[pos]) {
        localMax = points[pos] + find(pos + 1, remainingTime - time[pos]);
    }
    int t = find(pos + 1, remainingTime);
    if (t > localMax) localMax = t;
    return max[pos][remainingTime] = localMax;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        w = getInt();
        FOR(i, n) {
            int c = getInt();
            int p = getInt();
            time[i] = getInt();
            points[i] = c * p;
        }

        FOR(i, n + 1) FOR(j, w + 1) max[i][j] = -1;
        printf("%d\n", find(0, w));
    }
}
