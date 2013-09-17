// Maximum number of spoons for n cities is Comb(n, n/2)
// http://www.codechef.com/SEPT13/problems/SPOONS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_C 65

long long int comb[MAX_C][MAX_C];
long long int data[MAX_C];

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


int main(void) {
    FOR(i, MAX_C) {
        comb[i][0] = comb[i][i] = 1;
        FORE(j, 1, i) comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        data[i] = comb[i][i >> 1];
    }

    int t = getInt();
    FOR(tt, t) {
        long long int n = getInt();
        int i = 2;
        while (data[i] < n) i++;
        printf("%d\n", i);
    }
}
