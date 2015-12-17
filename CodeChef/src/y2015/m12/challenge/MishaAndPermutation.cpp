// Just brute force solution for small inputs. The solution is based on the fact, that number of invalid subsets is BAD(N, K) = BAD(N, N - K + 1) + BAD(N - 1, N - K + 1).
// https://www.codechef.com/DEC15/problems/MGCHPERM
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int


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

int getString(char *start) {
    char *data = start;
    while (!(ccc > ' ' && ccc <= '~')) ccc = getc_unlocked(stdin);
    while (ccc > ' ' && ccc <= '~') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *data = 0;
    return data - start;
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

void printString(const char *str) {
    while (*str) putc_unlocked(*str++, stdout);
    putc_unlocked('\n', stdout);
}

void fail() {
    *((char *)0) = 0;
}

#define MOD 1000000007
#define MAX_N 1000010
#define MAX_K 8

int bad[MAX_K][MAX_N];


int pow(int a, int b) {
    int sq = a;
    int res = 1;
    while (b > 0) {
        if ((b & 1) == 1) res = res * (LLI)sq % MOD;
        b >>= 1;
        sq = sq * (LLI)sq % MOD;
    }
    return res;
}

int mul(int a, int b) {
    return a * (LLI)b % MOD;
}

int ddiv(int a, int b) {
    return mul(a, pow(b, MOD - 2));
}

int comb(int a, int b) {
    int res1 = 1;
    int res2 = 1;
    FOR(i, b) res1 = res1 * (LLI)(a - i) % MOD;
    FOR(i, b) res2 = res2 * (LLI)(i + 1) % MOD;
    return ddiv(res1, res2);
}


int main(void) {
    int inv = pow(48, MOD - 2);
    FORE(i, 3, MAX_N) {
        int res = (mul(4, pow(i - 1, 3)) + mul(6, pow(i - 1, 2))) % MOD;
        res = (res + MOD - mul(4, i - 1)) % MOD;
        res = (res + MOD + ((i & 1) ? 0 : -6)) % MOD;
        bad[3][i] = mul(res, inv);
    }
    FORE(i, 4, MAX_K) {
        FORE(j, i, MAX_N) {
            bad[i][j] = (bad[i][j - i + 1] + bad[i - 1][j - i + 1]) % MOD;
        }
    }

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int k = getInt();
        int result = (comb(n, k) + MOD - bad[k][n]) % MOD;
        print(result);
    }
}
