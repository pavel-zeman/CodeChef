// The number of bad permutations is very low, so count just the bad permutations and subtract them from the count of all permutations (this works for N <= 20)
// https://www.codechef.com/NOV16/problems/SEAPERM3
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int
#define MOD 2000000011


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

#define MAX_N 100
#define NONE -1
int ff[MAX_N];
bool used[MAX_N];
int perm[MAX_N];
int bad;
int mm[MAX_N];

int n;

void calc(int level) {
    if (level == n) {
        bad++;
    } else {
        int f = ff[level];
        int s = mm[level] >= 0 ? mm[level] + 1 : n;
        if (f >= 0) {
            if (f < s) {
                FORE(j, level + 1, f)
                    if (mm[j] == NONE) mm[j] = level;
                calc(level + 1);
                FORE(j, level + 1, f) if (mm[j] == level) mm[j] = NONE;
            }
        } else {
            FOR(i, s)
                if (!used[i]) {
                    FORE(j, level + 1, i)
                        if (mm[j] == NONE) mm[j] = level;
                    used[i] = true;
                    perm[level] = i;
                    calc(level + 1);
                    used[i] = false;
                    FORE(j, level + 1, i) if (mm[j] == level) mm[j] = NONE;
                }
        }
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        int m = getInt();
        if (n > 20) return 0;
        FOR(i, n) ff[i] = -1;
        FOR(i, n) used[i] = false;
        FOR(i, n) mm[i] = -1;
        bool valid = true;
        int totalFixed = 0;
        FOR(i, m) {
            int x = getInt() - 1;
            int v = getInt() - 1;
            if (ff[x] < 0) totalFixed++;
            if (ff[x] >= 0 && ff[x] != v) valid = false;
            if (used[v] && ff[x] != v) valid = false;
            ff[x] = v;
            used[v] = true;
            perm[x] = v;
        }
        int result = 0;
        if (valid) {
            bad = 0;
            calc(0);
            n -= totalFixed;
            LLI fact = 1;
            FOR(i, n) fact = fact * (LLI)(i + 1) % MOD;
            result = (fact - bad + MOD) % MOD;
        }
        print(result);
    }
}

