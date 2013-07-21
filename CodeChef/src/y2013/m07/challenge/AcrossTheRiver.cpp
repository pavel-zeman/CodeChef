// Dijkstra's algorithm on a graph with vertices based on all the combinations of point (pile) and disk
// http://www.codechef.com/JULY13/problems/RIVPILE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 252
#define MAX_M 252

int m, n, w;


int heap[MAX_N * MAX_M];
int heapSize = 0;
int distances[MAX_N][MAX_N];


struct point {
    int x;
    int y;
} points[MAX_N];

struct disk {
    int r;
    int c;
} disks[MAX_M];
bool diskUsed[MAX_M];

int currentMin[MAX_N * MAX_M];
int heapPos[MAX_N * MAX_M];

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


int heapParent(int a) {
    return (a - 1) >> 1;
}

int heapLeftChild(int a) {
    return (a << 1) + 1;
}

void heapUp(int i) {
    int origValue = heap[i];
    while (i > 0 && currentMin[origValue] < currentMin[heap[heapParent(i)]]) {
        heap[i] = heap[heapParent(i)];
        heapPos[heap[i]] = i;
        i = heapParent(i);
    }
    heap[i] = origValue;
    heapPos[origValue] = i;
}

void addHeap(int pos) {
    heap[heapSize] = pos;
    heapUp(heapSize++);
}

void heapUpdate(int pos) {
    if (heapPos[pos] == -1) {
        addHeap(pos);
    } else {
        heapUp(heapPos[pos]);
    }
}

int heapMin(void) {
    int result = heap[0];

    heap[0] = heap[--heapSize];
    int i = 0;
    int child = heapLeftChild(i);
    int origValue = heap[0];

    while ((child < heapSize && currentMin[origValue] > currentMin[heap[child]]) || (child + 1 < heapSize && currentMin[origValue] > currentMin[heap[child + 1]])) {
        int c = child;
        if (child + 1 < heapSize && currentMin[heap[child + 1]] < currentMin[heap[child]]) c++;
        heap[i] = heap[c];
        heapPos[heap[i]] = i;
        i = c;
        child = heapLeftChild(i);
    }
    heap[i] = origValue;
    heapPos[origValue] = i;

    heapPos[result] = -1;
    return result;
}

int cmp(const void *p1, const void *p2) {
    struct disk *disk1 = (struct disk *)p1;
    struct disk *disk2 = (struct disk *)p2;
    return disk1->r == disk2->r ? disk2->c - disk1->c : disk1->r - disk2->r;
    //return disk1->r - disk2->r;
}

void removeRedundantDisks() {
    // remove all redundant disks
    int minPrice = disks[m - 1].c + 1;
    for(int i=m-1;i>=0;i--) {
        if (disks[i].c >= minPrice)
            diskUsed[i] = false;
        else
            minPrice = disks[i].c;
    }
    int targetDisk = 0;

    FOR(i, m) {
        if (diskUsed[i]) disks[targetDisk++] = disks[i];
    }
    m = targetDisk;
}

int calcPos(int point, int disk) {
    return point * m + disk;
}

int getPoint(int pos) {
    return pos / m;
}

int getDisk(int pos) {
    return pos % m;
}

int findDisk(int minRadius) {
    int l = 0, r = m - 1;
    int center = (l + r) >> 1;
    while (l < r) {
        if (disks[center].r == minRadius) return center;
        if (disks[center].r < minRadius) l = center + 1; else r = center - 1;
        center = (l + r) >> 1;
    }

    if (disks[l].r >= minRadius) return l;
    l++;
    return l < m ? l : -1;
}

int min(int a, int b) {
    return a < b ? a : b;
}

long long int sqr(long long int a) {
    return a * a;
}

void calcDistances() {
    FOR(i, n) FOR(j, n) {
        long long int dist2 = sqr(points[i].x - points[j].x) + sqr(points[i].y - points[j].y);
        int dist = (int)sqrt(dist2) - 1;
        while (dist < 0) dist++;
        while (sqr(dist) < dist2) dist++;
        distances[i][j] = dist;
    }
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();
        w = getInt();
        FOR(i, n) {
            points[i].x = getInt();
            points[i].y = getInt();
        }

        // calculate point distances
        calcDistances();

        FOR(i, m) {
            disks[i].r = getInt();
            disks[i].c = getInt();
            diskUsed[i] = true;
        }
        // sort by radius
        qsort(disks, m, sizeof(disks[0]), cmp);

        removeRedundantDisks();

        heapSize = 0;
        FOR(i, m * n) heapPos[i] = -1;
        FOR(i, m * n) currentMin[i] = INT_MAX;

        FOR(i, n) {
            int d = findDisk(points[i].y);
            if (d >= 0) {
                FORE(j, d, m) {
                    int pos = calcPos(i, j);
                    currentMin[pos] = disks[j].c;
                    addHeap(pos);
                }
            }
        }

        int result = INT_MAX;
        while (heapSize > 0) {
            int pos = heapMin();
            int point = getPoint(pos);
            int disk = getDisk(pos);

            if (points[point].y + disks[disk].r >= w) {
                result = currentMin[pos];
                break;
            }

            FOR(i, n) {
                if (i != point) {
                    int dist = distances[point][i];
                    int minDisk = findDisk(dist - disks[disk].r);
                    if (minDisk >= 0) {
                        FORE(j, minDisk, m) {
                            int pos2 = calcPos(i, j);
                            if (currentMin[pos] + disks[j].c < currentMin[pos2]) {
                                currentMin[pos2] = currentMin[pos] + disks[j].c;
                                heapUpdate(pos2);
                            } else
                                break; // no need to continue, because there is no chance of improvements
                        }
                    }
                }
            }
        }
        if (result == INT_MAX)
            printf("%s\n", "impossible");
        else
            printf("%d\n", result);
    }
}
