//
// http://www.codechef.com/OCT13/problems/LEBAMBOO
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 52

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

int abs(int a) {
    return a < 0 ? -a : a;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int src[MAX_N], dst[MAX_N];
        int srcSum = 0, dstSum = 0;
        FOR(i, n) srcSum += (src[i] = getInt());
        FOR(i, n) dstSum += (dst[i] = getInt());

        int result = -1;
        if (n == 1) {
            if (dstSum <= srcSum) result = srcSum - dstSum;
        } else if (n == 2) {
            if (dstSum == srcSum) result = abs(src[0] - dst[0]);
        } else {
            if (dstSum >= srcSum) {
                int step = n - 2;
                result = (dstSum - srcSum) / step;
                FOR(i, n) {
                    if (abs(src[i] - dst[i]) <= result && abs(src[i] - dst[i]) % 2 == result % 2) {
                    } else {
                        result = -1;
                        break;
                    }
                }
            }
        }
        printf("%d\n", result);
    }
}
