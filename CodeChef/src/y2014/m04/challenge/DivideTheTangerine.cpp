// Sort the "cuts" and check, whether the boy's cuts are a subset of the chef's cuts
// http://www.codechef.com/APRIL14/problems/TANGDIV
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_PIECES 510

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
    return (*(int *)p1) - (*(int *)p2);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        getInt(); // ignore n
        int k = getInt(), p = getInt();
        int l[MAX_PIECES];
        int a[MAX_PIECES];

        FOR(i, k) {
            getInt(); // ignore start of interval
            l[i] = getInt();
        }
        FOR(i, p) {
            getInt(); // ignore start of interval
            a[i] = getInt();
        }
        qsort(l, k, sizeof(l[0]), cmp);
        qsort(a, p, sizeof(l[0]), cmp);
        bool ok = true;
        int j = 0;
        FOR(i, p) {
            while (j < k && l[j] < a[i]) j++;
            if (j == k || l[j] != a[i]) {
                ok = false;
                break;
            }
        }
        printf("%s\n", ok ? "Yes" : "No");
    }
}
