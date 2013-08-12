// Cumulative counts of each number - well, not the number itself, but its prime numbers
// http://www.codechef.com/AUG13/problems/CHMOD
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100002
#define MAX_A 25

int count[MAX_N][MAX_A];

int primes[MAX_A] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

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

int pow(int a, int b, int m) {
    long long int result = 1;
    long long int power = a;

    while (b > 0) {
        if ((b & 1) == 1) result = result * power % m;
        power = power * power % m;
        b >>= 1;
    }
    return result;
}

int main(void) {
    int n = getInt();
    FOR(i, MAX_A) count[0][i] = 0;
    FOR(i, n) {
        int x = getInt();
        if (i > 0) FOR(j, MAX_A) count[i][j] = count[i - 1][j];
        FOR(j, MAX_A) {
            while (x % primes[j] == 0) {
                count[i][j]++;
                x /= primes[j];
            }
        }
    }

    int t = getInt();
    FOR(i, t) {
        int l = getInt() - 1;
        int r = getInt() - 1;
        int m = getInt();

        int lc[MAX_A];
        FOR(j, MAX_A) lc[j] = count[r][j];
        if (l > 0) {
            FOR(j, MAX_A) lc[j] -= count[l - 1][j];
        }

        long long int result = 1;
        FOR(j, MAX_A) {
            if (lc[j] > 0) result = result * pow(primes[j], lc[j], m) % m;
        }
        printf("%d\n", (int)result % m);
    }
}
