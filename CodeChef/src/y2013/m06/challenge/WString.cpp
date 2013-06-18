#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXN 10010

char string[MAXN];
int max1[MAXN], max2[MAXN];
int hashPos[MAXN];
int maxHash[MAXN];

int calcMax(int p1, int p2) {
    int freq[26];
    int max = 0;
    memset(freq, 0, sizeof(freq));
    FORE(i, p1 + 1, p2) if (++freq[string[i] - 'a'] > max) max++;
    return max;
}

int main(void) {
    gets(string);
    int t = atoi(string);
    FOR(tt, t) {
        gets(string);

        int length = strlen(string);
        int max = 0;
        int freq[26];
        memset(freq, 0, sizeof(freq));
        int hashes = 0;
        FOR(i, length) {
            if (string[i] != '#') {
                if (++freq[string[i] - 'a'] > max) max++;
            } else hashPos[hashes++] = i;
            max1[i] = max;
        }

        max = 0;
        memset(freq, 0, sizeof(freq));
        for(int i=length - 1;i>=0;i--) {
            if (string[i] != '#') {
                if (++freq[string[i] - 'a'] > max) max++;
            }
            max2[i] = max;
        }

        FOR(i, hashes - 1) maxHash[i] = calcMax(hashPos[i], hashPos[i + 1]);

        max = 0;
        FOR(i, hashes - 2) {
            int lm = max1[hashPos[i]] + maxHash[i] + maxHash[i + 1] + max2[hashPos[i + 2]];
            if (lm > max && max1[hashPos[i]] > 0 && maxHash[i] > 0 && maxHash[i + 1] > 0 && max2[hashPos[i + 2]] > 0) max = lm;
        }
        printf("%d\n", max > 0 ? max + 3 : 0);
    }
}
