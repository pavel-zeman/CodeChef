// Keep count of 2s and numbers greater than 2 and add to total for each number (pairs containing 0s and 1s don't satisfy the condition)
// http://www.codechef.com/MARCH14/problems/PROSUM
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

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int countTwo = 0;
        int countGreater = 0;
        long long int total = 0;

        FOR(i, n) {
            int a = getInt();
            if (a == 2) {
                total += countGreater;
                countTwo++;
            } else if (a > 2) {
                total += countTwo + countGreater;
                countGreater++;
            }
        }

        printf("%lld\n", total);
    }
}
