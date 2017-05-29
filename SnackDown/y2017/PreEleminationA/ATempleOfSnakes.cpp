// Calculate maximums from left and right for each positions and then choose position with minimum cost
// https://www.codechef.com/SNCKPA17/problems/SNTEMPLE
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

#define MAX_N 100010
int h[MAX_N];
LLI s[MAX_N];
int lf[MAX_N], rt[MAX_N];

LLI getSum(int a, int b) {
    if (a > b) return 0;
    return s[b] - (a > 0 ? s[a - 1] : 0);
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        FOR(i, n) h[i] = getInt();
        s[0] = h[0];
        FORE(i, 1, n) s[i] = s[i - 1] + h[i];

        int currHeight = 0;
        FOR(i, n)
            currHeight = lf[i] = h[i] >= currHeight + 1 ? currHeight + 1 : h[i];
        currHeight = 0;
        for(int i = n - 1; i >= 0; i--)
            currHeight = rt[i] = h[i] >= currHeight + 1 ? currHeight + 1 : h[i];

        LLI res = getSum(0, n - 1);
        FOR(i, n) {
            int hh = min(lf[i], rt[i]);
            LLI res1 = h[i] - hh;
            res1 += getSum(i - hh + 1, i - 1) - (1 + hh - 1) * (LLI)(hh - 1) / 2;
            res1 += getSum(i + 1, i + hh - 1) - (1 + hh - 1) * (LLI)(hh - 1) / 2;
            res1 += getSum(0, i - hh) + getSum(i + hh, n - 1);
            if (res1 < res) res = res1;
        }
        print(res);
    }
}

