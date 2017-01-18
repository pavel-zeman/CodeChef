// Solution for the small input based on dynamic programming. Result = total number of tuples - total number of tuples with GCD != 1, i.e. GCD = 0, 2, 3, 4, 5, .... These GCDs can be calculated recursively.
// https://www.codechef.com/JAN17/problems/TUPLES
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int
#define MOD 1000000007


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

int power(int a, int b) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % MOD;
        sq = sq * (LLI)sq % MOD;
        b >>= 1;
    }
    return result;
}

int inv(int a) {
    return power(a, MOD - 2);
}

template <class type> type gcd(type a, type b) {
    return b == 0 ? a : gcd(b, a % b);
}

void fail() {
    *((char *)0) = 0;
}

double cpu() {
    return clock() / (double)CLOCKS_PER_SEC;
}

#define MOD2 359999
#define MAX_N 1000010
int cc[MOD2];
int x[MAX_N];
int cache[MOD2];
int mx;
int cc03;

void solve(int mult) {
    int total = 0;
    for(int i = 0; i <= mx; i += mult) total += cc[i];
    total = total % MOD;
    int res = total * (LLI)total % MOD * total % MOD;
    for(int i = 2 * mult; i <= mx; i += mult) {
        res -= cache[i];
        if (res < 0) res += MOD;
    }
    res -= cc03;
    if (res < 0) res += MOD;
    cache[mult] = res;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        if (n > 1000) return 1;
        FOR(i, n) x[i] = getInt();
        FOR(i, MOD2) cc[i] = 0;
        FOR(i, n) FORE(j, i + 1, n) cc[x[i] * (LLI)x[j] % MOD2] += 2;
        FOR(i, n) cc[x[i] * (LLI)x[i] % MOD2]++;
        mx = MOD2 - 1;
        while (cc[mx] == 0) mx--;
        cc03 = cc[0] * (LLI)cc[0] % MOD * cc[0] % MOD;
        //FOR(i, mx + 1) if (cc[0][i] > 0) printf("%d = %d\n", i, cc[0][i]);
        for(int i=mx; i>=1; i--) solve(i);
        print(cache[1]);

        /*FOR(i, n) FOR(j, n) brute[i * n + j] = x[i] * (LLI)x[j] % MOD2;
        int total = 0;
        FOR(i, n * n) FOR(j, n * n) FOR(k, n * n) if (gcd(brute[i], gcd(brute[j], brute[k])) == 1) total++;
        print(total);*/
    }
}

