// Lowest common ancestor in the tree rooted in B. Inspired by http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=lowestCommonAncestor.
// http://www.codechef.com/DEC14/problems/CHEFPRES
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

#define MAX_N 10010
#define MAX_LOG_N 16

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int n, b;
vector<int> neighbor[MAX_N];
int f[MAX_N];
int level[MAX_N];
int ancestor[MAX_N];
bool visited[MAX_N];
int p[MAX_N][MAX_LOG_N];


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

void visit(int node, int previous, int l) {
    level[node] = l;
    ancestor[node] = previous;
    visited[node] = true;
    for (vector<int>::iterator it = neighbor[node].begin(); it != neighbor[node].end(); it++) {
        if (!visited[*it]) visit(*it, node, l + 1);
    }
}

void prepare() {
    FOR(i, n) for (int j = 0; 1 << j < n; j++) p[i][j] = -1;
    FOR(i, n) p[i][0] = ancestor[i];

    for (int j = 1; 1 << j < n; j++) FOR(i, n) if (p[i][j - 1] != -1) {
        p[i][j] = p[p[i][j - 1]][j - 1];
    }
}

int query(int a, int b) {
    if (level[a] < level[b]) {
        int temp = a;
        a = b;
        b = temp;
    }
    int log;
    for (log = 1; 1 << log <= level[a]; log++);
    log--;

    for (int i = log; i >= 0; i--)
        if (level[a] - (1 << i) >= level[b]) {
            a = p[a][i];
        }
    if (a == b) return a;

    for (int i = log; i >= 0; i--)
        if (p[a][i] != -1 && p[a][i] != p[b][i]) {
            a = p[a][i];
            b = p[b][i];
        }
    return ancestor[a];
}

int main(void) {
    n = getInt();
    getInt(); // we don't need k
    b = getInt() - 1;
    FOR(i, n - 1) {
        int x = getInt() - 1;
        int y = getInt() - 1;
        neighbor[x].push_back(y);
        neighbor[y].push_back(x);
    }
    FOR(i, n) f[i] = getInt();
    FOR(i, n) visited[i] = false;
    visit(b, -1, 0);
    prepare();

    int q = getInt();
    FOR(i, q) {
        int a = getInt() - 1, p = getInt();
        int maxLevel = -1;
        int city = -1;
        FOR(j, n) if (f[j] == p) {
            int c = query(j, a);
            if (level[c] > maxLevel) {
                maxLevel = level[c];
                city = j + 1;
            }
        }
        printf("%d\n", city);
    }
}
