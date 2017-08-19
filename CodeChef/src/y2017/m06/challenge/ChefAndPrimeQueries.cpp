// Use sqrt decomposition to perform 2D range queries
// https://www.codechef.com/JUNE17/problems/PRMQ
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
#define MAX_V 1000010
#define MAX_SQRT 320
#define MAX_P 80000
int a[MAX_N];
vector<pair<int, int> > factors[MAX_N];
int n;
int prime[MAX_V];
int primes[MAX_N];
int totalPrimes;
int sumN[MAX_SQRT][MAX_P];
int nSqrt;
int totalNSqrt;

int getSumN(int topx, int topy, int botx, int boty) {
    int res = sumN[topx][topy];
    if (botx > 0) res -= sumN[botx - 1][topy];
    if (boty > 0) res -= sumN[topx][boty - 1];
    if (botx > 0 && boty > 0) res += sumN[botx - 1][boty - 1];
    return res;
}

int calcFactors(int l, int r, int p1, int p2) {
    int res = 0;
    FORE(i, l, r + 1)
        for(auto it = factors[i].begin(); it != factors[i].end(); it++)
            if (it->first >= p1 && it->first <= p2) res += it->second;
    return res;
}

int main(void) {
    int xx = 1020;
    FORE(i, 2, xx) prime[i] = 1;
    FORE(i, 2, xx) if (prime[i]) {
        for(int j = i + i; j < xx; j += i) prime[j] = 0;
        primes[totalPrimes++] = i;
    }
    n = getInt();
    FOR(i, n) {
        int t = a[i] = getInt();
        int p = 0;
        while (primes[p] * primes[p] <= t) {
            int c = 0;
            while (t % primes[p] == 0) {
                c++;
                t /= primes[p];
            }
            if (c > 0) factors[i].push_back(make_pair(primes[p], c));
            p++;
        }
        if (t > 1) {
            prime[t] = 1;
            factors[i].push_back(make_pair(t, 1));
        }
    }
    totalPrimes = 0;
    FOR(i, MAX_V) if (prime[i]) {
        primes[totalPrimes++] = i;
        prime[i] = totalPrimes;
    }
    nSqrt = sqrt(n) + 1;
    totalNSqrt = n / nSqrt + 1;
    FOR(i, n) {
        int nPos = i / nSqrt;
        for(auto it = factors[i].begin(); it != factors[i].end(); it++) {
            it->first = prime[it->first] - 1;
            sumN[nPos][it->first] += it->second;
        }
    }
    FORE(j, 1, totalPrimes) sumN[0][j] += sumN[0][j - 1];
    FORE(i, 1, totalNSqrt) {
        sumN[i][0] += sumN[i - 1][0];
        FORE(j, 1, totalPrimes) sumN[i][j] += sumN[i - 1][j] + sumN[i][j - 1] - sumN[i - 1][j - 1];
    }


    int q = getInt();
    FOR(i, q) {
        int l = getInt() - 1;
        int r = getInt() - 1;
        int x = getInt();
        int y = getInt();
        int res = 0;
        int p1 = lower_bound(primes, primes + totalPrimes, x) - primes;
        if (p1 != totalPrimes) {
            int p2 = upper_bound(primes, primes + totalPrimes, y) - primes - 1;
            int ns1 = l / nSqrt;
            int ns2 = r / nSqrt;
            if (ns2 == ns1 || ns2 == ns1 + 1) res = calcFactors(l, r, p1, p2);
            else {
                res = getSumN(ns2 - 1, p2, ns1 + 1, p1);
                res += calcFactors(l, ns1 * nSqrt + nSqrt - 1, p1, p2);
                res += calcFactors(ns2 * nSqrt, r, p1, p2);
            }
        }
        print(res);
    }
}

