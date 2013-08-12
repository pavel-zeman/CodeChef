// Modular arithmetics
// http://www.codechef.com/AUG13/problems/CNTSOLS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 50
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

int power(int a, int b, int mod) {
    int result = 1 % mod;
    while (b > 0) {
        if ((b & 1) == 1) result = result * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return result;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int upper = getInt();
        int d = getInt();
        int m = getInt();
        int n = getInt();

        long long int counts[MAX_N];
        FOR(i, n) counts[i] = 0;
        FOR(i, n) {
            int p = power(i, d, n);
            int count = i > upper ? 0 : (upper - i) / n + 1;
            counts[p] += count;
        }

        int result = 0;
        FOR(i, n) {
            FOR(j, n) {
                int k = m - (i + j) % n;
                if (k < 0) k += n;
                result += counts[i] * counts[j] % MOD * counts[k] % MOD;
                result %= MOD;
            }
        }
        printf("%d\n", result);
    }
}
