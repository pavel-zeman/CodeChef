// O(N) algorithm, which incrementally calculates the total value to add to L[i] and to multiply with L[i] (multiplication of big numbers is solved using the Russian peasant algorithm)
// http://www.codechef.com/JAN14/problems/MTRICK
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1010

int n;
unsigned long long int l[MAX_N];
unsigned long long int a, b, c;

char cc = 0;
unsigned long long int getInt() {
    unsigned long long int r = 0;
    while (!(cc >= '0' && cc <= '9')) cc = getc_unlocked(stdin);
    while (cc >= '0' && cc <= '9') {
        r = r * 10 + (cc - '0');
        cc = getc_unlocked(stdin);
    }
    return r;
}

char getChar() {
    while (!(cc >= 'A' && cc <= 'Z')) cc = getc_unlocked(stdin);
    char result = cc;
    cc = getc_unlocked(stdin);
    return result;
}

// Russian peasant multiplication
unsigned long long int mulmod(unsigned long long int a, unsigned long long int b) {
    if (c <= 2000000000) return a * b % c;

    unsigned long long int res = 0;
    while (a > 0) {
        if (a & 1) {
            res += b;
            if (res >= c) res -= c;
        }
        a >>= 1;
        b <<= 1;
        if (b >= c) b -= c;
    }
    return res;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) l[i] = getInt();
        a = getInt();
        b = getInt();
        c = getInt();
        a %= c;
        b %= c;

        unsigned long long int mul = 1;
        unsigned long long int add = 0;

        int lastIndex = n - 1;
        int indexAdd = 1;
        int prevIndex = -1;
        FOR(i, n) {
            char ch = getChar();
            prevIndex += indexAdd;
            switch (ch) {
                case 'R': {
                    indexAdd *= -1;
                    int temp = lastIndex;
                    lastIndex = prevIndex;
                    prevIndex = temp;
                    break;
                }
                case 'A':
                    add = (add + a) % c;
                    break;

                case 'M':
                    mul = mulmod(mul, b);
                    add = mulmod(add, b);
                    break;
            }
            printf("%llu ", (mulmod(mul, l[prevIndex] % c) + add) % c);
        }
        printf("\n");
    }
}
