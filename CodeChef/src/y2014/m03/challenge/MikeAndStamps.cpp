// For all possible pair of offers check, if there collide. Then use brute force to find the maximum independent set.
// http://www.codechef.com/MARCH14/problems/MIKE3
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_M 22

using namespace std;
vector<int> offers[MAX_M];
bool collision[MAX_M][MAX_M];

int usedOffers[MAX_M];
int n, m;

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

bool collide(int v1, int v2) {
    int s1 = offers[v1].size();
    int s2 = offers[v2].size();
    int i1 = 0;
    int i2 = 0;

    while (i1 < s1 && i2 < s2) {
        if (offers[v1][i1] == offers[v2][i2]) return true;
        else if (offers[v1][i1] < offers[v2][i2]) {
            while (i1 < s1 && offers[v1][i1] < offers[v2][i2]) i1++;
        } else {
            while (i2 < s2 && offers[v1][i1] > offers[v2][i2]) i2++;
        }
    }

    return false;
}

void checkOffers(int firstToCheck, int used) {
    FORE(i, firstToCheck, m) {
        bool ok = true;
        FOR(j, used) {
            if (collision[usedOffers[j]][i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            usedOffers[used] = i;
            checkOffers(i + 1, used + 1);
        }
    }
}

int main(void) {
    n = getInt(), m = getInt();
    FOR(i, m) {
        int k = getInt();
        FOR(j, k) offers[i].push_back(getInt());
    }
    FOR(i, m) FORE(j, i + 1, m) collision[i][j] = collide(i, j);
    checkOffers(0, 0);
    int max = 1;
    while (usedOffers[max] != 0) max++;
    printf("%d\n", max);
}
