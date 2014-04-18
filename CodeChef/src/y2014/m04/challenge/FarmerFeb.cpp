// Just enumerate all primes less than 3000 and then choose the smallest one greater than x + y
// http://www.codechef.com/APRIL14/problems/POTATOES
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 3000

using namespace std;

bool prime[MAX_N];
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

void calcPrimes() {
    prime[0] = prime[1] = false;
    FORE(i, 2, MAX_N) prime[i] = true;
    int i = 2;
    while (i * i <= MAX_N) {
        if (prime[i]) for(int j=i+i;j<MAX_N;j+=i) prime[j] = false;
        i++;
    }
}

int main(void) {
    calcPrimes();
    int t = getInt();
    FOR(tt, t) {
        int x = getInt();
        int y = getInt();
        int z = x + y + 1;
        while (!prime[z]) z++;
        printf("%d\n", z - x - y);
    }
}
