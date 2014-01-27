// For each table sort the intervals based on (si, fi) and then it's simple linear check
// http://www.codechef.com/JAN14/problems/FGFS
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

int n, k;

struct Guest {
    int start;
    int end;
    int table;
} guests[MAX_N];

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
    Guest *g1 = (Guest *)p1;
    Guest *g2 = (Guest *)p2;
    if (g1->table != g2->table) return g1->table - g2->table;
    if (g1->start != g2->start) return g1->start - g2->start;
    return g1->end - g2->end;
}

int solve(int a, int b) {
    int t2 = guests[a].end;
    int total = 1;
    FORE(i, a + 1, b + 1) {
        if (guests[i].start >= t2) {
            // next interval starts after the end of the current one - count it in
            total++;
            t2 = guests[i].end;
        } else if (guests[i].end < t2) {
            // next interval is fully contained in the current one - decrease the upper bound
            t2 = guests[i].end;
        }
    }
    return total;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        k = getInt();
        FOR(i, n) {
            guests[i].start = getInt();
            guests[i].end = getInt();
            guests[i].table = getInt();
        }
        qsort(guests, n, sizeof(guests[0]), cmp);
        int total = 0;
        int l1 = 0;
        int l2 = 0;
        while (l1 < n) {
            int table = guests[l1].table;
            while (l2 < n && guests[l2].table == table) l2++;
            total += solve(l1, l2 - 1);
            l1 = l2;
        }
        printf("%d\n", total);
    }
}

