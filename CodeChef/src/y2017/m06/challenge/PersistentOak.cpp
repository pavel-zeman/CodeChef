// Description
// https://www.codechef.com/JUNE17/problems/OAK
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

#define MAX_N 128

int n, m;
int prevv[MAX_N];
int maxw[MAX_N];
vector<int> children[MAX_N];
LLI acorns[MAX_N][MAX_N];

void add(int s, int u, int x) {
    int t = u;
    while (t) {
        acorns[s][t] += x;
        t = prevv[t];
    }
    acorns[s][t] += x;
    while (u) {
        if (acorns[s][u] > maxw[u]) {
            print(u);
            int rem = acorns[s][u];
            while (u) {
                acorns[s][u] -= rem;
                u = prevv[u];
            }
            acorns[s][u] -= rem;
            return;
        }
        u = prevv[u];
    }
    print(0);
}

void rem(int s, int u) {
    print(acorns[s][u]);

    int rm = acorns[s][u];
    while (u) {
        acorns[s][u] -= rm;
        u = prevv[u];
    }
    acorns[s][u] -= rm;
}

int main(void) {
    maxw[0] = 2000000000;
    int t = getInt();
    FOR(tt, t) {
        n = getInt() + 1;
        m = getInt();
        FOR(i, n) children[i].clear();
        FOR(i, n - 1) {
            prevv[i + 1] = getInt();
            children[prevv[i + 1]].push_back(i);
            maxw[i + 1] = getInt();
        }
        FOR(i, n) acorns[0][i] = 0;
        FOR(i, m) {
            int state = getInt();
            FOR(j, n) acorns[i + 1][j] = acorns[state][j];
            int q = getInt();
            int u = getInt();
            int x;
            switch (q) {
            case 1:
                x = getInt();
                add(i + 1, u, x);
                break;
            case 2:
                rem(i + 1, u);
                break;
            }
        }
    }
}

