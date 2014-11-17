// This version works only for N <= 5 and for prime modulos. It is based on the fact, that V(N, R + 1) = V(N, R) * (N - R) ^ (N - R) / (R + 1) ^ (R + 1).
// http://www.codechef.com/NOV14/problems/POWERMUL
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

#define MAX_N 100010

using namespace std;

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

long long int power(int a, int b) {
    long long int result = 1;
    long long int temp = a;
    while (b > 0) {
        if ((b & 1) == 1) result *= temp;
        temp *= temp;
        b >>= 1;
    }
    return result;
}

long long int power(int a, int b, long long int mod) {
    long long int result = 1;
    long long int temp = a;
    while (b > 0) {
        if ((b & 1) == 1) result = result * temp % mod;
        temp = temp * temp % mod;
        b >>= 1;
    }
    return result;
}


long long int f(int n) {
    long long int result = 1;
    FOR(i, n) result *= power(i + 1, i + 1);
    return result;
}

long long int inv(long long int value, long long int mod) {
    return power(value, mod - 2, mod);
}

long long int fData[MAX_N];


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        int q = getInt();

        if (n > 5) {
            // assume prime
            fData[0] = 1;
            fData[1] = power(n, n, m);
            FORE(i, 2, n) {
                long long int temp = power(i, i, m);
                fData[i] = fData[i - 1] * power(n - i + 1, n - i + 1, m) % m * inv(temp, m) % m;
            }
        }

        FOR(qq, q) {
            int r = getInt();
            if (n <= 5) printf("%lld\n", f(n) / f(r) / f(n - r) % m);
            else printf("%lld\n", fData[r]); // assume prime
        }
    }
}
