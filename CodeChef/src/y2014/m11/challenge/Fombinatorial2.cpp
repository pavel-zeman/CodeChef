// Works for all inputs. It is based on the fact, that V(N, R + 1) = V(N, R) * (N - R) ^ (N - R) / (R + 1) ^ (R + 1). Stores current powers of all prime factors in an array and lazily calculates required result.
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
#define MAX_PRIMES 10000
#define GROUP_SIZE 64
#define GROUPS ((MAX_PRIMES / GROUP_SIZE) + 1)

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

long long int power(int a, long long int b, long long int mod) {
    long long int result = 1;
    long long int temp = a;
    while (b > 0) {
        if ((b & 1) == 1) result = result * temp % mod;
        temp = temp * temp % mod;
        b >>= 1;
    }
    return result;
}

bool prime[MAX_N];
int primeCount = 0;
int primes[MAX_PRIMES];
int primePosition[MAX_N];
vector<pair<int, int> > primeList[MAX_N];

int main(void) {
    // generate all primes lower than 10^5
    FOR(i, MAX_N) prime[i] = true;
    FORE(i, 2, MAX_N) {
        if (prime[i]) for(int next = i + i; next < MAX_N; next += i) prime[next] = false;
    }
    int primeCount = 0;
    FORE(i, 2, MAX_N) if (prime[i]) {
        primes[primeCount] = i;
        primePosition[i] = primeCount++;
    } else primePosition[i] = primeCount;

    // generate list of primes for each number
    FORE(i, 2, MAX_N) {
        int j = 0;
        int temp = i;
        while (primes[j] * primes[j] <= temp) {
            int count = 0;
            while (temp % primes[j] == 0) {
                count++;
                temp /= primes[j];
            }
            if (count > 0) primeList[i].push_back(make_pair(j, count * i));
            j++;
        }
        if (temp > 1) primeList[i].push_back(make_pair(primePosition[temp], 1 * i));
    }



    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        int q = getInt();
        bool used[MAX_N];
        bool dirty[MAX_PRIMES];
        bool dirtyGroup[GROUPS];
        int result[MAX_N];
        int primeResult[MAX_PRIMES];
        int primeGroupResult[GROUPS];
        long long int currentPrimeCount[MAX_PRIMES];
        vector<int> input;
        int usedSize = (n >> 1) + 2;
        FOR(i, usedSize) used[i] = false;
        int maxPrimes = primePosition[n] + 1;
        FOR(i, maxPrimes) {
            currentPrimeCount[i] = 0;
            dirty[i] = false;
        }
        int maxGroups = maxPrimes / GROUP_SIZE + 1;
        FOR(i, maxGroups) {
            dirtyGroup[i] = false;
            primeGroupResult[i] = 1;
        }

        FOR(qq, q) {
            int r = getInt();
            input.push_back(r);
            if (r > n - r) r = n - r;
            used[r] = true;
        }

        for(int i=1;i <= n - i;i++) {
            int p = n - i + 1;
            // update current prime powers
            if (p > 1) for (vector<pair<int, int> >::iterator it = primeList[p].begin(); it != primeList[p].end(); it++) currentPrimeCount[it->first] += it->second, dirty[it->first] = true, dirtyGroup[it->first / GROUP_SIZE] = true;
            if (i > 1) for (vector<pair<int, int> >::iterator it = primeList[i].begin(); it != primeList[i].end(); it++) currentPrimeCount[it->first] -= it->second, dirty[it->first] = true, dirtyGroup[it->first / GROUP_SIZE] = true;
            if (used[i]) {
                // we need to calculate this value
                long long int local = 1;
                FOR(j, maxGroups) {
                    // try a group first - if it is dirty, calculate its value
                    if (dirtyGroup[j]) {
                        long long int local2 = 1;
                        int end = (j + 1) * GROUP_SIZE;
                        FORE(k, j * GROUP_SIZE, end) if (currentPrimeCount[k] > 0) {
                            if (dirty[k]) {
                                primeResult[k] = power(primes[k], currentPrimeCount[k], m);
                                dirty[k] = false;
                            }
                            local2 = local2 * primeResult[k] % m;
                        }
                        primeGroupResult[j] = local2;
                        dirtyGroup[j] = false;
                    }
                    local = local * primeGroupResult[j] % m;
                }
                result[i] = local;
            }
        }

        for(vector<int>::iterator it = input.begin(); it != input.end(); it++) {
            int r = *it;
            printf("%d\n", result[r <= n - r ? r : n - r]);
        }
    }
}
