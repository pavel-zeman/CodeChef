// Manacher algorithm (but solved just a few minutes after the contest was over)
// http://www.codechef.com/COOK44/problems/PALIN3
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1000010

char s[MAX_N];
char s2[MAX_N * 2];

int maxSum[MAX_N * 2];
int p[MAX_N * 2];
int pWithoutZeros[MAX_N * 2];

long long int total = 0;

void calc(int length) {
    int c = 0;
    int r = 0;
    maxSum[0] = 0;
    p[0] = 0;
    pWithoutZeros[0] = 0;
    FORE(i, 1, length) {
        int mirror = c - (i - c);
        int newP = 0;

        if (r > i && p[mirror] < r - i) {
            // just copy the data
            p[i] = p[mirror];
            pWithoutZeros[i] = pWithoutZeros[mirror];
            maxSum[i] = maxSum[mirror];
        } else if (r > i && p[mirror] > r - i) {
            // the palindrom length is clear, but we need to recalculate the requested totals
            newP = p[i] = r - i;

            maxSum[i] = s2[i] == '#' ? 0 : s2[i];
            pWithoutZeros[i] = s2[i] != '#' && s2[i] % 3 == 0 ? 1 : 0;
            FOR(j, newP) {
                if (s2[i - j - 1] != '#') {
                    maxSum[i] += 2 * s2[i - j - 1];
                    if (s2[i - j - 1] != 0 && maxSum[i] % 3 == 0) pWithoutZeros[i]++;
                }
            }
        } else {
            // palindrom must be extended - we start from what we know and add new items
            newP = r - i;
            if (newP < 0) newP = 0;
            while (newP < i && i + newP < length - 1 && s2[i - newP - 1] == s2[i + newP + 1]) newP++;

            p[i] = newP;

            int start = 0;
            if (r > i) {
                maxSum[i] = maxSum[mirror];
                pWithoutZeros[i] = pWithoutZeros[mirror];
                start = r - i;
            } else {
                maxSum[i] = s2[i] == '#' ? 0 : s2[i];
                pWithoutZeros[i] = s2[i] != '#' && s2[i] % 3 == 0 ? 1 : 0;
            }
            FORE(j, start, newP) {
                if (s2[i - j - 1] != '#') {
                    maxSum[i] += 2 * s2[i - j - 1];
                    if (s2[i - j - 1] != 0 && maxSum[i] % 3 == 0) pWithoutZeros[i]++;
                }
            }
        }

        total += pWithoutZeros[i];
        if (i + p[i] > r) {
            r = i + p[i];
            c = i;
        }
    }
}

int main(void) {
    scanf("%s", s);
    char *t = s;
    char *r = s2;
    *r++ = '#';
    while (*t) {
        *r++ = *t++ - '0';
        *r++ = '#';
    }
    *r = 0;
    int length = (t - s) * 2 + 1;
    calc(length);

    printf("%lld\n", total);
}
