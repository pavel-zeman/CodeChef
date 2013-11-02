//
// http://www.codechef.com/COOK39/problems/PPXOR
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_V 1000000001


#define MAX_N 100100
int n;
int a[MAX_N];
unsigned int ones[MAX_N];
int oneCount;

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


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        FOR(i, n) a[i] = getInt();
        /*long long int sum1 = 0;
        FOR(i, n) FORE(j, i, n) {
            int x = 0;
            FORE(k, i, j + 1) x ^= a[k];
            sum1 += x;
        }*/

        long long int sum2 = 0;
        int bit = 1;
        while (bit < MAX_V) {
            oneCount = 0;
            FOR(i, n) {
                if ((a[i] & bit) != 0) ones[oneCount++] = i;
            }
            if (oneCount > 0) {
                unsigned long long int temp[MAX_N];
                int i = oneCount - 1;
                unsigned long long int subTotal = 0;
                while (i >= 0) {
                    unsigned int end = i < oneCount - 1 ? ones[i + 1] : n;
                    temp[i] = end - ones[i];
                    if (i < oneCount - 2) temp[i] += temp[i + 2];
                    subTotal += temp[i];

                    unsigned int begin = i > 0 ? ones[i - 1] + 1 : 0;
                    subTotal += (ones[i] - begin) * temp[i];
                    i--;
                }
                //printf("Bit %d Total %d\n", bit, subTotal);
                sum2 += subTotal * bit;
            }
            bit <<= 1;
        }

        //printf("%lld %lld\n", sum1, sum2);
        //if (sum1 != sum2) printf("ERROR\n");
        printf("%llu\n", sum2);
    }
}
