// F(N, K) = N * comb(N - 1, K - 1). Result = LCM(N - K + 1, N - K + 2, ...., N - K + K) as described at http://math.stackexchange.com/questions/1442/is-there-a-direct-proof-of-this-lcm-identity?rq=1. The LCM is then calculated using a precomputed array of prime number products.
// https://www.codechef.com/OCT15/problems/LOTERY
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


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


void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}

#define MAX_PRIMES 9600
#define MAX_INT_LENGTH 4500
#define MAX_M 100010
#define MAX_T 1000010
#define MOD 1000000007

bool isPrime[MAX_M];
int prime[MAX_PRIMES];
int primePos[MAX_M];
int primeCount;
int c[MAX_T];
int lastPrimes;
int memo[MAX_PRIMES][MAX_INT_LENGTH];
int nextPrimePos[MAX_M], prevPrimePos[MAX_M];

int solve(int n, int k) {
    if (k - 1 + k - 1 > n) k = (n - 1) / 2 + 1;

    int result = 1;
    int i=0;
    for(;prime[i] * prime[i] <= n;i++) {
        int lastValid = 1;
        int t = prime[i];
        while (n % t < k) {
            lastValid = t;
            t *= prime[i];
        }
        if (lastValid > 1) result = (result * (long long int)lastValid) % MOD;
    }
    int start = i;

    int p1 = nextPrimePos[n - k + 1];
    int p2 = prevPrimePos[n];
    if (p1 < start) p1 = start;
    if (p2 >= p1) result = (result * (long long int)memo[p1][p2 - p1]) % MOD; else p1 = p2;
    FORE(i, 2, MAX_M) {
        int is = (n - k + 1 + i - 1) / i;
        int ie = n / i;
        int np1 = nextPrimePos[is];
        int np2 = prevPrimePos[ie];
        if (np1 < start) np1 = start;
        if (np2 >= p1) np2 = p1 - 1;
        p1 = np1;
        p2 = np2;
        if (p2 >= p1) result = (result * (long long int)memo[p1][p2 - p1]) % MOD;
        if (ie <= k) {
            p1--;
            if (p1 >= start) result = (result * (long long int)memo[start][p1 - start]) % MOD;
            break;
        }
    }

    return result;
}

int main(void) {
    FOR(i, MAX_M) isPrime[i] = true;
    isPrime[0] = isPrime[1] = false;
    FOR(i, MAX_M)
        if (isPrime[i]) {
            primePos[i] = primeCount;
            prime[primeCount++] = i;
            for(int j=i + i;j<MAX_M;j += i) isPrime[j] = false;
        }
    FOR(i, MAX_PRIMES) {
        int result = 1;
        for(int j=0;j<MAX_INT_LENGTH && i + j < MAX_PRIMES;j++) {
            result = (result * (long long int)prime[i + j]) % MOD;
            memo[i][j] = result;
        }
    }

    int last = -1;
    FOR(i, MAX_M) {
        if (isPrime[i]) last++;
        prevPrimePos[i] = last;
    }
    last = primeCount;
    for(int i=MAX_M - 1;i>=0;i--) {
        if (isPrime[i]) last--;
        nextPrimePos[i] = last;
    }

    int t = getInt();
    int n = getInt();
    int k = getInt();
    int a = getInt();
    int b = getInt();
    int m = getInt();
    FOR(i, t - 1) c[i] = getInt();
    int result = solve(n, k);
    print(result);
    FOR(tt, t - 1) {
        n = 1 + (a * (long long int)result + c[tt]) % m;
        k = 1 + (b * (long long int)result + getInt()) % n;
        result = solve(n, k);
        print(result);
    }
}

