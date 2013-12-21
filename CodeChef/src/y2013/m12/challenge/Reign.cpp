// Maximum calculated incrementally for the beginning and end of the array
// http://www.codechef.com/DEC13/problems/REIGN
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100020

int a[MAX_N];
long long int first[MAX_N];
long long int last[MAX_N];

char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

long long int max(long long int a, long long int b) {
    return a > b ? a : b;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt(), k = getInt();
        FOR(i, n) a[i] = getInt();

        long long int s = 0;
        FOR(i, n)
            if (s < 0) s = first[i] = a[i]; else first[i] = (s += a[i]);
        s = first[0];
        FOR(i, n) s = first[i] = max(s, first[i]);

        s = 0;
        for(int i=n-1;i>=0;i--)
            if (s < 0) s = last[i] = a[i]; else last[i] = (s += a[i]);
        s = last[n - 1];
        for(int i=n-1;i>=0;i--) s = last[i] = max(s, last[i]);

        s = first[0] + last[k + 1];
        FOR(i, n - k - 1) s = max(s, first[i] + last[i + k + 1]);

        printf("%lld\n", s);
    }
}
