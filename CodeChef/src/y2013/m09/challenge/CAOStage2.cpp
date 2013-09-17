// No magic
// http://www.codechef.com/SEPT13/problems/CAOS2
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 510
#define WALL '#'


int primes[] = {2, 3, 5, 7, 11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251};
int primeCount[MAX_N];

char map[MAX_N][MAX_N];
int min[MAX_N][MAX_N];

int minf(int a, int b) {
    return a < b ? a : b;
}

int updateCounter(int counter, int row, int column) {
    return map[row][column] == WALL ? 0 : counter + 1;
}

int main(void) {
    int pos = 0;
    int counter = 0;
    FOR(i, (int)(sizeof(primes)/sizeof(primes[0]))) {
        while (pos < primes[i]) primeCount[pos++] = counter;
        counter++;
    }


    int t;
    scanf("%d", &t);
    FOR(i, t) {
        int r, c;
        scanf("%d%d", &r, &c);
        FOR(j, r) scanf("%s", map[j]);

        FOR(j, r) FOR(k, c) min[j][k] = MAX_N;

        FOR(j, c) {
            int counter = 0;
            FOR(k, r) {
                min[k][j] = minf(min[k][j], counter);
                counter = updateCounter(counter, k, j);
            }
            counter = 0;
            FOR(k, r) {
                min[r - 1 - k][j] = minf(min[r - 1 - k][j], counter);
                counter = updateCounter(counter, r - 1 - k, j);
            }
        }

        FOR(k, r) {
            int counter = 0;
            FOR(j, c) {
                min[k][j] = minf(min[k][j], counter);
                counter = updateCounter(counter, k, j);
            }
            counter = 0;
            FOR(j, c) {
                min[k][c - 1 - j] = minf(min[k][c - 1 - j], counter);
                counter = updateCounter(counter, k, c - 1 - j);
            }
        }

        int result = 0;
        FOR(j, c) FOR(k, r) if (map[k][j] != WALL) result += primeCount[min[k][j]];
        printf("%d\n", result);
    }
}
