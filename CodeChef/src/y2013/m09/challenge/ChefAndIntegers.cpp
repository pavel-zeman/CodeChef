// Increase all integers, if there are more than X of them. Otherwise increase the integers one by one.
// http://www.codechef.com/SEPT13/problems/INTEG
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010

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

int cmp(const void *p1, const void *p2) {
    return *((int *)p2) - *((int *)p1);
}

int main(void) {
    int n = getInt();
    int totalNumbers = 0;
    int a[MAX_N];
    FOR(i, n) {
        a[totalNumbers] = getInt();
        if (a[totalNumbers] < 0) totalNumbers++;
    }
    long long int x = getInt();

    long long int result = 0;
    if (totalNumbers > 0) {
        if (totalNumbers > x) {
            qsort(a, totalNumbers, sizeof(a[0]), cmp);
            int v = -a[totalNumbers - x];
            result = v * x;
            FORE(i, totalNumbers - x + 1, totalNumbers) result += -a[i] - v;
        } else {
            FOR(i, totalNumbers) result += -a[i];
        }
    }
    printf("%lld\n", result);


}
