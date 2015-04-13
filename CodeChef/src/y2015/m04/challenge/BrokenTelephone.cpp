// Count every number, that is different than the previous one or next one
// http://www.codechef.com/APRIL15/problems/BROKPHON
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
        int last = getInt();
        bool lastCounted = false;
        int total = 0;
        FOR(i, n - 1) {
            int a = getInt();
            if (a != last) {
                if (!lastCounted) total++;
                total++;
                lastCounted = true;
            } else
                lastCounted = false;
            last = a;
        }
        printf("%d\n", total);
    }
}
