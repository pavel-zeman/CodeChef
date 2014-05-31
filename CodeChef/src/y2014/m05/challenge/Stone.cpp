// After the second step the array alternates between two states
// http://www.codechef.com/MAY14/problems/RRSTONE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100002

long long int a[MAX_N];

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
    int n = getInt(), k = getInt();
    FOR(j, n) a[j] = getInt();
    if (k > 3) k = ((k - 2) & 1) + 2;
    FOR(i, k) {
        long long int max = a[0];
        FOR(j, n) if (a[j] > max) max = a[j];
        FOR(j, n) a[j] = max - a[j];
    }
    FOR(j, n) printf("%lld ", a[j]);
}
