// I tried to find a closed formula for F = 1, but it seems, that it fails in some corner cases.
// http://www.codechef.com/JULY15/problems/EASYEX
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

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


char ccc = 0;
int getInt() {
    int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}

int getSignedInt() {
    int r = 0;
    while (!(ccc == '-' || (ccc >= '0' && ccc <= '9'))) ccc = getc_unlocked(stdin);
    bool minus = ccc == '-';
    if (minus) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

long long int getLongLongInt() {
    long long int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}


template <class type> void print(type a) {
    if (a < 0) {
        putc_unlocked('-', stdout);
        a = -a;
    }
    if (a == 0) {
        putc_unlocked('0', stdout);
    } else {
        char result[20];
        int resSize = 0;
        while (a > 0) {
            result[resSize++] = '0' + a % 10;
            a /= 10;
        }
        while (--resSize >= 0) putc_unlocked(result[resSize], stdout);
    }
    putc_unlocked('\n', stdout);
}

void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}


#define MOD 2003

int comb[MOD + 4][MOD + 4];
int fact[MOD + 4];
int inv[MOD];

int getComb(int n, int k) {
    int result = 1;
    if (n < k) fail();
    while (n > 0 || k > 0) {
        int n1 = n % MOD;
        int k1 = k % MOD;
        //printf("Comb %d %d = %d\n", n1, k1, comb[n1][k1]);
        result = result * comb[n1][k1] % MOD;
        n /= MOD;
        k /= MOD;
    }
    return result;
}


int pow(int a, int b) {
    a %= MOD;
    int power = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * power % MOD;
        b >>= 1;
        power = power * power % MOD;
    }
    return result;
}

int main(void) {
    FOR(i, MOD) inv[i] = -1;
    inv[0] = 0;
    FORE(i, 1, MOD) if (inv[i] == -1)
        FORE(j, 1, MOD) if (j * i % MOD == 1) {
            inv[i] = j;
            inv[j] = i;
            break;
        }
    FOR(i, MOD) if (inv[i] < 0) fail();

    fact[0] = 1;
    FORE(i, 1, MOD + 4) fact[i] = i * fact[i - 1] % MOD;
    FOR(i, MOD) if (fact[i] < 0) fail();

    comb[0][0] = 1;
    FORE(i, 1, MOD + 4) {
        comb[i][0] = comb[i][i] = 1;
        FORE(j, 1, i) comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
    }
    FOR(i, MOD + 4) FOR(j, MOD + 4) if (comb[i][j] < 0) fail();

    int t = getInt();

    FOR(tt, t) {
        int n = getInt();
        int k = getInt();
        int l = getInt();
        getInt(); // just ignore F now
        if (n < l || l >= MOD) print(0); else {
            int end = n;
            if (end >= MOD) end = MOD - 1;

            int result = 0;
            FORE(i, l, end + 1) {
                //printf("%d %d ", getComb(n, i), fact[i]);
                result += ((getComb(n, i) * fact[i] % MOD) * pow(k, n - i) % MOD) * getComb(i - 1, l - 1) % MOD;
                result %= MOD;
                //printf("%d ", result);
                if (result < 0) fail();
            }
            int denom = pow(k, n);
            if (denom == 0) result = 0; else result = result * inv[denom] % MOD;
            if (result < 0) fail();
            print(result);
        }
    }
}

