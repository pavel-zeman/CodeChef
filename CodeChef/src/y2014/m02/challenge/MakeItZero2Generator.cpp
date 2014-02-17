// Generator of test data
// http://www.codechef.com/FEB14/problems/LMATRIX2
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100

int a[MAX_N][MAX_N], p[MAX_N][MAX_N];

int n, m;


int main(void) {
    int n = 99;
    int m = 99;

    srand(time(NULL));

    FOR(i, n) FOR(j, m) p[i][j] = rand() % 9 + 1;
    FOR(i, n) FOR(j, m) a[i][j] = rand() % p[i][j];

    printf("%d %d\n", 99, 99);
    FOR(i, n) {
        FOR(j, m) printf("%d ", p[i][j]);
        printf("\n");
    }
    FOR(i, n) {
        FOR(j, m) printf("%d ", a[i][j]);
        printf("\n");
    }


}
