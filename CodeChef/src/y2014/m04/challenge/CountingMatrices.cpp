// Simply calculate all the possibilities
// http://www.codechef.com/APRIL14/problems/CNPIIM
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
        for (int i=1;i <= n - i;i++) {
            int product = i * (n - i);
            int temp = 0;
            for(int j=1;j*j<product;j++) {
                int div = product / j;
                if (div * j == product) div--;
                temp += (div - j) * 2 + 1;
            }
            total += temp;
            if (i < n - i) total += temp;
        }
        printf("%lld\n", total);
    }
}
