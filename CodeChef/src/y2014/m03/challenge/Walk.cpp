// Just simple maximum
// http://www.codechef.com/MARCH14/problems/WALK
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

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
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int res = 0;
        FOR(i, n) {
            res = max(res, getInt() + i);
        }
        printf("%d\n", res);
    }
}
