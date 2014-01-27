// The solution for (L, H) is the max of ((L + 1, H), (L, H - 1) and a rectangle spanning all the columns, i.e. of width H - L + 1 - the size of such rectangle can be precalculated)
// http://www.codechef.com/JAN14/problems/METEORAK
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <algorithm>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1002

using namespace std;

int n, m, k;


bool dangerous[MAX_N][MAX_N];
int maxLeft[MAX_N][MAX_N];
int result[MAX_N][MAX_N];

struct Length {
    int length;
    int start;
};

struct Length2 {
    int length;
    int height;
};

vector<Length2> globalLengths[MAX_N];


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


void calcMaxLeft() {
    FOR(i, m) {
        int curr = 0;
        FOR(j, n) {
            if (dangerous[i][j]) curr = 0; else curr++;
            maxLeft[i][j] = curr;
        }
    }

}

int max(int a, int b) {
    return a > b ? a : b;
}

void calcMaxLengths() {
    // for each column
    FOR(i, n) {
        int maxLeftLocal[MAX_N];
        FOR(j, i + 2) maxLeftLocal[j] = 0;
        vector<Length> lengths;
        int lastLength = 0;
        FOR(j, m) {
            int currLength = maxLeft[j][i];
            if (currLength < lastLength) {
                int lastStart = -1;
                while (!lengths.empty() && lengths.back().length > currLength) {
                    int start = lengths[lengths.size() - 1].start;
                    int length = lengths[lengths.size() - 1].length;
                    lastStart = start;
                    maxLeftLocal[length] = max(maxLeftLocal[length], j - start);
                    lengths.pop_back();
                }
                if ((lengths.empty() && currLength > 0) || lengths.back().length < currLength) {
                    Length l;
                    l.start = lastStart;
                    l.length = currLength;
                    lengths.push_back(l);
                }
            } else if (currLength > lastLength) {
                Length l;
                l.start = j;
                l.length = currLength;
                lengths.push_back(l);
            } // do nothing, if they are equal
            lastLength = currLength;
        }
        FOR(j, (int)lengths.size()) {
            int start = lengths[j].start;
            int length = lengths[j].length;
            maxLeftLocal[length] = max(maxLeftLocal[length], m - start);
        }
        int currHeight = 0;
        for(int j=i + 1;j>0;j--) {
            if (maxLeftLocal[j] > 0) {
                if (maxLeftLocal[j] > currHeight) {
                    Length2 l2;
                    l2.height = maxLeftLocal[j];
                    l2.length = j;
                    globalLengths[i].push_back(l2);
                    currHeight = maxLeftLocal[j];
                }
            }
        }
        reverse(globalLengths[i].begin(), globalLengths[i].end());
    }
}

int findMax(int column, int length) {
    if (globalLengths[column].empty() || globalLengths[column].back().length < length) return 0;
    FOR(i, (int)globalLengths[column].size()) {
        if (globalLengths[column][i].length >= length) return globalLengths[column][i].height * length;
    }
    return -1;
}


int calc(int l, int h) {
    if (result[l][h] == -1) {
        int localResult = -1;
        if (l == h) {
            localResult = globalLengths[l].empty() ? 0 : globalLengths[l][0].height;
        } else {
            localResult = max(calc(l + 1, h), calc(l, h - 1));
            localResult = max(localResult, findMax(h, h - l + 1));
        }
        result[l][h] = localResult;
    }
    return result[l][h];
}

// fast print
void print(int a) {
    if (a == 0) {
        putc_unlocked('0', stdout);
    } else {
        char result[20];
        int resSize = 0;
        while (a > 0) {
            result[resSize++] = '0' + a % 10;
            a /= 10;
        }
        while (--resSize >= 0) putc_unlocked(result[resSize], stdout);
    }
    putc_unlocked('\n', stdout);
}

int main(void) {
    n = getInt();
    m = getInt();
    FOR(i, m) FOR(j, n) dangerous[i][j] = false;

    k = getInt();
    FOR(i, k) {
        int x = getInt() - 1;
        int y = getInt() - 1;
        dangerous[y][x] = true;
    }
    calcMaxLeft();
    calcMaxLengths();
    FOR(i, n) FORE(j, i, n) result[i][j] = -1;

    int q = getInt();
    FOR(i, q) {
        int l = getInt() - 1;
        int h = getInt() - 1;
        print(calc(l, h));
    }
}
