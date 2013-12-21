// Still O(n * m) with little memoization
// http://www.codechef.com/DEC13/problems/QTREE6
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

using namespace std;

#define MAX_N 100010

vector<int> neighbors[MAX_N];

char color[MAX_N];

int n, m;


struct Queue {
    int item;
    int previousItem;
} queue[MAX_N];

int qPos, qSize;


struct Node {
    int parent;
    int color;
    vector<int> children;
    int numSameColor;
    int numTotal;
} nodes[MAX_N];


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

void add(int item, int previousItem) {
    queue[qSize].item = item;
    queue[qSize].previousItem = previousItem;
    qSize++;
}

bool isEmpty(void) {
    return qPos == qSize;
}


int calc(int node) {
    int res = 1;
    for (vector<int>::iterator it = nodes[node].children.begin(); it != nodes[node].children.end();it++) {
        res += calc(*it);
    }
    //printf("Setting node %d count to %d\n", node, res);
    return nodes[node].numTotal = nodes[node].numSameColor = res;
}


void flip(int node) {
    nodes[node].color ^= 1;
    int color = nodes[node].color;
    int count = 1;
    for (vector<int>::iterator it = nodes[node].children.begin(); it != nodes[node].children.end();it++) {
        if (nodes[*it].color == color) count += nodes[*it].numSameColor;
    }
    nodes[node].numSameColor = count;
}

void decrease(int node, int count) {
    int color = nodes[node].color;
    while (node != -1 && nodes[node].color == color) {
        nodes[node].numSameColor -= count;
        //if (nodes[node].numSameColor <= 0) printf("Error at %d = %d\n", node, nodes[node].numSameColor);
        node = nodes[node].parent;
    }
}

int main(void) {
    n = getInt();
    FOR(i, n) color[i] = 0;
    FOR(i, n - 1) {
        int a = getInt() - 1, b = getInt() - 1;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }

    qPos = 0;
    qSize = 0;
    add(0, -1);
    while (!isEmpty()) {
        int start = queue[qPos].item;
        int previous = queue[qPos].previousItem;
        nodes[start].parent = previous;
        nodes[start].color = 0;

        for (vector<int>::iterator it = neighbors[start].begin();it != neighbors[start].end();it++) {
            if (*it != previous) {
                add(*it, start);
                nodes[start].children.push_back(*it);
            }
        }
        qPos++;
    }

    calc(0);

    m = getInt();
    FOR(i, m) {
        int t = getInt();
        int u = getInt() - 1;
        //printf("Processing %d %d %d\n", t, u, nodes[30679].numSameColor);
        if (t == 0) {
            // calc
            while (nodes[u].parent != -1 && nodes[u].color == nodes[nodes[u].parent].color) u = nodes[u].parent;
            printf("%d\n", nodes[u].numSameColor);
        } else {
            if (nodes[u].parent == -1) {
                flip(u);
            } else {

                if (nodes[u].color == nodes[nodes[u].parent].color) {
                    // same color as parent
                    int origCount = nodes[u].numSameColor;
                    flip(u);
                    decrease(nodes[u].parent, origCount);
                } else {
                    // different color than parent
                    flip(u);
                    decrease(nodes[u].parent, -nodes[u].numSameColor);
                }
            }
        }
        //FOR(i, n) printf("%d ", nodes[i].numSameColor);
        //printf("\n");
    }
}

