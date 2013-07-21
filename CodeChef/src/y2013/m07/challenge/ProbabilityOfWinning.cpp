// No magic - the answer is always simply t1 / (t1 + t2)
// http://www.codechef.com/JULY13/problems/PROB
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
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int a = getInt(), b = getInt();
        getInt();
        getInt();
        printf("%lf\n", (double)a / (a + b));
    }
}
