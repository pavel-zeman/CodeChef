// Divide n by 2 and round up to the nearest integer and overwrite original n. If n is < 7, then return 0. Otherwise the result is comb(n - 1, 6).
// http://www.codechef.com/SEPT14/problems/RAINBOWB
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

#define MOD 1000000007
#define DIV 301388891

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

long long int comb(int n, int k) {
    long long int result = 1;
    int t = n;
    while (t > n - k) result = (result * t--) % MOD;
    return result * DIV % MOD;
}

int main(void) {
    int n = getInt();
    n = (n >> 1) + (n & 1);
    printf("%lld\n", n < 7 ? 0 : comb(n - 1, 6));
}
