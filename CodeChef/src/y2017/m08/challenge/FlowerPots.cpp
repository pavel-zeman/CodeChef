// There are 2 phases - 1. go to one direction and 2. go to both directions in parallel
// https://www.codechef.com/AUG17/problems/FLOWERPO
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

#define MAX_N 3010
#define MAX_B 3010
#define MAX_NB 1000000
#define INF (1LL << 59)
int n, b, c;
int a[MAX_N];
LLI res1[MAX_NB]; // go to the right
LLI res12[MAX_NB]; // go to the right
LLI res2[MAX_NB]; // go to the left
LLI res22[MAX_NB]; // go to the left
LLI bidiRes[MAX_NB];

LLI sqr(int a) {
    return a * (LLI)a;
}

void setValue(LLI *d, int bb, int nn, LLI v) {
    //if (v > INF) fail();
    int index = bb * n + nn;
    d[index] = v;
}

LLI getValue(LLI *d, int bb, int nn) {
    int index = bb * n + nn;
    return d[index];
}

void step1(int i) {
    setValue(res1, 0, i, INF);
    FORE(j, 1, b + 1) {
        LLI resLocal = INF;
        FORE(k, i + 1, n) {
            LLI ttt = sqr(a[k] - a[i]) + getValue(res1, j - 1, k);
            if (ttt < resLocal) resLocal = ttt;
        }
        setValue(res1, j, i, resLocal);
    }
}

void step12(int i) {
    setValue(res12, 0, i, INF);
    FORE(j, 1, b + 1) {
        LLI resLocal = INF;
        FORE(k, i + 1, c + 1) {
            LLI ttt = sqr(a[k] - a[i]) + getValue(res12, j - 1, k);
            if (ttt < resLocal) resLocal = ttt;
        }
        setValue(res12, j, i, resLocal);
    }
}


void step2(int i) {
    setValue(res2, 0, i, INF);
    FORE(j, 1, b + 1) {
        LLI resLocal = INF;
        FOR(k, i) {
            LLI ttt = sqr(a[i] - a[k]) + getValue(res2, j - 1, k);
            if (ttt < resLocal) resLocal = ttt;
        }
        setValue(res2, j, i, resLocal);
    }
}


void step22(int i) {
    setValue(res22, 0, i, INF);
    FORE(j, 1, b + 1) {
        LLI resLocal = INF;
        FORE(k, c, i) {
            LLI ttt = sqr(a[i] - a[k]) + getValue(res22, j - 1, k);
            if (ttt < resLocal) resLocal = ttt;
        }
        setValue(res22, j, i, resLocal);
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        b = getInt();
        c = getInt() - 1;
        FOR(i, n) a[i] = getInt();

        //if (a[n - 1] - a[0] >= 90000000) fail();
        //if (n * b >= 29900) fail();

        FOR(i, b + 1) setValue(res1, i, n - 1, 0);
        for(int i = n - 2; i >= c; i--) step1(i);
        if (c > 0) {
            FOR(i, b + 1) setValue(res12, i, c, 0);
            for(int i = c - 1; i >= 0; i--) step12(i);
        }

        FOR(i, b + 1) setValue(res2, i, 0, 0);
        for(int i = 1; i <= c; i++) step2(i);
        if (c < n - 1) {
            FOR(i, b + 1) setValue(res22, i, c, 0);
            for(int i = c + 1; i < n; i++) step22(i);
        }

        if (c == 0) print(getValue(res1, b, 0));
        else if (c == n - 1) print(getValue(res2, b, n - 1));
        else {
            FOR(i, n) {
                FOR(j, b + 1) setValue(bidiRes, j, i, INF);
                int l = min(i, c), r = max(i, c);
                while (l > 0 || r < n - 1) {
                    if (l > 0 && r < n - 1) {
                        if (a[i] - a[l - 1] <= a[r + 1] - a[i]) l--; else r++;
                    } else if (l > 0) l--; else r++;
                    int dist = max(a[i] - a[l], a[r] - a[i]);
                    LLI sd = sqr(dist);
                    //int bb = min(b, l + n - r);
                    FORE(j, 1, b + 1) {
                        LLI resLocal1 = getValue(res1, j - 1, r) + getValue(res2, j - 1, l);
                        LLI curr = getValue(bidiRes, j, i);
                        if (resLocal1 + sd < curr) setValue(bidiRes, j, i, resLocal1 + sd);
                    }
                }
            }
            LLI resTotal = getValue(bidiRes, b, c);
            FOR(i, c) {
                FORE(j, 1, b) {
                    LLI resLocal = getValue(bidiRes, j, i) + getValue(res12, b - j, i);
                    if (resLocal < resTotal) {
                        resTotal = resLocal;
                        //fail();
                    }
                }
            }
            FORE(i, c + 1, n) {
                FORE(j, 1, b) {
                    LLI resLocal = getValue(bidiRes, j, i) + getValue(res22, b - j, i);
                    if (resLocal < resTotal) {
                        resTotal = resLocal;
                        //fail();
                    }
                }
            }
            //print(resTotal);
            printf("%lld\n", resTotal);
            if (resTotal < 0 || resTotal >= INF) fail();
        }
    }
}

