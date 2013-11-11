// Special number must be prime or square number. So we find all the primes and then check all squares one by one.
// http://www.codechef.com/NOV13/problems/PRETNUM
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_PRIME 1000100
#define MAX_DIVISOR 1000010
#define MAX_PRIMES 80000

char prime[MAX_PRIME];
char ok[MAX_DIVISOR];
int primeCount = 0;
int primes[MAX_PRIMES];

char c = 0;
long long int getInt() {
    long long int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

long long int sqr(int a) {
    return ((long long int)a) * a;
}

int check(int a) {
    int count = 0;
    long long int sqra = sqr(a);
    for(int v = 1; v < a; v++) if (sqra % v == 0) count++;
    return prime[count * 2 + 1];
}

int main(void) {
    memset(prime, 1, sizeof(prime));
    prime[0] = prime[1] = 0;
    FORE(i, 2, MAX_PRIME) {
        if (prime[i]) {
            primes[primeCount++] = i;
            int j = i + i;
            while (j < MAX_PRIME) {
                prime[j] = 0;
                j += i;
            }
        }
    }

    int t = getInt();
    FOR(tt, t) {
        long long int l = getInt(), r = getInt();
        int pos = 0;
        int total = r - l + 1;
        int divPos = 0;
        FOR(i, total) ok[i] = 1;

        // check prime numbers
        while (pos <= total) {
            int div = primes[divPos];
            while (sqr(div) > l + pos && pos <= total) pos++;
            if (pos <= total) {
                int rem = (l + pos) % div;
                int start = rem == 0 ? pos : pos + div - rem;
                while (start <= total) {
                    ok[start] = 0;
                    start += div;
                }
            }
            divPos++;
        }

        // add squares
        int start = sqrt(l);
        while (sqr(start) < l) start++;
        for(; sqr(start) <= r; start++) ok[sqr(start) - l] = check(start);

        int count = 0;
        FOR(i, total) count += ok[i];

        printf("%d\n", count);
    }
}
