// No magic - sorts the bottles in each room and uses the biggest ones
// http://www.codechef.com/AUG13/problems/LELEMON
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 110
#define MAX_BOTTLES 110


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
    return *((int *)p2) - *((int *)p1);
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();

        int roomVisits[MAX_N];
        FOR(i, n) roomVisits[i] = 0;
        FOR(i, m) {
            roomVisits[getInt()]++;
        }

        int bottle[MAX_BOTTLES];
        int total = 0;
        FOR(i, n) {
            int b = getInt();
            FOR(j, b) bottle[j] = getInt();
            qsort(bottle, b, sizeof(bottle[0]), cmp);
            for(int j=0;j<roomVisits[i] && j<b;j++) total += bottle[j];
        }

        printf("%d\n", total);
    }
}
