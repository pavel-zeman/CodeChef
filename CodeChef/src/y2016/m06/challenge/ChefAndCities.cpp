// Pre-calculate all results for all possible R. Then updated the pre-calculated values, because for each modification, there is just "a couple" of them. Used logarithms to calculate the first digit.
// https://www.codechef.com/JUNE16/problems/FRJUMP
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

#define OP_CHANGE 1
#define OP_FIND 2

#define MAX_N 100010
int n;
int f[MAX_N];
int total[MAX_N];
double logTotal[MAX_N];


bool prime[MAX_N];
vector<pair<int, int> > divisors[MAX_N];


void adjust(int sofar, int pos, int adjustValue, double logAdjustValue, int level) {
    if (level == (int)divisors[pos].size()) {
        total[sofar] = total[sofar] * (LLI)adjustValue % MOD;
        logTotal[sofar] += logAdjustValue;
    } else {
        FOR(i, divisors[pos][level].second + 1) {
            adjust(sofar, pos, adjustValue, logAdjustValue, level + 1);
            sofar *= divisors[pos][level].first;
        }
    }
}

int main(void) {
    n = getInt();
    FOR(i, n) f[i] = getInt();
    FORE(i, 1, n + 1) {
        int tt = 1;
        double log = 0;
        for(int j = i; j < n; j += i) {
            tt = tt * (LLI)f[j] % MOD;
            log += log10(f[j]);
        }
        total[i] = tt;
        logTotal[i] = log;
    }
    FOR(i, MAX_N) prime[i] = true;
    FORE(i, 2, MAX_N) {
        if (prime[i]) {
            for(int j=i;j<MAX_N;j+=i) {
                divisors[j].push_back(make_pair(i, 1));
                prime[j] = false;
            }
        }
    }
    FORE(i, 2, MAX_N) {
        FOR(j, divisors[i].size()) {
            int d = divisors[i][j].first;
            int tt = i / d;
            int c = 1;
            while (tt % d == 0) {
                tt /= d;
                c++;
            }
            divisors[i][j].second = c;
        }
    }

    int q = getInt();
    if (n <= 10) {
        // handle small data separately (there seems to be some kind of overflow with logs)
        FOR(i, q) {
            int op = getInt();
            int p1 = getInt();
            if (op == OP_CHANGE) f[p1 - 1] = getInt();
            else {
                LLI total = 1;
                for(int j = 0; j < n; j += p1) total *= f[j];
                LLI digit = total;
                while (digit >= 10) digit /= 10;
                printf("%lld %lld\n", digit, total % MOD);
            }
        }

    } else {
        FOR(i, q) {
            int op = getInt();
            int p1 = getInt();
            if (op == OP_CHANGE) {
                int newf = getInt();
                p1--;
                if (p1 == 0) f[p1] = newf;
                else {
                    double logAdjust = log10(newf) - log10(f[p1]);
                    int mult = inv(f[p1]) * (LLI)newf % MOD;
                    f[p1] = newf;
                    adjust(1, p1, mult, logAdjust, 0);
                }
            } else {
                int result = total[p1];
                double logResult = logTotal[p1];
                result = result * (LLI)f[0] % MOD;
                logResult += log10(f[0]);
                logResult -= trunc(logResult);
                int x = pow(10, logResult);
                printf("%d %d\n", x, result);
            }
        }
    }

}


