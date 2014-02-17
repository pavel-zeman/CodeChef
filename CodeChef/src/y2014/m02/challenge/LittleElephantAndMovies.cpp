// Generate histogram of all numbers and start with the highest one and let h(i) = number of occurrences of the i-th highest number and H(i) = number of occurrences of all the number greater then i-th number.
// Then the number of orders of the first N numbers with excitingness = K can be defined as
// R(N, K) = R(N - 1, K) * h(N)! * C(H(i) + h(i) -1, H(i) - 1) + R(N - 1, K - 1) * h(N)! * (C(H(i) + h(i), H(i)) - C(H(i) + h(i) -1, H(i) - 1))
// http://www.codechef.com/FEB14/problems/LEMOVIE
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
#define MAX_N 210
#define MAX_P 210

int n, k;
int hist[MAX_P];
int fact[MAX_P];
int comb[MAX_P][MAX_P];
int r[MAX_N][MAX_N];

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

void generateStaticData(void) {
    long long int f = 1;
    FORE(i, 1, MAX_P) {
        f = f * i % MOD;
        fact[i] = (int)f;
    }

    FOR(i, MAX_P) {
        comb[i][0] = comb[i][i] = 1;
        FORE(j, 1, i) {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
        }
    }
}

int main(void) {
    generateStaticData();
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        k = getInt();
        FOR(i, MAX_P) hist[i] = 0;
        FOR(i, n) hist[getInt()]++;

        int totalNumbers = 0;
        int pos = 1;
        for(int i=MAX_P - 1;i >= 0;i--) {
            if (hist[i] > 0) {
                if (pos == 1) {
                    r[pos][1] = fact[hist[i]];
                } else {
                    for (int j=1;j<=k && j<=pos;j++) {
                        long long int add1 = 0;
                        long long int add2 = 0;
                        if (pos - 1 >= j) {
                            add1 = ((long long int)r[pos - 1][j]) * fact[hist[i]] % MOD * comb[hist[i] + totalNumbers - 1][totalNumbers - 1] % MOD;
                        }
                        if (j > 1) {
                            add2 = ((long long int)r[pos - 1][j - 1]) * fact[hist[i]] % MOD * (comb[hist[i] + totalNumbers][totalNumbers] - comb[hist[i] + totalNumbers - 1][totalNumbers - 1]) % MOD;
                        }
                        r[pos][j] = (add1 + add2) % MOD;
                    }
                }
                pos++;
                totalNumbers += hist[i];
            }
        }

        long long int total = 0;
        for(int i=1;i<=k && i <= pos - 1;i++) {
            total = (total + r[pos - 1][i]) % MOD;
        }
        if (total < 0) total += MOD;
        printf("%d\n", (int)total);
    }
}
