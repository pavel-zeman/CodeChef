// Unfortunately, this does not work
// http://www.codechef.com/AUG14/problems/TSHIRTS
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


#define MAX_N 12
#define MAX_TSHIRTS 101

#define MOD 1000000007

bool hasShirt[MAX_N][MAX_TSHIRTS];
long long int numArrs[MAX_N][MAX_N][MAX_TSHIRTS];
long long int totalCombinations[MAX_N];
int totalShirts[MAX_N];

/*long long int getArrs1(int start, int shirt) {
    long long int result = numArrs1[start][shirt];
    if (result < 0) {
        if (hasShirt[start][shirt]) {
            result = (totalCombinations[start + 1] + (totalShirts[start] - 1) * getArrs1(start + 1, shirt)) % MOD;
        } else {
            result = totalShirts[start] * getArrs1(start + 1, shirt) % MOD;
        }
        numArrs1[start][shirt] = result;
    }
    return result;
}

long long int getArrs2(int start, int shirt) {
    long long int result = numArrs2[start][shirt];
    if (result < 0) {
        if (hasShirt[start][shirt]) {
            result = (getArrs1(start + 1, shirt) + (totalShirts[start] - 1) * getArrs2(start + 1, shirt)) % MOD;
        } else {
            result = totalShirts[start] * getArrs2(start + 1, shirt) % MOD;
        }
        numArrs2[start][shirt] = result;
    }
    return result;
}*/

long long int getArrs(int start, int count, int shirt) {
    long long int result = numArrs[start][count][shirt];
    if (result < 0) {
        if (hasShirt[start][shirt]) {
            result = (getArrs(start + 1, count - 1, shirt) + (totalShirts[start] - 1) * getArrs(start + 1, count, shirt)) % MOD;
        } else {
            result = totalShirts[start] * getArrs(start + 1, count, shirt) % MOD;
        }
        numArrs[start][count][shirt] = result;
        //printf("%d %d %d %lld\n", start, count, shirt, result);
    }
    return result;
}


int main(void) {
    char buffer[1000];
    gets(buffer);
    int t = atoi(buffer);
    FOR(tt, t) {
        gets(buffer);
        int n = atoi(buffer);
        FOR(i, n) FOR(j, MAX_TSHIRTS) hasShirt[i][j] = false;

        // read input data
        FOR(i, n) {
            gets(buffer);
            char *start = buffer;
            bool end = false;
            totalShirts[i] = 0;
            //printf("#%s#", buffer);
            while (!end) {
                char *temp = start;
                while (*temp >= '0' && *temp <= '9') temp++;
                end = *temp == 0;
                *temp = 0;
                //printf("%d %d, ", i, atoi(start));
                hasShirt[i][atoi(start) - 1] = true;
                start = temp + 1;
                totalShirts[i]++;
            }
        }
        totalCombinations[n] = 1;
        for(int i = n - 1; i >= 0; i--) totalCombinations[i] = totalCombinations[i + 1] * totalShirts[i] % MOD;
        FOR(i, n + 1) FOR(j, n) FOR(k, MAX_TSHIRTS) numArrs[i][j][k] = -1;
        FOR(i, n + 1) FOR(j, MAX_TSHIRTS) numArrs[i][0][j] = totalCombinations[i];
        FORE(i, 1, n) FOR(j, MAX_TSHIRTS) numArrs[n][i][j] = 0;

        long long int total = 0;
        FORE(i, 2, n) FOR(j, MAX_TSHIRTS) {
            total = (total + getArrs(0, i, j)) % MOD;
        }
        printf("%lld %lld ", totalCombinations[0], total);
        total = totalCombinations[0] - total;
        if (total < 0) total += MOD;
        printf("%lld\n", total);
    }
}
