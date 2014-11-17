// Just binary numbers and interval halving
// http://www.codechef.com/NOV14/problems/CHEFSEG
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
long long int getInt() {
    long long int r = 0;
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
        long long int x = getInt();
        long long int k = getInt();
        long long int temp = 1;
        double segmentSize = x;
        while (temp <= k) {
            temp <<= 1;
            segmentSize /= 2;
        }
        temp >>= 1;
        printf("%.10lf\n", segmentSize + (k - temp) * 2 * segmentSize);
    }
}
