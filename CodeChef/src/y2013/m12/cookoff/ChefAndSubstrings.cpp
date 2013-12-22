// Suffix tree, but unfortunately this is not fast enough
// http://www.codechef.com/COOK41/problems/GERALD3
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
#define MIN_H - 200


int n;
char data[MAX_N];

int bucket[MAX_LOG_N][MAX_N];
int step;
int prefixLength;
int indexes[MAX_N];



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
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        scanf("%s", data);
        n = strlen(data);
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

        int m;
        int b[MAX_N]; // precalculate lcps
        FORE(i, 1, n) b[i] = lcp(indexes[i - 1], indexes[i]);
        scanf("%d", &m);
        FOR(i, m) {
            int l, r;
            scanf("%d %d", &l, &r);
            l--, r--;
            unsigned int total = n * (r - l + 1);
            int min = 0;
            FOR(i, n) {
                if (indexes[i] >= l && indexes[i] <= r) {
                    total -= indexes[i];
                    total -= min;
                    min = b[i + 1];
                } else if (b[i + 1] < min) min = b[i + 1];
            }
            printf("%u\n", total);
        }
    }
}
