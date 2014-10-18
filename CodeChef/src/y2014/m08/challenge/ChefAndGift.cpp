// Count number of even numbers and compare it with k (and handle special case, when k = 0)
// http://www.codechef.com/AUG14/problems/PRGIFT
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

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
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int k = getInt();
        int totalEven = 0;
        FOR(i, n) totalEven += (getInt() & 1) ^ 1;
        printf("%s\n", totalEven < k || (k == 0 && totalEven == n) ? "NO" : "YES");
    }
}
