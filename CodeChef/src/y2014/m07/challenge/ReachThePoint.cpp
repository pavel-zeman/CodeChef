// The path must be "zig-zag", i.e. to increase coordinate by 1, we need either 1 or 3 steps
// http://www.codechef.com/JULY14/problems/RETPO
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

int abs(int a) {
    return a < 0 ? -a : a;
}

int min(long long int a, long long int b) {
    return a < b ? a : b;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        long long int x = abs(getInt()), y = abs(getInt());
        long long int m = min(x, y);
        long long int result = m * 2;

        if (x > m) result += (x - m) / 2 + (x - m - (x - m) /2) * 3;
        else if (y > m) result += ((y - m) / 2) * 3 + (y - m - (y - m) /2);

        printf("%lld\n", result);
    }
}
