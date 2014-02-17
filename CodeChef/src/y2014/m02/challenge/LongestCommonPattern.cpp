// Calculate histogram of all characters and them sum the intersection
// http://www.codechef.com/FEB14/problems/LCPESY
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_LENGTH 10010

char a[MAX_LENGTH], b[MAX_LENGTH];

int ha[128], hb[128];

void generateHistogram(char *data, int *histogram) {
    while (*data) {
        histogram[(int)*data]++;
        data++;
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        scanf("%s%s", a, b);
        FOR(i, 128) ha[i] = hb[i] = 0;
        generateHistogram(a, ha);
        generateHistogram(b, hb);

        int total = 0;
        FOR(i, 128) total += min(ha[i], hb[i]);
        printf("%d\n", total);
    }
}


