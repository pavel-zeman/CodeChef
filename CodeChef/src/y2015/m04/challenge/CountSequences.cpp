// The answer is sum of all 1 to N combinations with repetitions of (L-R+1) = K items. This is sum(i=1..N, comb(K + i - 1, i)) = ((N+1) * comb(K+N, N + 1) - K) / K = comb(N+K, K) - 1. The combination number can be calculated using Lucas' theorem.
// http://www.codechef.com/APRIL15/problems/CSEQ
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 1000003

int fact[MOD];

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


int inverse(int a) {
    int p = MOD - 2;
    long long int sqr = a % MOD;
    long long int total = 1;
    while (p > 0) {
        if (p & 1) total = total * sqr % MOD;
        p >>= 1;
        sqr = sqr * sqr % MOD;
    }
    return total;
}


int comb(int n, int k) {
    if (n < k) return 0;
    return fact[n] * (long long int)inverse(fact[k]) * inverse(fact[n - k]) % MOD;
}

// Lucas' theorem
int comb2(int n, int k) {
    return comb(n % MOD, k % MOD) * (long long int)comb(n / MOD, k / MOD) % MOD;
}


int main(void) {
    fact[0] = 1;
    FORE(i, 1, MOD) fact[i] = fact[i - 1] * (long long int)i % MOD;

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int l = getInt();
        int r = getInt();
        int k = r - l + 1;
        printf("%d\n", (comb2(n + k, k) - 1 + MOD) % MOD);
    }
}
