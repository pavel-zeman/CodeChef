// Probability = n * probability, that a pair selected at random wins
// http://www.codechef.com/OCT13/problems/ARRGAME2
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100004

int a[MAX_N], b[MAX_N];
int n;

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

int cmp(const void *p1, const void *p2) {
    return *((int *)p1) - *((int *)p2);
}

int findFirst(int value) {
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int middle = (left + right) >> 1;
        if (b[middle] < value) left = middle + 1; else right = middle - 1;
    }
    if (right < 0) right++;
    if (b[right] < value) right++;
    return right;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) a[i] = getInt();
        FOR(i, n) b[i] = getInt();

        qsort(b, n, sizeof(b[0]), cmp);

        int ones = 0;
        int twos = 0;
        FOR(i, n) {
            if (b[i] == 1) ones++;
            else if (b[i] == 2) twos++;
            else break;
        }

        long long int totalWins = 0;
        FOR(i, n) {
            if (a[i] > 1) {
                totalWins += n - findFirst(a[i] == 2 ? 5 : a[i] + 1);
                if (a[i] >= 2) totalWins += ones;
                if (a[i] == 3) totalWins += twos;
            }
        }
        printf("%lf\n", (double) totalWins / n);
    }
}
