// There are 4 situations, that must be checked one by one
// http://www.codechef.com/AUG14/problems/CRAWA
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
        int x = getInt();
        int y = getInt();
        bool result = false;

        if (!result && y > 0 && (y & 1) == 0) result = x >= -y && x <= y - 1;
        if (!result && y <= 0 && (y & 1) == 0) result = x >= y && x <= -y + 1;
        if (!result && x > 0 && (x & 1) == 1) result = y >= -x + 1 && y <= x + 1;
        if (!result && x < 0 && (x & 1) == 0) result = y >= x && y <= -x;

        printf("%s\n", result ? "YES" : "NO");
    }
}
