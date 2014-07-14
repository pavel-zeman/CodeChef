// For each fight create union of both sets of dishes. To create union, the disjoint set data structure is used.
// http://www.codechef.com/JULY14/problems/DISHOWN
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 10010


int prev[MAX_N];
int s[MAX_N];
int depth[MAX_N];
int chef[MAX_N];


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

int root(int a) {
    while (prev[a] != a) a = prev[a];
    return a;
}

void add(int x, int y) {
    int r = x;
    if (depth[x] > depth[y]) {
        prev[y] = x;
    } else if (depth[y] > depth[x]) {
        prev[x] = y;
        r = y;
    } else {
        prev[y] = x;
        depth[x]++;
    }

    if (s[x] > s[y]) {
        chef[r] = chef[x];
        s[r] = s[x];
    } else {
        chef[r] = chef[y];
        s[r] = s[y];
    }
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        FOR(i, n) prev[i] = i, chef[i] = i, depth[i] = 1, s[i] = getInt();
        int q = getInt();
        FOR(i, q) {
            int type = getInt();
            int x, y;
            switch (type) {
                case 0:
                    // fight
                    x = root(getInt() - 1);
                    y = root(getInt() - 1);
                    if (x == y)
                        printf("Invalid query!\n");
                    else if (s[x] != s[y])
                        add(x, y);
                    break;

                case 1:
                    // query
                    printf("%d\n", chef[root(getInt() - 1)] + 1);
                    break;
            }
        }
    }
}
