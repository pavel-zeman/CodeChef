// Simplified Aho-Corasick to find all occurrences of f in s and then simple dynamic programming
// https://www.codechef.com/NOV16/problems/GIFTCHEF
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

double cpu() {
    return clock() / (double)CLOCKS_PER_SEC;
}

#define MAX_L 300010
char f[MAX_L], ss[MAX_L];
int fl;
bool start[MAX_L];
int result[MAX_L];



#define MAX_STATES MAX_L
struct state {
    int f;
} states[MAX_STATES];

void calcF(void) {
    states[0].f = 0;
    states[1].f = 0;
    FORE(state, 1, fl) {
        int ff = states[state].f;
        while (f[ff] != f[state] && ff > 0) ff = states[ff].f;
        states[state + 1].f = f[ff] == f[state] ? ff + 1 : ff;
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int sl = getString(ss);
        fl = getString(f);
        FOR(i, sl) start[i] = false;

        calcF();

        int pos = 0;
        FOR(i, sl) {
            while (f[pos] != ss[i] && pos > 0) pos = states[pos].f;
            pos = f[pos] == ss[i] ? pos + 1 : pos;
            start[i - fl + 1] = pos == fl;
        }
        result[sl] = 0;
        for(int i=sl - 1; i>=0; i--) {
            result[i] = result[i + 1];
            if (start[i]) {
                result[i] = result[i] + result[i + fl] + 1;
                if (result[i] >= MOD) result[i] -= MOD;
            }
        }
        print(result[0]);
    }
}

