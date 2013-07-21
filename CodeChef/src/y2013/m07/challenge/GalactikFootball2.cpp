// Kruskal algorithm to find minimum spanning tree
// Version 2 - there is no need to create heap
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100100
#define MAX_WEIGHT 100000

int n, m;
int set[MAX_N];
char setDepth[MAX_N];
int graphComponents;
int weight[MAX_N];
bool isRoot[MAX_N];

char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

int root(int a) {
    while (set[a] != -1) a = set[a];
    return a;
}

int join(int a, int b) {
    int ra = root(a);
    int rb = root(b);
    if (ra != rb) {
        graphComponents--;
        if (setDepth[ra] < setDepth[rb]) {
            set[ra] = rb;
            isRoot[ra] = false;
            return rb;
        } else {
            set[rb] = ra;
            isRoot[rb] = false;
            if (setDepth[ra] == setDepth[rb]) setDepth[ra]++;
            return ra;
        }
    }
    return ra;
}

void updateRootWeight(int a) {
    int r = root(a);
    if ((weight[a] >= 0 && weight[r] < 0) || (weight[a] >= 0 && weight[a] < weight[r])) {
        weight[r] = weight[a];
    }
}


int main(void) {
    int n = getInt(), m = getInt();
    FOR(i, n) set[i] = -1, setDepth[i] = 1, isRoot[i] = true;
    graphComponents = n;

    FOR(i, m) join(getInt() - 1, getInt() - 1);
    FOR(i, n) weight[i] = getInt();
    FOR(i, n) updateRootWeight(i);

    bool ok = true;
    int result = 0;
    if (graphComponents > 1) {
        int minWeight = MAX_WEIGHT;
        FOR(i, n)
            if (isRoot[i]) {
                if (weight[i] < 0) {
                    ok = false;
                    break;
                } else {
                    result += weight[i];
                    if (weight[i] < minWeight) minWeight = weight[i];
                }
            }
        result += (graphComponents - 2) * minWeight;
    }
    printf("%d", ok ? result : -1);
}
