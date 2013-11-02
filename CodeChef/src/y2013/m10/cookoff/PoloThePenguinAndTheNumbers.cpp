//
// http://www.codechef.com/COOK39/problems/PPNUM
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 1000000007

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


int numDigits(int x) {
    int count = 0;
    while (x > 0) {
        count++;
        x /= 10;
    }
    return count;
}

int maxValue(int digits) {
    int result = 0;
    FOR(i, digits) {
        result *= 10;
        result += 9;
    }
    return result;
}


long long int sum(long long int a, long long int b) {
    return (a + b) * (b - a + 1) / 2 % MOD;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int l = getInt();
        int r = getInt();

        int nl = numDigits(l);
        int nr = numDigits(r);

        long long int result = 0;
        if (nl == nr) {
            result = sum(l, r) * nl % MOD;
        } else {
            result = sum(l, maxValue(nl)) * nl % MOD;
            FORE(i, nl + 1, nr) {
                result += sum(maxValue(i - 1) + 1, maxValue(i)) * i % MOD;
                result %= MOD;
            }
            result += sum(maxValue(nr - 1) + 1, r) * nr % MOD;
            result %= MOD;
        }
        printf("%lld\n", result);
    }
}
