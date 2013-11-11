// Sum of combination numbers is 2^N, but in this case we have to subtract 1
// http://www.codechef.com/NOV13/problems/JOHNY
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 1000000007


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
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        long long int res = 1;
        long long int power = 2;
        while (n > 0) {
            if ((n & 1) == 1) res = res * power % MOD;
            n >>= 1;
            power = power * power % MOD;
        }
        res--;
        if (res < 0) res += MOD;
        printf("%lld\n", res);

    }
}
