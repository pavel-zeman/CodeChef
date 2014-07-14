// The expected color for each object depends on the number of paintings. For each painting the color is calculated as 1/2 * original color + 1/2 * all possible paintings.
// http://www.codechef.com/JULY14/problems/LEPAINT
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

#define MAX_N 51
#define MAX_C 101
#define MAX_K 55

double prob1[MAX_C];
double prob2[MAX_C];

double probStep[MAX_K];
int changes[MAX_N];


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
        int c = getInt();
        int k = getInt();

        FOR(j, c) prob1[j] = 0;
        prob1[1] = 1;
        probStep[0] = 1;

        FOR(kk, k) {
            FOR(j, c) prob2[j] = prob1[j] / 2;
            FOR(j, c) FOR(k, c) prob2[j * k % c] += prob1[j] / 2 / c;
            FOR(j, c) prob1[j] = prob2[j];
            double temp = 0;
            FOR(j, c) temp += j * prob1[j];
            probStep[kk + 1] = temp;
        }

        FOR(i, n) changes[i] = 0;
        FOR(kk, k) {
            int l = getInt() - 1, r = getInt();
            FORE(i, l, r) changes[i]++;
        }

        double result = 0;
        FOR(i, n) result += probStep[changes[i]];
        printf("%.10lf\n", result);
    }
}
