// Use DP to calculate all shortest paths from node 1. Then the shortest paths from node 2 (and all others) are almost the same, so calculate just the difference.
// https://www.codechef.com/MARCH17/problems/SUMDIS
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

#define MAX_S 1024
#define MAX_N 100010
#define TTDIF 1000000000
LLI res[MAX_N];
int a[MAX_N], b[MAX_N], c[MAX_N];
int diffs[MAX_N];
int prevDiffs[MAX_N];
LLI totalSuffix[MAX_N];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        FOR(i, n - 1) a[i] = getInt();
        FOR(i, n - 2) b[i] = getInt();
        FOR(i, n - 3) c[i] = getInt();
        LLI total = 0;
        FOR(i, n) prevDiffs[i] = 0;
        FOR(i, n) {
            res[i] = 0;
            bool early = false;
            FORE(j, i + 1, n) {
                res[j] = res[j - 1] + a[j - 1];
                if (j >= i + 2) res[j] = min(res[j], res[j - 2] + b[j - 2]);
                if (j >= i + 3) res[j] = min(res[j], res[j - 3] + c[j - 3]);
                total += res[j];
                diffs[j] = res[j] - res[j - 1];
                if (j >= i + 4 && diffs[j] == prevDiffs[j] && diffs[j - 1] == prevDiffs[j - 1] && diffs[j - 2] == prevDiffs[j - 2]) {
                    total += res[j] * (n - j - 1);
                    total += totalSuffix[j + 1];
                    for(int k = j; k >= i + 1; k--) {
                        prevDiffs[k] = diffs[k];
                        totalSuffix[k] = totalSuffix[k + 1] + prevDiffs[k] * (n - k);
                    }
                    early = true;
                    break;
                }
            }
            if (!early) {
                FORE(j, i + 1, n) prevDiffs[j] = diffs[j];
                totalSuffix[n] = 0;
                for(int j = n - 1; j >= i + 1; j--) totalSuffix[j] = totalSuffix[j + 1] + prevDiffs[j] * (n - j);
            }
        }
        printf("%lld\n", total);
    }
}

