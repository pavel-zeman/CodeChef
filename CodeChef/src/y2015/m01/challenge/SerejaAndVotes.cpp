// Total of all Bi-s must be at least 100 and less than 100 + number of non-zero elements
// http://www.codechef.com/JAN15/problems/SEAVOTE
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
        int total = 0;
        int nonZero = 0;
        FOR(i, n) {
            int b = getInt();
            total += b;
            if (b > 0) nonZero++;
        }
        printf(total >= 100 && total < 100 + nonZero ? "YES\n" : "NO\n");
    }
}
