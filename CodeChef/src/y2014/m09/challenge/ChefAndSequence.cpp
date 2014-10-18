// In the first K+2 numbers, there must be at least 2, which are not modified. So try all the possible pairs.
// http://www.codechef.com/SEPT14/problems/UASEQ
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

int a[MAX_N];

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

int main(void) {
    int n = getInt();
    int k = getInt();
    FOR(i, n) a[i] = getInt();

    int r = k + 2;
    long long int a0 = LONG_MAX;
    long long int d0 = LONG_MAX;
    FOR(i, r) FORE(j, i + 1, r) {
        if ((a[j] - a[i]) % (j - i) == 0) {
            long long int d = (a[j] - a[i]) / (j - i);
            long long int start = a[i] - i * d;
            if (start < a0 || (start == a0 && d < d0)) {
                int changes = 0;
                FOR(x, n) if (start + d * x != a[x]) {
                    if (++changes > k) break;
                }
                if (changes <= k) {
                    a0 = start;
                    d0 = d;
                }
            }
        }
    }
    FOR(i, n) printf("%lld ", a0 + d0 * i);
}
