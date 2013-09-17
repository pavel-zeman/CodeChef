// Brute force for n <= 16, otherwise 0
// http://www.codechef.com/SEPT13/problems/LEEXAMS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_A 16

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
        double result = 0;
        if (n > MAX_A) {
            FOR(i, n * 3) getInt();
        } else {
            int p[MAX_A], a[MAX_A], b[MAX_A];
            FOR(i, n) p[i] = getInt(), a[i] = getInt(), b[i] = getInt();
            int cases = (1 << n);
            FOR(i, cases) {
                int used = 0;
                int temp = i;
                bool ok = true;
                FOR(j, n) {
                    int value = (temp & 1) == 0 ? a[j] : b[j];
                    if ((used & (1 << value)) != 0) {
                        ok = false;
                        break;
                    }
                    used |= (1 << value);
                    temp >>= 1;
                }
                if (ok) {
                    temp = i;
                    double tempRes = 1;
                    FOR(j, n) {
                        tempRes *= ((temp & 1) == 0 ? p[j] : (100 - p[j])) / 100.0;
                        temp >>= 1;
                    }
                    result += tempRes;
                }

            }
        }
        printf("%lf\n", result);
    }
}
