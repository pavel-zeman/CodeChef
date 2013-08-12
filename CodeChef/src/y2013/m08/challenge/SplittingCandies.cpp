// Simple division and modulo
// http://www.codechef.com/AUG13/problems/SPCANDY
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
    FOR(tt, t) {
        long long int n, k;
        scanf("%lld%lld", &n, &k);
        printf("%lld %lld\n", k == 0 ? 0 : n / k, k == 0 ? n : n % k);
    }
}
