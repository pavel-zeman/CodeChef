// No magic - simply selects number with the highest frequency, removes everything else one by one and then removes the number with the highest frequency in a single step
// http://www.codechef.com/AUG13/problems/DELNMS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100002
#define MAX_A 100002

int a[MAX_N];
int n;
int hist[MAX_A];

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
    n = getInt();
    FOR(i, MAX_A) hist[i] = 0;
    FOR(i, n) {
        a[i] = getInt();
        hist[a[i]]++;
    }
    int maxValue = 0;
    int maxPos = -1;
    FOR(i, MAX_A) {
        if (hist[i] > maxValue) {
            maxValue = hist[i];
            maxPos = i;
        }
    }

    printf("%d\n", n - maxValue + 1);
    for(int i=n-1;i>=0;i--) {
        if (a[i] != maxPos) {
            printf("%d %d\n", i + 1, n--);
        }
    }
    printf("1 1\n");
}
