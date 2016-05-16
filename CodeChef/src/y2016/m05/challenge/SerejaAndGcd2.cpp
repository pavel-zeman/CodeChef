// To get gcd = 1, the numbers must be either 1 or must have different prime factors. There are 25 primes < 100, so try up to 25 non-one array elements.
// https://www.codechef.com/MAY16/problems/SEAGCD2
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


#define MAX_M 101
#define MAX_N 100010
bool prime[MAX_M];
int primes[MAX_M];
int primeCount;
int fact[MAX_N];
int comb[MAX_M][MAX_M];

bool used[MAX_M];


int getWays(int m, int product, int firstPrime, int lastPrime, int primesRemain, int remain);

int finish(int m, int firstPrime, int primesRemain, int remain) {
    int result = 0;
    if (remain == 0) result = 1;
    else if (primesRemain < remain) result = 0;
    else if (primes[firstPrime] * primes[firstPrime] > m) result = comb[primesRemain][remain];
    else {
        int i = firstPrime;
        int skipped = 0;
        while (primes[i] <= m) {
            if (!used[i]) {
                skipped++;
                if (primes[i] * primes[i] > m) result += comb[primesRemain - skipped][remain - 1];
                else {
                    used[i] = true;
                    result += getWays(m, primes[i], i, i, primesRemain - skipped, remain - 1);
                    used[i] = false;
                }
            }
            i++;
        }
    }
    return result;
}

int getWays(int m, int product, int firstPrime, int lastPrime, int primesRemain, int remain) {
    int result = 0;

    if (product * primes[lastPrime] <= m)
        result += getWays(m, product * primes[lastPrime], firstPrime, lastPrime, primesRemain, remain);
    int i = lastPrime + 1;
    while (product * primes[i] <= m) {
        if (!used[i]) {
            used[i] = true;
            result += getWays(m, product * primes[i], firstPrime, i, primesRemain - 1, remain);
            used[i] = false;
        }
        i++;
    }

    result += finish(m, firstPrime + 1, primesRemain, remain);
    return result;
}

int main(void) {
    FOR(i, MAX_M) prime[i] = true;
    FORE(i, 2, MAX_M) {
        if (prime[i]) {
            primes[primeCount++] = i;
            for(int j=i + i; j < MAX_M;j +=i) prime[j] = false;
        }
    }

    fact[0] = 1;
    FORE(i, 1, MAX_N) fact[i] = (i * (LLI)fact[i - 1]) % MOD;

    primes[primeCount] = MAX_M;

    comb[0][0] = 1;
    FORE(i, 1, 30) {
        comb[i][0] = comb[i][i] = 1;
        FORE(j, 1, i) comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        int usablePrimes = 0;
        while (primes[usablePrimes] <= m) usablePrimes++;
        int result = 0;
        FOR(j, n + 1) {
            result += (fact[n] * (LLI)finish(m, 0, usablePrimes, j)) % MOD * inv(fact[n - j]) % MOD;
            result %= MOD;
            if (j >= usablePrimes) break;
        }
        print(result);
    }
}

