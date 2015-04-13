// Brute force solution - sum all the possible factors up to sqrt(N)
// http://www.codechef.com/APRIL15/problems/CHEFLCM
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
        long long int total = 0;
        int c = 1;
        while (c * c < n) {
            if (n % c == 0) {
                total += c;
                total += n / c;
            }
            c++;
        }
        if (c * c == n) total += c;
        printf("%lld\n", total);
    }
}
