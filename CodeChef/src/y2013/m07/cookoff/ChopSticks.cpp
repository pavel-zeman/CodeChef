// Sort the lengths and the choose following 2, if their difference is less than D
// http://www.codechef.com/COOK36/submit/TACHSTCK
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100100

int n;
int d;
int l[MAX_N];


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
    return *((int *)p1) - *((int *)p2);
}


int main(void) {
    int n = getInt();
    int d = getInt();
    FOR(i, n) l[i] = getInt();
    qsort(l, n, sizeof(l[0]), cmp);

    int i = 0;
    int total = 0;
    while (i < n - 1) {
        if (l[i + 1] - l[i] <= d) {
            total++;
            i += 2;
        } else
            i++;
    }
    printf("%d", total);

}
