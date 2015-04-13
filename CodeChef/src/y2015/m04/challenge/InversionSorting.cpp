// Simple dynamic programming - go from the end of the string and calculate minimum possible inversions, if current character is at least i (for all i = 1 to m).
// http://www.codechef.com/APRIL15/problems/CARLOS
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


#define MAX_M 202
#define MAX_N 200001
#define INF (MAX_N * 2)

bool mm[MAX_M][MAX_M];
int input[MAX_N];
int m, n;
int result1[MAX_M];
int result2[MAX_M];


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


int min(int a, int b) {
    return a < b ? a : b;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        m = getInt();
        int k = getInt();
        n = getInt();
        FOR(i, m) FOR(j, m) mm[i][j] = false;
        FOR(i, k) {
            int x = getInt() - 1;
            int y = getInt() - 1;
            mm[x][y] = mm[y][x] = true;
        }
        FOR(i, n) input[i] = getInt() - 1;

        // calculate transitive inversions
        bool changed = true;
        while (changed) {
            changed = false;
            FOR(i, m) FOR(j, m)
                if (mm[i][j]) {
                    FOR(k, m)
                        if (mm[j][k] && !mm[i][k]) {
                            mm[i][k] = true;
                            changed = true;
                        }
                }
        }

        int *last = result1;
        int *current = result2;
        FOR(i, m) last[i] = 0;

        for(int i=n-1;i>=0;i--) {
            int c = input[i];
            current[m] = INF;

            for(int j=m - 1;j>=0;j--) {
                if (c == j) current[j] = last[j];
                else current[j] = min(min(current[j + 1], (mm[c][j] ? 1 : INF) + last[j]), INF);
            }
            int *temp = current;
            current = last;
            last = temp;
        }

        int minFound = INF;
        FOR(i, m) if (last[i] < minFound) minFound = last[i];

        printf("%d\n", minFound >= INF ? -1 : minFound);
    }
}
