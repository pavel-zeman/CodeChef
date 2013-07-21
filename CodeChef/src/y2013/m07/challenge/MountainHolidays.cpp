// Suffix array and longest common prefix (LCP)
// http://www.codechef.com/JULY13/problems/MOU1H
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100100
#define MAX_LOG_N 18
#define MOD 1000000009
#define MIN_H -200


int n;
int data[MAX_N];

int bucket[MAX_LOG_N][MAX_N];
int step;
int prefixLength;
int indexes[MAX_N];



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

int previousBucket(int pos) {
    return pos < n ? bucket[step - 1][pos] : MIN_H;
}

int cmp(const void *p1, const void *p2) {
    int i1 = *(int *)p1;
    int i2 = *(int *)p2;
    if (bucket[step - 1][i1] != bucket[step - 1][i2])
        return bucket[step - 1][i1] - bucket[step - 1][i2];
    int v1 = previousBucket(i1 + prefixLength);
    int v2 = previousBucket(i2 + prefixLength);
    return v1 == v2 ? i1 - i2 : v1 - v2;
}

int lcp(int a, int b) {
    int total = 0;
    for(int i=step-1;i>=0 && a < n && b < n;i--) {
        if (bucket[i][a] == bucket[i][b]) {
            a += 1 << i;
            b += 1 << i;
            total += 1 << i;
        }
    }
    return total;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        int h1, h2;
        FOR(i, n) {
            h2 = getInt();
            if (i != 0) data[i - 1] = h2 - h1;
            h1 = h2;
        }
        n--;
        FOR(i, n) bucket[0][i] = data[i];
        FOR(i, n) indexes[i] = i;

        bool dontStop = true;
        for(step = 1, prefixLength = 1;prefixLength <= n && dontStop;step++, prefixLength <<= 1) {
            qsort(indexes, n, sizeof(indexes[0]), cmp);
            dontStop = false;
            FOR(i, n) {
                if (i > 0 && previousBucket(indexes[i]) == previousBucket(indexes[i - 1]) && previousBucket(indexes[i] + prefixLength) == previousBucket(indexes[i - 1] + prefixLength)) {
                    dontStop = true;
                    bucket[step][indexes[i]] = bucket[step][indexes[i - 1]];
                } else {
                    bucket[step][indexes[i]] = i;
                }
            }
        }

        int total = 0;
        FOR(i, n) {
            total += n - indexes[i];
            if (i > 0) total -= lcp(indexes[i - 1], indexes[i]);
            total %= MOD;
        }
        printf("%d\n", total);
    }
}
