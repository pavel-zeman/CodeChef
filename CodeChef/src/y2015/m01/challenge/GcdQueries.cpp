// Precalculate the values of GDC for every "prefix" of A and every "suffix" of A, so that each query can be answered in constant time
// http://www.codechef.com/JAN15/problems/GCDQ
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

#define MAX_N 100010

int a[MAX_N];
int prefix[MAX_N];
int postfix[MAX_N];


int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

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
        int q = getInt();
        FOR(i, n) a[i] = getInt();

        prefix[0] = a[0];
        FORE(i, 1, n) prefix[i] = gcd(prefix[i - 1], a[i]);
        postfix[n - 1] = a[n - 1];
        FORE(i, 1, n) postfix[n - i - 1] = gcd(postfix[n - i], a[n - i - 1]);

        FOR(i, q) {
            int l = getInt() - 1;
            int r = getInt() - 1;
            int result = l > 0 ? prefix[l - 1] : postfix[r + 1];
            if (r < n - 1) result = gcd(result, postfix[r + 1]);
            printf("%d\n", result);
        }
    }
}
