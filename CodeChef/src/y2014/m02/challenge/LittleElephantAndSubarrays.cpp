// Checks all possible subarrays
// http://www.codechef.com/FEB14/problems/SUBMIN
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 60

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

int min(int a, int b) {
    return a < b ? a : b;
}

int main(void) {
    int n = getInt();
    int a[MAX_N];
    FOR(i, n) a[i] = getInt();
    int q = getInt();
    FOR(qq, q) {
        int k = getInt();
        int total = 0;

        FOR(i, n) {
            int m = a[i];
            FORE(j, i, n) {
                m = min(m, a[j]);
                if (m == k) total++;
            }
        }
        printf("%d\n", total);
    }
}

