// Number of iterations equals to number of 1s (plus special cases)
// https://www.codechef.com/OCT16/problems/FENWITER
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

#define MAX_L 1024
char l1[MAX_L];
char l2[MAX_L];
char l3[MAX_L];

int totalOnes(char *data, int l) {
    int res = 0;
    FOR(i, l) if (data[i] == '1') res++;
    return res;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int ll1 = getString(l1);
        int ll2 = getString(l2);
        int ll3 = getString(l3);
        int n = getInt();
        int res = totalOnes(l1, ll1) + totalOnes(l2, ll2) * n + totalOnes(l3, ll3) + 1;

        int i = ll3 - 1;
        while (i >= 0 && l3[i] == '1') i--;
        res -= ll3 - i - 1;

        if (i < 0) {
            i = ll2 - 1;
            while (i >= 0 && l2[i] == '1') i--;
            if (i >= 0) res -= ll2 - i - 1;
            else {
                res -= ll2 * n;
                i = ll1 - 1;
                while (i >= 0 && l1[i] == '1') i--;
                res -= ll1 - i - 1;
            }
        }
        print(res);
    }
}

