// No magic - simply calculate the number of likes until reaching L (less than 32 steps are always required)
// http://www.codechef.com/JAN14/problems/PLZLYKME
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
    int t = getInt();
    FOR(tt, t) {
        long long int l = getInt();
        int d = getInt();
        long long int s = getInt();
        long long int c = getInt();
        FORE(i, 1, d) {
            if (s >= l) break;
            s = s * (1 + c);
        }
        printf("%s\n", s >= l ? "ALIVE AND KICKING" : "DEAD AND ROTTING");
    }
}

