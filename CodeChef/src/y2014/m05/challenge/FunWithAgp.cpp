// Just an unsuccessful attempt
// http://www.codechef.com/MAY14/problems/FUNAGP
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010

long long int a[MAX_N];

int n, q, r;
int p1, p2, maxp;

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
        n = getInt();
        q = getInt();
        r = getInt();
        p1 = getInt();
        p2 = getInt();
        maxp = p1 * p2;
        FOR(i, n) a[i] = getInt();
        FOR(qq, q) {
            int operation = getInt();
            int s, d, x, y, mult, g;
            long long int m;
            switch (operation) {
                case 0:
                    s = getInt();
                    d = getInt();
                    x = getInt() - 1;
                    y = getInt();
                    mult = 1;
                    FORE(i, x, y) {
                        a[i] += (s + (i - x) * d) * mult;
                        a[i] %= maxp;
                        mult *= r;
                        mult %= maxp;
                    }
                    break;

                case 1:
                    x = getInt() - 1;
                    g = getInt() - 1;
                    m = a[x];
                    FOR(i, g) {
                        a[x] *= m;
                        a[x] = a[x] % p2;
                    }
                    break;

                case 2:
                    x = getInt() - 1;
                    y = getInt();
                    long long int sum = 0;
                    FORE(i, x, y) {
                        sum += a[i];
                    }
                    printf("%lld\n", sum % p1);
                    break;
            }
        }
    }
}
