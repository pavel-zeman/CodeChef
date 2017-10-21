// The kiwis will be given only for apples or only for bananas (or for no fruits). Calculate the penalty for both fruits and then generate the sequence with the lower penalty.
// https://www.codechef.com/OCT17/problems/CHEFGP
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

#define MAX_N 200010
char s[MAX_N];
int outPos;


int calc(int c1, int c2, int k1, int k2) {
    int g1 = (c1 + k1 - 1) / k1;
    if (c2 < g1 - 1) return MAX_N;
    int g2 = (c2 + k2 - 1) / k2;
    if (g2 <= c1 + 1) return 0;
    int last = c2 - c1 * k2;
    return (last - 1) / k2;
}

void print(int c, int k, int f) {
    FOR(i, c) s[outPos++] = 'a' + f;
}

void gen(int c1, int c2, int k1, int k2, int f) {
    int p1 = 0;
    int p2 = 0;
    outPos = 0;

    int g1 = (c1 + k1 - 1) / k1;
    int g2 = (c2 + k2 - 1) / k2;
    if (g2 < g1 - 1) g2 = g1 - 1;
    else if (g2 > g1 + 1) g1 = min(g2 - 1, c1);


    int v1 = g1 == 0 ? 0 : c1 / g1;
    int v1c2 = c1 - v1 * g1;

    int last = 0;
    if (g2 > g1) {
        last = c2 - g1 * k2;
        g2 = g1;
    } else if (g2 < g1 - 1) g2 = g1 - 1;
    int v2 = g2 == 0 ? 0 : (c2 - last) / g2;
    int v2c2 = (c2 - last) - v2 * g2;

    FOR(i, g1) {
        if ((i == 0 && g1 == g2) || i > 0) {
            print(p2 < v2c2 ? v2 + 1 : v2, k2, f ^ 1);
            p2++;
        }
        print(p1 < v1c2 ? v1 + 1 : v1, k1, f);
        p1++;
    }

    int tt = 0;
    FOR(i, last) {
        if (tt == k2) {
            s[outPos++] = '*';
            tt = 0;
        }
        tt++;
        s[outPos++] = 'a' + (f ^ 1);
    }
    s[outPos] = 0;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getString(s);
        int x = getInt();
        int y = getInt();
        int num[2];
        num[0] = num[1] = 0;
        FOR(i, n) num[s[i] - 'a']++;
        int penalty1 = calc(num[0], num[1], x, y);
        int penalty2 = calc(num[1], num[0], y, x);
        if (penalty1 <= penalty2) gen(num[0], num[1], x, y, 0); else gen(num[1], num[0], y, x, 1);
        printString(s);
    }
}

