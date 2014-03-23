// Rabin-Karp algorithm string search with a binary search for maximum string length
// http://www.codechef.com/MARCH14/problems/SSTORY
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <utility>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_LENGTH 250010
#define HASH_SIZE (1 << 14)
#define MOD1 50000017
#define MOD2 40000003
#define AB_SIZE 26

using namespace std;

char s1[MAX_LENGTH], s2[MAX_LENGTH];
int l1, l2;
vector<pair<int,int> > hashTable[HASH_SIZE];

int find(int size) {
    FOR(i, HASH_SIZE) hashTable[i].clear();

    int max1 = 1;
    int max2 = 1;
    FORE(i, 1, size) {
        max1 = max1 * AB_SIZE % MOD1;
        max2 = max2 * AB_SIZE % MOD2;
    }
    int sum1 = 0;
    int sum2 = 0;
    FOR(i, size) {
        sum1 = (sum1 * AB_SIZE + s1[i]) % MOD1;
        sum2 = (sum2 * AB_SIZE + s1[i]) % MOD2;
    }
    int i = size;
    while (i <= l1) {
        hashTable[sum1 & (HASH_SIZE - 1)].push_back(make_pair(sum1, sum2));
        sum1 -= s1[i - size] * max1 % MOD1;
        sum2 -= s1[i - size] * max2 % MOD2;
        if (sum1 < 0) sum1 += MOD1;
        if (sum2 < 0) sum2 += MOD2;
        sum1 = (sum1 * AB_SIZE + s1[i]) % MOD1;
        sum2 = (sum2 * AB_SIZE + s1[i]) % MOD2;
        i++;
    }

    sum1 = 0;
    sum2 = 0;
    FOR(i, size) {
        sum1 = (sum1 * AB_SIZE + s2[i]) % MOD1;
        sum2 = (sum2 * AB_SIZE + s2[i]) % MOD2;
    }
    i = size;
    while (i <= l2) {
        int h = sum1 & (HASH_SIZE - 1);
        for (vector<pair<int, int> >::iterator it = hashTable[h].begin(); it != hashTable[h].end();it++) {
            if (it->first == sum1 && it->second == sum2) return i - size;
        }
        sum1 -= s2[i - size] * max1 % MOD1;
        sum2 -= s2[i - size] * max2 % MOD2;
        if (sum1 < 0) sum1 += MOD1;
        if (sum2 < 0) sum2 += MOD2;
        sum1 = (sum1 * AB_SIZE + s2[i]) % MOD1;
        sum2 = (sum2 * AB_SIZE + s2[i]) % MOD2;
        i++;
    }
    return -1;
}

int main(void) {
    scanf("%s%s", s1, s2);
    l1 = strlen(s1);
    l2 = strlen(s2);
    FOR(i, l1) s1[i] -= 'a';
    FOR(i, l2) s2[i] -= 'a';

    int l = 1, r = l2;

    while (l <= r) {
        int m = (l + r) >> 1;
        int pos = find(m);
        if (pos >= 0) l = m + 1; else r = m - 1;
    }
    int pos = r > 0 ? find(r) : 0;
    if (r > 0) {
        FOR(i, l2) s2[i] += 'a';
        s2[pos + r] = 0;
        printf("%s\n", s2 + pos);
    }
    printf("%d\n", r);
}
