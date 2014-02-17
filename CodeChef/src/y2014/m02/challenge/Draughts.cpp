// Search for connected components using DFS and marking rooms on path between rooms with open windows
// http://www.codechef.com/FEB14/problems/DRGHTS
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

#define MAX_N 50002

using namespace std;

bool window[MAX_N];
bool marked[MAX_N];
unsigned int windows;
bool visited[MAX_N];
vector<int> neighbor[MAX_N];
int path[MAX_N];
int totalDraughts = 0;

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

void visit(int node, int previousNode, int level) {
    path[level] = node;
    visited[node] = true;
    if (window[node]) {
        windows++;
        int i = level;
        if (i > 0) {
            while (i >= 0 && !marked[path[i]]) {
                marked[path[i]]= true;
                i--;
            }
            totalDraughts += level - i;
        }
    }
    for (vector<int>::iterator it = neighbor[node].begin();it != neighbor[node].end();it++) {
        if (previousNode != *it) visit(*it, node, level + 1);
    }
}

int main(void) {
    int n = getInt();
    int m = getInt();

    FOR(i, n) window[i] = getInt() == 1;
    FOR(i, m) {
        int a = getInt() - 1, b = getInt() - 1;
        neighbor[a].push_back(b);
        neighbor[b].push_back(a);
    }

    unsigned int totalPairs = 0;
    FOR(i, n) {
        if (!visited[i] && window[i]) {
            windows = 0;
            visit(i, -1, 0);
            totalPairs += windows * (windows - 1) >> 1;
        }
    }
    printf("%u %d\n", totalPairs, totalDraughts);
}
