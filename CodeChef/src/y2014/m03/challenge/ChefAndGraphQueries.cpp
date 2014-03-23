// Sort the queries by interval length and try to reuse results from small intervals to calculate results for long intervals
// http://www.codechef.com/MARCH14/problems/GERALD07
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <algorithm>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_M 200002
#define MAX_N 200002

using namespace std;

int n, m, q;
struct Edge {
    int a, b;
} edges[MAX_M];

struct Query {
    int l, r;
    int result;
} queries[MAX_M];

int depth[MAX_N];
int set[MAX_N];
int components;

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

int root(int a) {
    while (a != set[a]) a = set[a];
    return a;
}

void merge(int edge) {
    int a = edges[edge].a;
    int b = edges[edge].b;
    if (a != b) {
        int ra = root(a);
        int rb = root(b);
        if (ra != rb) {
            components--;
            if (depth[ra] < depth[rb]) {
                set[ra] = rb;
            } else {
                set[rb] = ra;
                if (depth[ra] == depth[rb]) depth[ra]++;
            }
        }
    }
}

bool cmp(int a, int b) {
    int la = queries[a].r - queries[a].l;
    int lb = queries[b].r - queries[b].l;

    return la < lb || (la == lb && queries[a].l < queries[b].l);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();
        q = getInt();

        FOR(i, m) {
            edges[i].a = getInt() - 1;
            edges[i].b = getInt() - 1;
        }

        vector<int> toProcess;
        FOR(i, q) {
            queries[i].l = getInt() - 1;
            queries[i].r = getInt();
            toProcess.push_back(i);
        }
        sort(toProcess.begin(), toProcess.end(), cmp);

        vector<int> remain;
        vector<int> *v1, *v2;
        v1 = &toProcess;
        v2 = &remain;
        while (v1->size() > 0) {
            v2->clear();
            memset(depth, 0, sizeof(depth[0]) * n);
            FOR(j, n) set[j] = j;
            components = n;

            int toProcessSize = v1->size();
            int l = queries[(*v1)[0]].l;
            int r = queries[(*v1)[0]].r;
            FORE(j, l, r) merge(j);
            queries[(*v1)[0]].result = components;

            FORE(i, 1, toProcessSize) {
                int currentQuery = (*v1)[i];
                if (queries[currentQuery].l <= l && queries[currentQuery].r >= r) {
                    FORE(j, queries[currentQuery].l, l) merge(j);
                    FORE(j, r, queries[currentQuery].r) merge(j);
                    l = queries[currentQuery].l;
                    r = queries[currentQuery].r;
                    queries[currentQuery].result = components;
                } else {
                    v2->push_back((*v1)[i]);
                }
            }
            vector<int> *v3;
            v3 = v2;
            v2 = v1;
            v1 = v3;
        }

        FOR(i, q) printf("%d\n", queries[i].result);
    }
}

