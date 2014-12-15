// Finds minimum spanning tree
// http://www.codechef.com/DEC14/problems/KALKI
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 402

int x[MAX_N], y[MAX_N];
int n;
int prev[MAX_N];
int depth[MAX_N];
bool processed[MAX_N];
int maxDist[MAX_N];
int dist[MAX_N][MAX_N];

struct HeapItem {
    int v1, v2;
    int d;
} heap[MAX_N * MAX_N / 2];
int heapSize;


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
    while (prev[a] != a) a = prev[a];
    return a;
}

void merge(int a, int b) {
    int ra = root(a);
    int rb = root(b);
    if (depth[ra] < depth[rb]) {
        prev[ra] = rb;
    } else {
        prev[rb] = ra;
        if (depth[ra] == depth[rb]) depth[ra]++;
    }
}

int calcDist(int a, int b) {
    int dx = x[a] - x[b];
    int dy = y[a] - y[b];
    return dx * dx + dy * dy;
}

int calcAddVertex(int v, int d) {
    int total = 0;
    if (d > maxDist[v]) {
        FOR(i, n) if (dist[v][i] > maxDist[v] && dist[v][i] <= d) total++;
    }
    return 0;
}

int calcAdd(int a, int b) {
    int d = dist[a][b];
    return calcAddVertex(a, d) + calcAddVertex(b, d);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int parent(int p) {
    return (p - 1) >> 1;
}

int child(int p) {
    return (p << 1) + 1;
}

void copyItem(int src, int dst) {
    heap[dst].v1 = heap[src].v1;
    heap[dst].v2 = heap[src].v2;
    heap[dst].d = heap[src].d;
}

void addItem(int v1, int v2, int d) {
    int p = heapSize;
    while (p > 0 && d < heap[parent(p)].d) {
        int temp = parent(p);
        copyItem(temp, p);
        p = temp;
    }
    heap[p].v1 = v1;
    heap[p].v2 = v2;
    heap[p].d = d;
    heapSize++;
}


void removeTop() {
    heapSize--;
    int d = heap[heapSize].d;
    int p = 0;
    while (child(p) < heapSize && heap[child(p)].d < d || child(p) + 1 < heapSize && heap[child(p) + 1].d < d) {
        int minp = child(p);
        if (minp + 1 < heapSize && heap[minp + 1].d < heap[minp].d) minp++;
        copyItem(minp, p);
        p = minp;
    }
    copyItem(heapSize, p);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) {
            x[i] = getInt();
            y[i] = getInt();
            prev[i] = i;
            depth[i] = 0;
            maxDist[i] = 0;
        }
        heapSize = 0;
        FOR(i, n) FORE(j, i + 1, n) addItem(i, j, calcDist(i, j));
        while (heapSize > 0) {
            if (root(heap[0].v1) != root(heap[0].v2)) {
                merge(heap[0].v1, heap[0].v2);
                printf("%d %d\n", heap[0].v1 + 1, heap[0].v2 + 1);
            }
            removeTop();
        }

        /*FOR(k, n - 1) {
            int minDist = 5000 * 5000 * 10;
            int v1, v2;
            FOR(i, n) FORE(j, i + 1, n) if (root(i) != root(j)) {
                if (dist[i][j] < minDist) {
                    v1 = i;
                    v2 = j;
                    minDist = dist[i][j];
                }
            }
            printf("%d %d\n", v1 + 1, v2 + 1);
            merge(v1, v2);
        }*/

        /*int edges = 0;
        while (edges < n - 1) {
            int maxAdd = 0;
            int v1, v2;
            FOR(i, n) {
                FORE(j, i + 1, n) {
                    if (root(i) != root(j)) {
                        int temp = calcAdd(i, j);
                        if (temp > maxAdd) {
                            maxAdd = temp;
                            v1 = i;
                            v2 = j;
                        }
                    }
                }
            }
            if (maxAdd > 0) {
                printf("%d %d\n", v1 + 1, v2 + 1);
                merge(v1, v2);
                int d = dist(v1, v2);
                maxDist[v1] = max(maxDist[v1], d);
                maxDist[v2] = max(maxDist[v2], d);
                edges++;
            } else break;
        }
        if (edges < n - 1) {
            FOR(i, n) FORE(j, i + 1, n) if (root(i) != root(j)) {
                printf("%d %d\n", i + 1, j + 1);
                merge(i, j);
            }
        }*/
    }
}
