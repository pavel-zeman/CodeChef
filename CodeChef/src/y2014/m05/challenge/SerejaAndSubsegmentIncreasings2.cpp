// Just an unsuccessful attempt
// http://www.codechef.com/MAY14/problems/SEINC
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <map>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010
#define MAX_D 200
#define IMPOSSIBLE 1000000000

int a[MAX_N];
int cc[MAX_N];
int b[MAX_N];

int remain[MAX_N];
int n;

//int res[MAX_N][MAX_D];
map<pair<int, int>, int> res;

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

int solve(int pos, int value) {
    map<pair<int, int>, int>::iterator resIt = res.find(make_pair(pos, value));

    //if (res[pos][value] != -1) return res[pos][value];
    if (resIt != res.end()) return resIt->second;

    int result = IMPOSSIBLE;
    if (pos == n) {
        result = value == 0 ? 0 : IMPOSSIBLE;
    } else {
        if (4 - cc[pos] + value <= remain[pos + 1]) result = solve(pos + 1, 4 - cc[pos] + value);
        if (value >= cc[pos]) {
            int temp = solve(pos + 1, value - cc[pos]) + cc[pos];
            if (temp < result) result = temp;
        }
    }
    //printf("Result: %d %d = %d\n", pos, value, result);
    res[make_pair(pos, value)] = result;
    //return res[pos][value] = result;
    return result;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) a[i] = getInt();
        FOR(i, n) a[i] = (a[i] - getInt() + 4) & 3;

        a[n] = 0;
        b[0] = a[0];
        n++;
        FORE(i, 1, n) b[i] = (a[i] - a[i - 1] + 4) & 3;
        int n2 = 0;
        FOR(i, n) if (b[i] != 0) cc[n2++] = b[i];
        n = n2;
        remain[n] = 0;
        for(int i=n-1;i>=0;i--) remain[i] = remain[i + 1] + cc[i];


        res.clear();
        //printf("Solving: ");
        //FOR(i, n) printf("%d ", cc[i]);
        //printf("\n");

        printf("%d\n", solve(0, 0));
    }
}

