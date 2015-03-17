// Cosine functions never intersect each other at x-axis, so they can add up to 1 intersection. The number of intersections of l sine functions is 2^(s-l) (+ 2 points (0, 2*pi) with exactly s intersections).
// http://www.codechef.com/MARCH15/problems/SIGNWAVE
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
        int s = getInt();
        int c = getInt();
        int k = getInt();
        long long int total = 0;
        if (s == 0) {
            if (k == 1) total = (1LL << (c + 1)) - 2;
        } else {
            if (k == 1) {
                int m = s;
                if (c + 1 > m) m = c + 1;
                total = (1LL << m) + 1;
            } else if (k <= s) {
                total = (1LL << (s - k + 1)) - 1 + 2;
                if (c > s - k) total += 1LL << (s - k + 1);

            }
        }
        printf("%lld\n", total);
    }
}
