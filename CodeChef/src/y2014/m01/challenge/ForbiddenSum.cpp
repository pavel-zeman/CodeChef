// Values of the input array are split into intervals of power-2 length, which are processed one-by-one. The total time complexity is O(M*sqrt(N)).
// http://www.codechef.com/JAN14/problems/FRBSUM
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010
#define MAX_NSQ 320
#define MAX_L 30

int a[MAX_N];
int n;
int nsq;
int sum[MAX_L][MAX_N];
int rmq[MAX_L][MAX_NSQ];


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

int getStart(int level) {
    return 1 << level;
}

void calcSums() {
    FOR(i, MAX_L) {
        int start = getStart(i);
        int end = start * 2 - 1;
        int total = 0;
        FOR(j, n) {
            if (a[j] >= start && a[j] <= end) total += a[j];
            sum[i][j] = total;
        }
        start <<= 1;
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

void calcMins() {
    nsq = sqrt(n);
    if (nsq < 1) nsq = 1;
    FOR(i, MAX_L) {
        int start = getStart(i);
        int end = start * 2 - 1;
        int l = 0;
        int pos = 0;
        while (l < n) {
            int r = min(l + nsq, n);
            int m = INT_MAX;
            FORE(j, l, r) {
                if (a[j] >= start && a[j] <= end) m = min(m, a[j]);
            }
            l = r;
            rmq[i][pos++] = m;
        }
    }
}

int findSum(int level, int a, int b) {
    int total = sum[level][b];
    if (a > 0) total -= sum[level][a - 1];
    return total;
}

int findMin(int level, int l, int h) {
    int m = INT_MAX;
    int start = getStart(level);
    int end = (start << 1) - 1;
    int e = (l / nsq + 1) * nsq;
    int i = l;
    while (i < e && i <= h) {
        if (a[i] >= start && a[i] <= end) m = min(a[i], m);
        i++;
    }
    int step = i / nsq;
    while (i + nsq <= h - 1) {
        m = min(rmq[level][step++], m);
        i += nsq;
    }
    while (i <= h) {
        if (a[i] >= start && a[i] <= end) m = min(a[i], m);
        i++;
    }
    return m;
}

int solve(int l, int h) {
    int total = 0;
    FOR(j, MAX_L) {
        int end = getStart(j + 1) - 1;
        if (total < end) {
            int m = findMin(j, l, h);
            if (m > total + 1) return total + 1;
        }
        total += findSum(j, l, h);
    }
    return total + 1;
}

int main(void) {
    n = getInt();
    FOR(i, n) a[i] = getInt();
    calcSums();
    calcMins();

    int m = getInt();
    FOR(i, m) {
        int l = getInt() - 1, r = getInt() - 1;
        printf("%d\n", solve(l, r));
    }
}
