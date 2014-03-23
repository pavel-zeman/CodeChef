// For each strength, we only need to know, whether the number of players with this strength is odd or even. If it is odd, we consider this strength, when calculating the requested difference.
// http://www.codechef.com/MARCH14/problems/TMSLT
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 1000000

char flag[MOD];

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
        int a = getInt(), b = getInt(), c = getInt(), d = getInt();
        long long int s = d;

        FOR(i, MOD) flag[i] = 0;
        flag[s] = 1;

        FORE(i, 1, n) {
            s = ((a * s + b) * s + c) % MOD;
            flag[s] ^= 1;
        }

        long long int total = 0;
        int sign = 1;
        FOR(i, MOD) {
            if (flag[i] != 0) {
                total += sign * i;
                sign *= -1;
            }
        }
        printf("%lld\n", total < 0 ? -total : total);
    }
}
