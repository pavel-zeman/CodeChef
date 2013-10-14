// The goal is to calculate the number of sequences such that max - min = q and each number is <= m
// http://www.codechef.com/OCT13/problems/SEATRSF
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 1000000007

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

long long int power(int a, int b) {
    long long int p = a;
    long long int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * p % MOD;
        p = p * p % MOD;
        b >>= 1;
    }
    return result;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        int q = getInt();
        getInt();

        if (m <= q) {
            printf("0\n");
        } else {
            long long int total = power(q + 1, n) - power(q, n) - (power(q, n) - power(q - 1, n));
            total %= MOD;
            if (total < 0) total += MOD;
            total = total * (m - q) % MOD;
            printf("%lld\n", total);
        }
    }
}
