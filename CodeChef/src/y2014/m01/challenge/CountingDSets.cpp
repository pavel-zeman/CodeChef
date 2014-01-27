// Inclusion-exclusion principle. The result is based on function F(k) = 2^k - k - 1.
// The result = F((D + 1)^N) - sum(i=1..N, (-1)^(i-1) * comb(N, i) * F((D+1)^(N-i) * D^i)) - sum(i=0..N, (-1)^i * comb(N, i) * F(D^(N-i) * (D-1)^i))
// http://www.codechef.com/JAN14/problems/CNTDSETS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define D 3
#define D2 ((D + 1)*(D + 1) *(D + 1))
#define MOD 1000000007
#define MOD1 (MOD - 1)
#define MAX_N 1010


int comb[MAX_N][MAX_N];

int selected[D2];
int resultAll;
int resultOK;

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

long long int pow(int a, int b, int mod) {
    long long int temp = a;
    long long int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * temp % mod;
        temp = temp * temp % mod;
        b >>= 1;
    }
    return result;
}

long long int f(long long int a, long long int b) {
    a %= MOD1;
    long long int result = (pow(2, a, MOD) - b - 1) % MOD;
    if (result < 0) result += MOD;
    return result;
}

int main(void) {
    FOR(i, MAX_N) {
        comb[i][0] = comb[i][i] = 1;
        FORE(j, 1, i) comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
    }

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int d = getInt();

        long long int a = f(pow(d + 1, n, MOD1), pow(d + 1, n, MOD));
        long long b = 0;
        int sign = 1;
        FORE(i, 1, n + 1) {
            b = (b + comb[n][i] * f(pow(d + 1, n - i, MOD1) * pow(d, i, MOD1), pow(d + 1, n - i, MOD) * pow(d, i, MOD)) * sign) % MOD;
            sign *= -1;
        }

        long long int c = 0;
        sign = 1;
        FOR(i, n + 1) {
            c = (c + comb[n][i] * f(pow(d, n - i, MOD1) * pow(d - 1, i, MOD1), pow(d, n - i, MOD) * pow(d - 1, i, MOD)) * sign) % MOD;
            sign *= -1;
        }
        a = (a - b - c) % MOD;
        if (a < 0) a += MOD;
        printf("%lld\n", a);
    }
}


