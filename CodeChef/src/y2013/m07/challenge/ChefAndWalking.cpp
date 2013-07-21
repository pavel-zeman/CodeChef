// http://www.codechef.com/JULY13/problems/CHRECT
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)




int main(void) {
    int t;
    scanf("%d", &t);
    FOR(i, t) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        printf("%d\n", n * m <= 2 ? 0 : (n == 1 || m == 1 ? k : k / 2 + k % 2));
    }
}
