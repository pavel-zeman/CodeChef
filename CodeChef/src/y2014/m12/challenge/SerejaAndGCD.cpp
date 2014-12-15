// Let F(D, M) be the solution for D. Then F(D, M) = F(1, trunc(M/D)) and F(1, M) = N^M - sum(i=2..M, F(i, M)) = N^M - sum(i=2..M, F(1, trunc(M/i))). So we just have to recursively calculate values of F(1, i) (and store them in result array).
// http://www.codechef.com/DEC14/problems/SEAGCD
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

#define MAX_M 10000010
#define MOD 1000000007
#define INVALID -1

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


int result[MAX_M];
int n, m, l, r;

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

int power(int v) {
    long long int temp = v;
    int power = n;
    long long int result = 1;
    while (power > 0) {
        if ((power & 1) == 1) result = result * temp % MOD;
        temp = temp * temp % MOD;
        power >>= 1;
    }
    return result;
}

int solve(int v) {
    if (result[v] == INVALID) {
        long long int total = power(v);
        total -= (v - v / 2);
        int i = 2;
        while (i * i < v) {
            total -= solve(v / i);
            int s = v / (i + 1);
            if (s < i) s = i;
            total -= (v / i - s) * (long long int)solve(i);
            i++;
        }
        if (i * i == v) total -= solve(v / i);
        result[v] = (total % MOD + MOD) % MOD;
    }
    return result[v];
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();
        l = getInt();
        r = getInt();

        FOR(i, m + 1) result[i] = INVALID;
        result[1] = 1;
        long long int total = 0;
        r++;
        FORE(i, l, r) total += solve(m / i);
        printf("%lld\n", total % MOD);
    }
}
