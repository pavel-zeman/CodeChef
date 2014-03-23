// The first player wins, if N is not prime, otherwise it loses (but there are 5 exceptions - 2, 16, 17, 34, 289)
// http://www.codechef.com/COOK44/problems/DIVIDING
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define N 20000
#define MAX_P 10000

bool win[N];
bool prime[N];
int primes[MAX_P];
int primeCount = 0;

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


bool checkPrime(int a) {
    int p = 0;
    while (primes[p] * primes[p] <= a) {
        if (a % primes[p] == 0) return false;
        p++;
    }
    return true;
}

int main(void) {
    FOR(i, N) prime[i] = true;
    FORE(i, 2, N) {
        if (prime[i]) {
            int j = i + i;
            while (j < N) {
                prime[j] = false;
                j += i;
            }
            primes[primeCount++] = i;
        }
    }

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        bool first;
        if (n == 2 || n == 17) first = true;
        else  if (n == 16 || n == 34 || n == 289) first = false;
        else first = !checkPrime(n);
        printf(first ? "Mike\n" : "Tom\n");
    }
}
