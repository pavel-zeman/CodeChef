// Unfortunately, this does not work
// http://www.codechef.com/SEPT14/problems/SEABUB
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 120
#define MAX_PAIRS 5000
#define UNKNOWN -10

long double prob[MAX_PAIRS];
long double probCummulative[MAX_PAIRS];
long double resultCache[MAX_PAIRS];
int n, n2;


char c = 0;
long long int getInt() {
    /*long long int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;*/
    long long int r = 0;
    scanf("%lld", &r);
    return r;
}


void initProbs() {
    long double quotient = 1;
    long double sum = 0;
    long double a = 1;
    FOR(i, n2) quotient *= 2;
    //printf("%Lf ", quotient);
    FOR(i, n2 + 1) {
        //printf("%Lf ", a);
        long double t = prob[i] = a / quotient;
        sum += t;
        probCummulative[i] = sum;
        a *= n2 - i;
        a /= (i + 1);
    }
}

long double min(long double a, long double b) {
    return a < b ? a : b;
}

long double calc(int k) {
    long double result = resultCache[k];
    if (result <= -1) {
        if (k == 0) result = ((double)n) * (n - 1) / 4;
        else {
            result = 0;
            long double prevResult = calc(k - 1);
            FORE(i, k + 1, n2 + 1) {
                long double v1 = i - k;
                result += prob[i] * min(v1, prevResult);
                //printf("PrevResult: %Lf, Result: %Lf, Prob: %Lf, I: %d, K: %d\n", prevResult, result, prob[i], i, k);
            }
        }
        resultCache[k] = result;
    }
    return result;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        n2 = n * (n - 1) / 2;
        long long int k = getInt();
        int a[MAX_N];
        FOR(i, n) a[i] = getInt();

        int inversions = 0;
        FOR(i, n) FORE(j, i + 1, n) if (a[i] > a[j]) inversions++;

        if (k == 0) printf("%d\n", inversions); else
        if (inversions <= k) printf("%d\n", 0); else {
            initProbs();
            FOR(i, k) resultCache[i] = UNKNOWN;
            long long int manualInversions = inversions - k;
            double d = calc((int)k - 1);
            //printf("%lld %lf ", manualInversions, d);
            if (manualInversions < d) printf("%lld\n", manualInversions); else printf("%.10lf\n", d);
        }
    }
}
