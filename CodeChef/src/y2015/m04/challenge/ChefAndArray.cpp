// RMQ in constant time with n*log(n) preprocessing time (see https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/)
// http://www.codechef.com/APRIL15/problems/FRMQ
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


#define MAX_N 100001
#define MAX_LOG_N 17

int rmq[MAX_LOG_N][MAX_N];
char logs[MAX_N];

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

int min(int a, int b) {
    return a < b ? a : b;
}

void preProcess(int n) {
    for (int j = 1; 1 << j <= n; j++) {
        int end = n - (1 << j) + 1;
        int step = 1 << (j - 1);
        FOR(i, end)
            rmq[j][i] = max(rmq[j - 1][i], rmq[j - 1][i + step]);
    }
}

int main(void) {
    int n = getInt();
    FOR(i, n) rmq[0][i] = getInt();
    int m = getInt();
    int x = getInt();
    int y = getInt();

    logs[0] = -1;
    FORE(i, 1, n + 1) logs[i] = logs[i - 1] + ((i & (i - 1)) == 0 ? 1 : 0);

    preProcess(n);
    long long int total = 0;
    FOR(i, m) {
        int l = min(x, y);
        int r = max(x, y);
        int level = logs[r - l + 1];
        total += max(rmq[level][l], rmq[level][r - (1 << level) + 1]);
        x += 7;
        if (x >= n - 1) x %= n - 1;
        y += 11;
        if (y >= n) y %= n;
    }
    printf("%lld\n", total);
}
