// If there are no zeros, then we can change k&1, k&1 + 2, ... , k numbers. If there is any zero, we can change 0 to k numbers. Then it's just combinatorial number.
// https://www.codechef.com/JUNE16/problems/CHEFARK
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

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 100010
int fact[MAX_N];
int invFact[MAX_N];

int comb(int n, int k) {
    return fact[n] * (LLI)invFact[k] % MOD * invFact[n - k] % MOD;
}

int main(void) {
    fact[0] = 1;
    FORE(i, 1, MAX_N) fact[i] = fact[i - 1] * (LLI)i % MOD;
    FOR(i, MAX_N) invFact[i] = inv(fact[i]);
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int k = getInt();
        int nums = 0;
        FOR(i, n) {
            int a = getInt();
            if (a != 0) nums++;
        }
        int result = 0;
        if (nums < n)
            for(int j = 0; j <= k && j <= nums; j++) result = (result + comb(nums, j)) % MOD;
        else
            for(int j = k & 1; j <= k && j <= nums; j += 2) result = (result + comb(nums, j)) % MOD;
        print(result);
    }
}

