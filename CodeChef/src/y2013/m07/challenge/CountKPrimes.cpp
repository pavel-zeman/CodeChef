// http://www.codechef.com/JULY13/problems/KPRIME
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


#define MAX_PRIMES 100200
#define MAX_B 100100
#define MAX_K 6

int factorCount[MAX_PRIMES];
int count[MAX_B][MAX_K];


void generatePrimes() {
    FOR(i, MAX_PRIMES) factorCount[i] = 0;
    FORE(i, 2, MAX_PRIMES) {
        if (factorCount[i] == 0) {
            factorCount[i]++;
            for(int current = i + i;current < MAX_PRIMES;current += i) {
                factorCount[current]++;
            }
        }
    }
}

void generateCounts() {
    FOR(i, MAX_K) count[0][i] = count[1][i] = 0;
    FORE(i, 2, MAX_B) {
        FOR(j, MAX_K) count[i][j] = count[i - 1][j];
        if (factorCount[i] < MAX_K) count[i][factorCount[i]]++;
    }
}


int main(void) {
    generatePrimes();
    generateCounts();

    int t;
    scanf("%d", &t);
    FOR(i, t) {
        int a, b, k;
        scanf("%d%d%d", &a, &b, &k);
        printf("%d\n", count[b][k] - count[a - 1][k]);
    }
}
