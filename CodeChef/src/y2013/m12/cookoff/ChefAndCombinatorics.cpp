// Dynamic programming and combinations with repetitions
// http://www.codechef.com/COOK41/problems/GERALD05
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
#define MAX_S 110

long long int possibilities[MAX_S][MAX_S];

int f[MAX_S];
long long int inverse[MAX_S];
int s;


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


long long int power(long long int m, int power) {
    long long int current = m;
    long long int result = 1;
    while (power > 0) {
        if ((power & 1) != 0) result = result * current % MOD;
        current = current * current % MOD;
        power >>= 1;
    }
    return result;
}

long long int comb(int n, int k) {
    long long int result = 1;
    for(int i=n + k - 1;i>n - 1;i--) result = result * i % MOD;
    FORE(i, 1, k) result = result * inverse[i + 1] % MOD;
    return result;
}

long long int calc(int currentSum, int firstRang) {
    if (possibilities[currentSum][firstRang] == -1) {
        long long int result = 0;
        if (currentSum == s) {
            result = 1;
        } else if (firstRang > s - currentSum) {
            result = 0;
        } else {
            FOR(i, s + 1) {
                if (currentSum + i * firstRang > s) break;
                result += comb(f[firstRang], i) * calc(currentSum + i * firstRang, firstRang + 1) % MOD;
                result %= MOD;
            }
        }
        possibilities[currentSum][firstRang] = result;
    }
    return possibilities[currentSum][firstRang];
}

int main(void) {
    FORE(i, 1, MAX_S) inverse[i] = power(i, MOD - 2);
    int t = getInt();
    FOR(tt, t) {
        int a0 = getInt(), a1 = getInt(), a2 = getInt(), a3 = getInt();
        s = getInt();
        FORE(i, 1, s + 1) f[i] = a0 + a1 * i + a2 * i * i + a3 * i * i * i;
        FOR(i, MAX_S) FOR(j, MAX_S) possibilities[i][j] = -1;

        printf("%lld\n", calc(0, 1));
    }
}

