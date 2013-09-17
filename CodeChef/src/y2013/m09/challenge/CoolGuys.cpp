// O(sqrt(n)) algorithm, which counts number of times a number from 1 to sqrt(N) divides all numbers from 1 to N
// http://www.codechef.com/SEPT13/problems/COOLGUYS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX 32000
#define PRIME_COUNT 4000

int count[MAX];
int primes[PRIME_COUNT];
int primeCount = 0;
bool sieve[MAX];


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


int main(void) {
    FOR(i, MAX) sieve[i] = true;
    FORE(i, 2, MAX) {
        if (sieve[i]) {
            primes[primeCount++] = i;
            for(int j = i + i;j<MAX;j += i) sieve[j] = false;
        }
    }

    int t = getInt();
    FOR(tt, t) {
        long long int result1 = 0;
        int n = getInt();
        int i = 1;
        while (true) {
            result1 += (count[i] = n / i);
            if (count[i] <= i) {
                count[i] = i;
                break;
            }
            i++;
        }
        FORE(j, 1, i) {
            result1 += j * (count[j] - count[j + 1]);
        }

        long long int result2 = ((long long int )n) * n;
        FOR(i, primeCount) {
            if (result1 < primes[i]) break;
            while (result1 % primes[i] == 0 && result2 % primes[i] == 0) {
                result1 /= primes[i];
                result2 /= primes[i];
            }
        }
        while (n > 1 && result1 % n == 0 && result2 % n == 0) {
            result1 /= n;
            result2 /= n;
        }
        printf("%lld/%lld\n", result1, result2);

    }
}
