// Just handle all possible cases
// https://www.codechef.com/SNCKQL17/problems/SAMESNAK
//#include <bits/stdc++.h>
#include <stdio.h>
#include <algorithm>
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


int x1[2], yy1[2], x2[2], y2[2];

void sw(int x) {
    swap(x1[x], x2[x]);
    swap(yy1[x], y2[x]);
}

bool isOne(int x) {
    return max(abs(x1[x] - x2[x]), abs(yy1[x] - y2[x])) == 0;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int horizontal[2];
        FOR(i, 2) {
            x1[i] = getSignedInt();
            yy1[i] = getSignedInt();
            x2[i] = getSignedInt();
            y2[i] = getSignedInt();
            horizontal[i] = yy1[i] == y2[i];
        }
        bool ok;
        if (isOne(0)) horizontal[0] = horizontal[1];
        if (isOne(1)) horizontal[1] = horizontal[0];

        if (horizontal[0] && horizontal[1]) {
            FOR(i, 2) if (x1[i] > x2[i]) sw(i);
            ok = yy1[0] == yy1[1] && !(x2[1] < x1[0] || x2[0] < x1[1]);
        } else if (!horizontal[0] && !horizontal[1]) {
            FOR(i, 2) if (yy1[i] > y2[i]) sw(i);
            ok = x1[0] == x1[1] && !(y2[1] < yy1[0] || y2[0] < yy1[1]);
        } else {
            if (!horizontal[0]) {
                swap(x1[0], x1[1]);
                swap(yy1[0], yy1[1]);
                swap(x2[0], x2[1]);
                swap(y2[0], y2[1]);
            }
            ok = (yy1[0] == yy1[1] || yy1[0] == y2[1]) && (x1[0] == x1[1] || x2[0] == x1[1]);
        }
        printString(ok ? "yes" : "no");
    }
}

