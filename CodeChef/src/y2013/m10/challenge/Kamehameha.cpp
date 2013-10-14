// Maximum bipartite matching
// http://www.codechef.com/OCT13/problems/KMHAMHA
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <map>
#include <list>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1010

using namespace std;

bool visitedR[MAX_N];
list<int> left[MAX_N];
map<int, int> leftMap, rightMap;
int totalL, totalR;
int previous[MAX_N];

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

int getValue(map<int, int> &m, int value) {
    map<int, int>::iterator it = m.find(value);
    if (it == m.end()) {
        int t = m.size();
        return m[value] = t;
    } else return it->second;
}

void addItem(int leftInput, int rightInput) {
    left[getValue(leftMap, leftInput)].push_back(getValue(rightMap, rightInput));
}

bool check(int v, bool leftItem) {
    if (leftItem) {
        for(list<int>::iterator it = left[v].begin(); it != left[v].end(); it++) {
            if (previous[*it] != v && check(*it, false)) {
                previous[*it] = v;
                return true;
            }
        }
    } else {
        if (visitedR[v]) return false;
        visitedR[v] = true;
        return previous[v] == -1 || check(previous[v], true);
    }
    return false;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        leftMap.clear();
        rightMap.clear();
        FOR(i, MAX_N) left[i].clear();

        FOR(i, n) {
            int x = getInt();
            int y = getInt();
            addItem(x, y);
        }
        totalL = leftMap.size();
        totalR = rightMap.size();

        int total = 0;
        FOR(i, totalR) previous[i] = -1;

        FOR(i, totalL) {
            FOR(j, totalR) visitedR[j] = false;
            if (check(i, true)) total++;
        }
        printf("%d\n", total);
    }
}
