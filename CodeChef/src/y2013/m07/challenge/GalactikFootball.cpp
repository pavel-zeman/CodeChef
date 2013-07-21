// Kruskal algorithm to find minimum spanning tree
// http://www.codechef.com/JULY13/problems/GALACTIK
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

int n, m;


int set[MAX_N], setDepth[MAX_N];
int graphComponents;
int weight[MAX_N];
bool isRoot[MAX_N];
int heap[MAX_N];
int heapSize = 0;



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

int heapParent(int a) {
    return (a - 1) >> 1;
}

int heapLeftChild(int a) {
    return (a << 1) + 1;
}

void heapSwap(int a, int b) {
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

void addHeap(int pos) {
    heap[heapSize] = pos;
    int i = heapSize++;
    while (i > 0 && weight[heap[i]] < weight[heap[heapParent(i)]]) {
        heapSwap(i, heapParent(i));
        i = heapParent(i);
    }
}

int heapMin(void) {
    int result = heap[0];

    heap[0] = heap[--heapSize];
    int i = 0;
    int child = heapLeftChild(i);
    while ((child < heapSize && weight[heap[i]] > weight[heap[child]]) || (child + 1 < heapSize && weight[heap[i]] > weight[heap[child + 1]])) {
        int c = child;
        if (child + 1 < heapSize && weight[heap[child + 1]] < weight[heap[child]]) c++;
        heapSwap(i, c);
        i = c;
        child = heapLeftChild(i);
    }

    return result;
}


int main(void) {
    int n = getInt(), m = getInt();
    FOR(i, n) set[i] = -1, setDepth[i] = 1, isRoot[i] = true;
    graphComponents = n;

    FOR(i, m) join(getInt() - 1, getInt() - 1);
    FOR(i, n) weight[i] = getInt();
    FOR(i, n) updateRootWeight(i);

    // check if all the components can be connected
    bool ok = true;
    if (graphComponents > 1) {
        FOR(i, n) if (isRoot[i] && weight[i] < 0) { ok = false; break; }
    }
    int result = -1;
    if (ok) {
        result = 0;
        FOR(i, n) if (isRoot[i]) addHeap(i);

        while (graphComponents > 1) {
            int p1 = heapMin();
            int p2 = heapMin();
            result += weight[p1] + weight[p2];
            int newRoot = join(p1, p2);
            updateRootWeight(p1);
            updateRootWeight(p2);
            addHeap(newRoot);
        }
    }
    printf("%d", result);
}
