// Nothing special here, just try all the possibilities
// http://www.codechef.com/JULY15/problems/CHCUBE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_LENGTH 20


char color[6][MAX_LENGTH];

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

bool equal(int a, int b, int c) {
    return !strcmp(color[a], color[b]) && !strcmp(color[b], color[c]);
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        FOR(i, 6) scanf("%s", color[i]);
        puts(equal(0, 2, 5) || equal(0, 3, 5) || equal(1, 3, 5) || equal(1, 2, 5) ||
             equal(0, 2, 4) || equal(0, 3, 4) || equal(1, 3, 4) || equal(1, 2, 4) ? "YES" : "NO");
    }
}
