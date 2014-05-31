// Use DP to count subsets having at least M colors. For each balloon, calculate its contribution to the total sum as its price times number of subsets having at least M-1 colors.
// http://www.codechef.com/MAY14/problems/LEBALONS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 42
#define EMPTY -1

int count[MAX_N];
long long int possibilities[MAX_N][MAX_N];
vector<int> price[MAX_N];
int totalColors;

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

long long int numPossibilities(int startPosition, int min) {
    if (possibilities[startPosition][min] != EMPTY) return possibilities[startPosition][min];

    long long int result = 0;
    if (startPosition == totalColors) {
        result = min == 0 ? 1 : 0;
    } else if (min == 0) {
        result = (1L << count[startPosition]) * numPossibilities(startPosition + 1, min);
    } else {
        result = ((1L << count[startPosition]) - 1) * numPossibilities(startPosition + 1, min - 1) + numPossibilities(startPosition + 1, min);
    }
    return possibilities[startPosition][min] = result;
}

long long int calcPossibilities(int colors, int min) {
    FOR(i, MAX_N) FOR(j, MAX_N) possibilities[i][j] = EMPTY;
    totalColors = colors;
    return numPossibilities(0, min < 0 ? 0 : min);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        FOR(i, MAX_N) count[i] = 0, price[i].clear();
        FOR(i, n) {
            int c = getInt();
            int p = getInt();
            price[c].push_back(p);
        }
        int src = 0;
        int colors = 0;
        while (src < MAX_N) {
            while (src < MAX_N && price[src].empty()) src++;
            if (src < MAX_N) price[colors++] = price[src++];
        }

        FOR(i, colors) count[i] = price[i].size();
        long long int totalPossibilities = calcPossibilities(colors, m);

        double totalSum = 0;
        FOR(i, colors) {
            int j = 0;
            FOR(k, colors) if (k != i) count[j++] = price[k].size();
            long long int temp = calcPossibilities(colors - 1, m - 1) * (1L << (price[i].size() - 1));
            double localSum = 0;
            FOR(k, (int)price[i].size()) localSum += price[i][k];
            totalSum += localSum * temp;
        }

        printf("%.10lf\n", totalSum / totalPossibilities);
    }
}

