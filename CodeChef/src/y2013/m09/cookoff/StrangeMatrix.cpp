// i * (n - 1) = j * (m - 1)
// http://www.codechef.com/COOK38/problems/RRCODE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}


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

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        int res = 0;
        if (n == m) res = n;
        else if (n == 1 || m == 1) res = m * n;
        else res = gcd(n - 1, m - 1) + 1;
        printf("%d\n", res);
    }
}
