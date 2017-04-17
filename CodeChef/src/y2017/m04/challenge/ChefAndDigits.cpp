// Inclusion-exclusion principle.
// https://www.codechef.com/APRIL17/problems/DGTCNT
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

#define N (1 << 10)
#define FF 20
int a[10];
int b[10];
vector<int> digs[N];
LLI fact[FF];
LLI comb[FF][FF];
LLI ppp[10][FF];

LLI calc(int digits) {
    int cc[10];
    LLI result = 0;
    FORE(i, 1, N) {
        bool ok = true;
        int ct = 0;
        int totalFixed = 0;
        FOR(j, digs[i].size()) {
            if (b[digs[i][j]] < 0) { ok = false; break;}
            totalFixed += (cc[ct++] = b[digs[i][j]]);
        }
        if (ok && totalFixed <= digits) {
            LLI t = fact[totalFixed];
            LLI tt = 1;
            FOR(j, ct) tt *= fact[cc[j]];
            t /= tt;
            t *= comb[digits][totalFixed];
            t *= ppp[10 - ct][digits - totalFixed];
            if ((ct & 1) == 1) result += t; else result -= t;
        }
    }
    return result;
}


LLI solve(LLI v) {
    LLI result = 0;
    if (v < 10) {
        FORE(i, 1, v + 1) if (a[i] == 1) result++;
    } else {
        FORE(i, 1, 10) if (a[i] == 1) result++;
        FOR(i, 10) b[i] = a[i];
        LLI mult = 10;
        int toCalc = 1;
        while (v / 10 >= mult) {
            FORE(i, 1, 10) {
                b[i]--;
                result += calc(toCalc);
                b[i]++;
            }
            mult *= 10;
            toCalc++;
        }

        LLI t = mult;
        int i = 1;
        for(; t + mult <= v; i++, t += mult) {
            b[i]--;
            result += calc(toCalc);
            b[i]++;

        }
        b[i]--;
        toCalc--;
        mult /= 10;

        while (toCalc > 0) {
            int i = 0;

            for(; t + mult <= v; i++, t += mult) {
                b[i]--;
                result += calc(toCalc);
                b[i]++;
            }
            b[i]--;
            toCalc--;
            mult /= 10;
        }

        for(int i = 0; t <= v; i++, t++) {
            b[i]--;
            FOR(j, 10) if (b[j] == 0) {
                result++;
                break;
            }
            b[i]++;
        }
    }
    return result;
}

bool isInvalid(int v) {
    int digits[10];
    FOR(i, 10) digits[i] = 0;
    while (v > 0) {
        digits[v % 10]++;
        v /= 10;
    }
    FOR(i, 10) if (digits[i] == a[i]) return true;
    return false;
}

int main(void) {
    fact[0] = 1;
    FORE(i, 1, FF) fact[i] = i * fact[i - 1];
    comb[0][0] = 1;
    FORE(i, 1, FF) {
        comb[i][0] = comb[i][i] = 1;
        FORE(j, 1, i) comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }
    FOR(i, N) {
        int p = i;
        FOR(j, 10) {
            if ((p & 1) == 1) digs[i].push_back(j);
            p >>= 1;
        }
    }
    FOR(i, 10) {
        ppp[i][0] = 1;
        FORE(j, 1, FF) ppp[i][j] = ppp[i][j - 1] * i;
    }

    int t = getInt();
    FOR(tt, t) {
        LLI l = getLongLongInt();
        LLI r = getLongLongInt();
        FOR(i, 10) a[i] = getInt();
        LLI res = solve(r);
        if (l > 1) res -= solve(l - 1);
        res = r - l + 1 - res;
        print(res);
    }
}

