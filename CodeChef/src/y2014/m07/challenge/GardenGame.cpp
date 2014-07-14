// Calculate cycle length of all cycles and then calculate the lowest common product of these cycle lengths
// http://www.codechef.com/JULY14/problems/SGARDEN
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010
#define MOD 1000000007
#define MAX_PRIMES 10000


int a[MAX_N];
bool used[MAX_N];
bool prime[MAX_N];
int primes[MAX_PRIMES];
int primeCount = 0;
int countUsed[MAX_PRIMES];

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


int max(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    FOR(i, MAX_N) prime[i] = true;
    prime[0] = prime[1] = false;
    FORE(i, 2, MAX_N) {
        if (prime[i]) {
            for(int j = i + i;j<MAX_N;j += i) {
                prime[j] = false;
            }
            primes[primeCount++] = i;
        }
    }

    int t = getInt();
    FOR(tt, t) {
        FOR(i, primeCount) countUsed[i] = 0;

        int n = getInt();
        FOR(i, n) a[i] = getInt() - 1, used[i] = false;

        FOR(i, n)
            if (!used[i]) {
                // count cycle length
                int c = 1;
                int t = a[i];
                used[i] = true;
                while (t != i) {
                    used[t] = true;
                    c++;
                    t = a[t];
                }
                // take cycle length and factorize it
                for(int j=0;j<primeCount && c > 1;j++) {
                    int q = 0;
                    while (c % primes[j] == 0) { c /= primes[j]; q++;}
                    countUsed[j] = max(countUsed[j], q);
                }
            }
        long long int result = 1;
        FOR(i, primeCount) FOR(j, countUsed[i]) result = result * primes[i] % MOD;
        printf("%lld\n", result);
    }
}
