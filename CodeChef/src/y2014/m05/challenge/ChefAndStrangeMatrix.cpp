// Maintain a map of increments for each row. Then evaluate each row one by one.
// http://www.codechef.com/MAY14/problems/CHEFBM
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

#define MAX_N 100002

map<int, int> increments[MAX_N];
pair<int, int> row[MAX_N];

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

int cmp(const void *p1, const void *p2) {
    pair<int, int> *x1 =  (pair<int, int> *)p1;
    pair<int, int> *x2 =  (pair<int, int> *)p2;
    return x1->first - x2->first;
}

int main(void) {
    int n = getInt(), m = getInt(), p = getInt();
    FOR(i, p) {
        int a = getInt() - 1;
        int b = getInt() - 1;
        map<int, int>::iterator it = increments[a].find(b);
        if (it == increments[a].end()) increments[a][b] = b + 2; else increments[a][b] = it->second + 1;
    }
    FOR(i, n) {
        int s = 0;
        for (map<int, int>::iterator it = increments[i].begin(); it != increments[i].end(); it++) row[s++] = *it;
        qsort(row, s, sizeof(row[0]), cmp);
        int ans = m - 1;
        if (s > 0) {
            bool ok = true;
            FOR(j, s) {
                if (row[j].first == m - 1 || // last element
                    row[j].second <= row[j].first + 2 || // increased at most by 1
                    (j < s - 1 && row[j].first == row[j + 1].first - 1 && row[j].second <= row[j + 1].second) // less then or equal to the next element
                ) {
                    // OK
                } else {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                int last = row[s - 1].first == m - 1 ? row[s - 1].second : m;
                int first = row[0].first == 0 ? row[0].second : 1;
                ans = last - first;
            } else ans = -1;
        }
        printf("%d\n", ans);
    }
}

