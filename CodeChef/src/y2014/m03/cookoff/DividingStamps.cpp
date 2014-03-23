// The total value must be N * (N + 1) / 2
// http://www.codechef.com/COOK44/problems/DIVIDING
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

long long int f(long long int n) {
    return n * (n + 1) / 2;
}

int main(void) {
    int n = getInt();
    long long int total = 0;
    FOR(i, n) total += getInt();
    long long int res = (-1 + sqrt(1 + 8 * total)) / 2;
    while (f(res) > total) res--;
    while (f(res) < total) res++;
    printf(f(res) == total ? "YES\n" : "NO\n");
}
