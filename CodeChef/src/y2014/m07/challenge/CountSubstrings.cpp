// Calculate running totals of number of 1s and then use it to calculate the result
// http://www.codechef.com/JULY14/problems/CSUB
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

int total[MAX_N];

char input[MAX_N];

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(i, t) {
        int n;
        scanf("%d", &n);
        scanf("%s", input);

        total[n] = 0;
        for(int i=n-1;i>=0;i--) total[i] = total[i + 1] + input[i] - '0';

        long long int result = 0;
        FOR(i, n) if (input[i] == '1') result += total[i];

        printf("%lld\n", result);
    }
}
