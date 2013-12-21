// Unfortunately, this is too slow - O(n * m)
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

int main(void) {
    n = getInt();
    FOR(i, n) color[i] = 0;
    FOR(i, n - 1) {
        int a = getInt() - 1, b = getInt() - 1;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }

    m = getInt();
    FOR(i, m) {
        int t = getInt();
        int u = getInt() - 1;
        if (t == 0) {
            qPos = 0;
            qSize = 0;
            add(u, -1);
            char c = color[u];
            while (!isEmpty()) {
                int start = queue[qPos].item;
                int previous = queue[qPos].previousItem;
                qPos++;
                for (vector<int>::iterator it = neighbors[start].begin();it != neighbors[start].end();it++) {
                    if (*it != previous && color[*it] == c) {
                        add(*it, start);
                    }
                }
            }
            printf("%d\n", qSize);
        } else {
            color[u] ^= 1;
        }
    }
}

