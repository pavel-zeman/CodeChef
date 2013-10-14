// Just get all the dividers and check them one by one
// http://www.codechef.com/OCT13/problems/MAANDI
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

int check(int value) {
    while (value > 0) {
        if (value % 10 == 7 || value % 10 == 4) return 1;
        value /= 10;
    }
    return 0;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int total = 0;
        int divider = 1;
        while (divider * divider <= n) {
            if (n % divider == 0) {
                int div2 = n / divider;
                total += check(divider);
                if (div2 != divider) total += check(div2);
            }
            divider++;
        }
        printf("%d\n", total);
    }
}
