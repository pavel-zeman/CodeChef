// Precalculate powers of 4 and then multiple them for the bits, that are set to 1
// http://www.codechef.com/NOV13/problems/SPOTWO
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

#define POWERS 100
int powers[POWERS];

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
    long long int power = 4;
    FOR(i, POWERS) {
        powers[i] = power;
        long long int power2 = power * power % MOD;
        long long int power4 = power2 * power2 % MOD;
        long long int power8 = power4 * power4 % MOD;
        power = power2 * power8 % MOD;
    }

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        long long int result = 1;
        for(int i=0;i<POWERS && n > 0; i++) {
            if ((n & 1) == 1) result = result * powers[i] % MOD;
            n >>= 1;
        }
        printf("%lld\n", result);
    }
}
