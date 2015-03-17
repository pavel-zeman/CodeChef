// Implementation based on the Caley-Hamilton theorem as described at http://discuss.codechef.com/questions/49614/linear-recurrence-using-cayley-hamilton-theorem (still too slow for the second subtask).
// http://www.codechef.com/MARCH15/problems/RNG
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

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_K 3002
#define MOD 104857601

int a[MAX_K];
int cc[MAX_K];

int mPowers[MAX_K][MAX_K];

int mPower[MAX_K];
int mPower2[MAX_K];


int firstRow[MAX_K][MAX_K];

int finalPowers[MAX_K];

int k;
long long int n;

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

long long int getLongLongInt() {
    long long int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}


int main(void) {
    k = getInt();
    if (k > MAX_K) return 1;
    n = getLongLongInt();
    FOR(i, k) a[i] = getInt();
    FOR(i, k) cc[i] = getInt();
    if (n <= k) {
        printf("%d\n", a[n - 1]);
        return 0;
    }
    FOR(i, k) mPowers[0][i] = cc[i];
    FORE(i, 1, k) {
        FOR(j, k - 1) mPowers[i][j] = mPowers[i - 1][j + 1];
        mPowers[i][k - 1] = 0;
        FOR(j, k) mPowers[i][j] = (mPowers[i][j] + ((long long int)mPowers[i - 1][0]) * mPowers[0][j]) % MOD;
        //FOR(j, k) printf("%d ", mPowers[i][j]);
        //printf("\n");
    }
    //printf("aa\n");
    long long int target = n - k;
    long long int power = 0;
    long long int temp = target;
    int index = 0;
    while (temp > 0) {
        index++;
        temp >>= 1;
    }
    index--;
    FOR(i, k) mPower[i] = 0;
    mPower[k - 1] = 1;
    while (power < target) {
        //printf("%lld %lld %d\n", power, target, index);
        if (((((long long int)1) << index) & target) != 0) {
            power++;
            FOR(j, k - 1) mPower2[j] = mPower[j + 1];
            mPower2[k - 1] = 0;
            FOR(j, k) mPower2[j] = (mPower2[j] + ((long long int)mPower[0]) * mPowers[0][j]) % MOD;
            FOR(j, k) mPower[j] = mPower2[j];
            //printf("Adding 1\n");
        }
        if (power < target) {
            //printf("Multiplying 2\n");
            FOR(i, k) {
                long long int total = 0;
                FORE(j, i, k) {
                    //total = (total + ((long long int)mPower[j]) * mPower[k - 1 - (j - i)]) % MOD;
                    total += ((long long int)mPower[j]) * mPower[k - 1 - (j - i)];
                    if ((j & 63) == 0) total %= MOD;
                }
                mPower2[i] = total % MOD;
            }
            // higher powers
            FOR(i, k - 1) {
                long long int total = 0;
                FORE(j, 0, k - 1 - i) {
                    //total = (total + ((long long int)mPower[j] * mPower[k - 1 - (k + i - (k - 1 - j))])) % MOD;
                    total += ((long long int)mPower[j]) * mPower[k - 1 - (k + i - (k - 1 - j))];
                    if ((j & 63) == 0) total %= MOD;
                }
                total %= MOD;
                FOR(j, k) mPower2[j] = (mPower2[j] + ((long long int)total * mPowers[i][j])) % MOD;
            }
            FOR(j, k) mPower[j] = mPower2[j];
            power <<= 1;
        }
        index--;
    }
    //printf("bb\n");

    FOR(i, k) firstRow[0][i] = 0;
    firstRow[0][0] = 1;
    FORE(i, 1, k) {
        FOR(j, k - 1) {
            firstRow[i][j] = (((long long int)firstRow[i - 1][0]) * cc[j] + firstRow[i - 1][j + 1]) % MOD;
        }
        firstRow[i][k - 1] = ((long long int)firstRow[i - 1][0]) * cc[k - 1] % MOD;
        //FOR(j, k) printf("%d ", firstRow[i][j]);
        //printf("\n");
    }

    FOR(i, k) finalPowers[i] = 0;
    FOR(i, k) {
        long long int m = mPower[i];
        //printf("%d ", mPower[i]);
        FOR(j, k)
            finalPowers[j] = (finalPowers[j] + m * firstRow[k - 1 - i][j]) % MOD;
    }
    //FOR(i, k) printf("%d ", finalPowers[i]);
    int result = 0;
    FOR(i, k) result = (result + ((long long int)finalPowers[i]) * a[k - 1 - i]) % MOD;

    printf("%d\n", result);
}
