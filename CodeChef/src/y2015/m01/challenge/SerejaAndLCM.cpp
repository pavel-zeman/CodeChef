// Exclusion and inclusion principle - for each D = p1^i1 * p2^i2 * p3^i3 ..., the result is M^N - #{i; i = 1..M && i is not divisible by p1^i1} - the same for p2^i2 ... + the same for all pairs of pi - the same for all triplets of pi ...
// http://www.codechef.com/JAN15/problems/SEALCM
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_M 1010
#define MOD 1000000007



int primeCount;
int primes[200];
bool isPrime[MAX_M];
int n, m, l, r;

int currentPrimes[10];
int currentPrimeCount;
bool currentUsed[10];


char c = 0;
int getInt() {
    int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}


long long int power(int a, int b) {
    long long int square = a;
    long long int result = 1;
    while (b > 0) {
        if ((b & 1) != 0) result = result * square % MOD;
        b >>= 1;
        square = square * square % MOD;
    }
    return result;
}

long long int countWithMissing(int start, int remain) {
    long long int total = 0;
    if (remain > 0) {
        FORE(i, start, currentPrimeCount) {
            if (!currentUsed[i]) {
                currentUsed[i] = true;
                total = (total + countWithMissing(i + 1, remain - 1)) % MOD;
                currentUsed[i] = false;
            }
        }
    } else {
        int validNumbers = 0;
        FORE(i, 1, m + 1) {
            bool valid = true;
            FOR(j, currentPrimeCount) if (currentUsed[j] && i % currentPrimes[j] == 0) {
                valid = false;
                break;
            }
            if (valid) validNumbers++;
        }
        total = power(validNumbers, n);
    }
    return total;
}

long long int solve(int d) {
    long long int result = power(m, n);
    if (d > 1) {
        currentPrimeCount = 0;
        FOR(i, primeCount)
            if (d % primes[i] == 0) {
                int p = 1;
                while (d % (primes[i] * p) == 0) p *= primes[i];
                currentPrimes[currentPrimeCount++] = p;
            }

        FOR(i, currentPrimeCount) {
            long long int temp = countWithMissing(0, i + 1);
            if ((i & 1) == 0) result = (result + MOD - temp) % MOD; else result = (result + temp) % MOD;
        }
    }
    return result;
}

int main(void) {
    FOR(i, MAX_M) isPrime[i] = true;
    isPrime[0] = isPrime[1] = false;
    primeCount = 0;
    FORE(i, 2, MAX_M) if (isPrime[i]) {
        for(int j = i + i;j < MAX_M; j += i) isPrime[j] = false;
        primes[primeCount++] = i;
    }

    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();
        l = getInt();
        r = getInt() + 1;

        long long int total = 0;
        FORE(i, l, r) total += solve(i);
        printf("%lld\n", total % MOD);
    }
}
