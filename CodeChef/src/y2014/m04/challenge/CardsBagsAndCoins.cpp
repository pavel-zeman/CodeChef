// Simple dynamic programming - for each card and possible remainder calculate the number of subsets starting with that card having that remainder
// http://www.codechef.com/APRIL14/problems/ANUCBC
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100002
#define MAX_M 128
#define MOD 1000000009

int card[MAX_N];

int count[2][MAX_M];


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

int abs(int x, int m) {
    if (x < 0) x += m;
    return x;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int q = getInt();
        FOR(i, n) card[i] = getInt();

        FOR(i, q) {
            int m = getInt();
            FOR(j, m) count[0][j] = 0;
            count[0][0] = 1;
            int last = 0;
            int next = 1;

            for(int j=n-1;j>=0;j--) {
                int mod = card[j] % m;
                if (mod < 0) mod += m;
                FOR(jj, m) {
                    count[next][jj] = (count[last][jj] + count[last][abs(jj - mod, m)]) % MOD;
                }
                last ^= 1;
                next ^= 1;
            }
            printf("%d\n", count[last][0]);
        }
    }
}
