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
#define MAXITEMS 1000



long long power(long long a, long long count) {
    long long result = 1;
    long long power = a % MOD;
    while (count > 0) {
        if (count & 1) result = (result * power) % MOD;
        count >>= 1;
        power = (power * power) % MOD;
    }
    return result;
}

char c = 0;
int getInt() {
    int r = 0;
    while (c < '0' || c > '9') c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

long long getLong() {
    long long r = 0;
    while (c < '0' || c > '9') c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        long long v = getLong();
        int n = getInt();
        long long p[MAXITEMS], q[MAXITEMS];
        long long l[MAXITEMS];

        p[0] = getLong();
        p[1] = getLong();
        long long a0 = getLong(), b0 = getLong(), c0 = getLong(), m0 = getLong();
        q[0] = getLong();
        q[1] = getLong();
        long long a1 = getLong(), b1 = getLong(), c1 = getLong(), m1 = getLong();

        FORE(i, 2, n) {
            p[i] = (((((a0 * a0) % m0) * p[i - 1]) % m0) + ((b0 * p[i - 2]) % m0) + c0) % m0;
            q[i] = (((((a1 * a1) % m1) * q[i - 1]) % m1) + ((b1 * q[i - 2]) % m1) + c1) % m1;
        }
        long long exp = 1;
        bool isOne = false;
        FOR(i, n) {
            l[i] = (((p[i] * m1) % (MOD - 1)) + q[i]) ;
            exp = (exp * (l[i] % (MOD - 1))) % (MOD - 1);
            isOne = l[i] == 0;
        }

        if (isOne) v = 1;
        else if (v % MOD == 0) v = 0;
        else v = power(v % MOD, exp);
        printf("%d\n", (int)v);
    }
}
