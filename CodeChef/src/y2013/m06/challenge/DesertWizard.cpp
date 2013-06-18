#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


#define MAXN 11000

int d[MAXN];
int n;

long long max1[MAXN], max2[MAXN]; // maximum from the beginning to i, maximum from i to the end
long long min1[MAXN], min2[MAXN];

long long mx1[MAXN], mx2[MAXN];
long long mn1[MAXN], mn2[MAXN];

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long min(long long a, long long b) {
    return a > b ? b : a;
}

long long abs(long long a) {
    return a >= 0 ? a : - a;
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        scanf("%d", &n);
        FOR(i, n) scanf("%d", &d[i]);

        max1[0] = d[0];
        min1[0] = d[0];
        FORE(i, 1, n) {
            max1[i] = max(max1[i - 1] + d[i], d[i]);
            min1[i] = min(min1[i - 1] + d[i], d[i]);
        }

        max2[n - 1] = d[n - 1];
        min2[n - 1] = d[n - 1];
        for(int i=n-2;i>=0;i--) {
            max2[i] = max(max2[i + 1] + d[i], d[i]);
            min2[i] = min(min2[i + 1] + d[i], d[i]);
        }

        mx1[0] = max1[0];
        mn1[0] = min1[0];
        FORE(i, 1, n) {
            mx1[i] = max(mx1[i - 1], max1[i]);
            mn1[i] = min(mn1[i - 1], min1[i]);
        }

        mx2[n - 1] = max2[n - 1];
        mn2[n - 1] = min2[n - 1];
        for(int i=n-2;i>=0;i--) {
            mx2[i] = max(mx2[i + 1], max2[i]);
            mn2[i] = min(mn2[i + 1], min2[i]);
        }


        long long result = 0;
        FOR(i, n - 1) {
            result = max(result, abs(mn1[i] - mx2[i + 1]));
            result = max(result, abs(mx1[i] - mn2[i + 1]));
        }
        printf("%lld\n", result);

    }
}
