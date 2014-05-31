// A % 6 must be 0, 1 or 3
// http://www.codechef.com/MAY14/problems/OJUMPS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

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
    long long int a = getInt();
    int mod = a % 6;
    puts(mod == 0 || mod == 1 || mod == 3 ? "yes" : "no");
}
