// For each i, the quality will be increased by either (x - y) * i or (y - x) * i. So use dynamic programming considering both cases.
// https://www.codechef.com/OCT17/problems/MARRAYS
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


#define MAX_N 1000010
LLI res[2][2];
int mul[2] = {1, -1};
int dish[MAX_N];


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        FOR(i, n) {
            int m = getInt();
            FOR(j, m) dish[j] = getInt();

            if (i == 0) {
                res[1][0] = *max_element(dish, dish + m);
                res[1][1] = -*min_element(dish, dish + m);
            } else if (i < n - 1) {
                FOR(j, 2) {
                    LLI best = -1000000000000000LL;
                    int mulj = mul[j];
                    FOR(k, 2) {
                        int mulk = mul[k];
                        FOR(l, m) {
                            LLI bb = mulj * dish[(l + m  - 1) % m] * (LLI)(i + 1) + mulk * dish[l] * (LLI)i + res[0][k ^ 1];
                            if (bb > best) best = bb;
                        }
                    }
                    res[1][j] = best;
                }
            } else {
                FOR(j, 2) {
                    LLI best = -1000000000000000LL;
                    int mulj = mul[j];
                    FOR(l, m) {
                        LLI bb = dish[l] * mulj * (LLI)(n - 1) + res[0][j ^ 1];
                        if (bb > best) best = bb;
                    }
                    res[1][j] = best;
                }
            }
            res[0][0] = res[1][0];
            res[0][1] = res[1][1];
        }
        printf("%lld\n", n > 1 ? max(res[0][0], res[0][1]) : 0);
    }
}

