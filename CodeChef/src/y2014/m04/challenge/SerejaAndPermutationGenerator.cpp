// Just generator of random input data
// http://www.codechef.com/APRIL14/problems/SEAPERM
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 2002

int a[MAX_N];
int res[MAX_N];
int resCount;
bool used[MAX_N];
int n, k, s;

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
    int t = 1000;
    printf("%d\n", t);
    FOR(tt, t) {
        int n = rand() % 2000 + 1;
        int k = rand() % n + 1;
        int s = rand() % 1000000000 + 1;
        FOR(i, n) a[i] = rand() % 10000 + 1;
        printf("%d %d %d\n", n, k, s);
        FOR(i, n) printf("%d ", a[i]);
        printf("\n");
    }
}
