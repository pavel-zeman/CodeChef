// The consecutive array must go through the left bound, right bound or interval mid-point. Pre-calculate all maximum consecutive element intervals and then try all 3 possibilities.
// https://www.codechef.com/FEB17/problems/MFREQ
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
int a[MAX_N];
int lastStart[MAX_N];
int length[MAX_N];


int getLength(int pos, int l, int r) {
    int l1 = lastStart[pos];
    int l2 = l1 + length[l1] - 1;
    if (l1 < l) l1 = l;
    if (l2 > r) l2 = r;
    return l2 - l1 + 1;
}

int main(void) {
    int n = getInt();
    int m = getInt();
    FOR(i, n) a[i] = getInt();
    int ls = 0;
    int lv = a[0];
    FOR(i, n) {
        if (lv != a[i]) {
            length[ls] = i - ls;
            lv = a[i];
            ls = i;
        }
        lastStart[i] = ls;
    }
    length[ls] = n - ls;

    FOR(i, m) {
        int l = getInt() - 1;
        int r = getInt() - 1;
        int k = getInt();
        int res = -1;
        if (getLength(l, l, r) >= k) res = a[l];
        else if (getLength(r, l, r) >= k) res = a[r];
        else if (getLength((l + r) >> 1, l, r) >= k) res = a[(l + r) >> 1];
        print(res);
    }
}

