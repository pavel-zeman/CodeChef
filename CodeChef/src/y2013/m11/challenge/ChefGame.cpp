// Hackenbush game
// http://www.codechef.com/NOV13/problems/CHEFGM
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 50

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

int cmp(const void *p1, const void *p2) {
    return *((int *)p1) - *((int *)p2);
}

long long int calc(int *data, int n) {
    int parity = data[0] & 1;
    int i = 1;
    long long int result = 0;
    long long int power = 1;
    power <<= 47;

    while (i < n && (data[i] & 1) == parity) i++;

    if (i == n) {
        result = power * i;
    } else {
        result = power * (i - 1);
        i++;
        while (i < n) {
            power >>= 1;
            if ((data[i] & 1) == parity) result += power;
            i++;
        }
        result += power >> 1;
    }

    return parity == 0 ? result : -result;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int k = getInt();
        long long int result = 0;
        FOR(i, k) {
            int n = getInt();
            int numbers[MAX_N];
            FOR(j, n) numbers[j] = getInt();
            qsort(numbers, n, sizeof(numbers[0]), cmp);
            result += calc(numbers, n);
        }

        if (result > 0) puts("EVEN"); else
        if (result < 0) puts("ODD"); else
            puts("DON'T PLAY");
    }
}
