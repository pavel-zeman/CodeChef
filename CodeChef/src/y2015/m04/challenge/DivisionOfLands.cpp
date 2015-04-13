// Generate components, choose the ones starting from the biggest one and then split the smallest one.
// http://www.codechef.com/APRIL15/problems/DIVLAND
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

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1000010

bool first[MAX_N];
vector<int> neighbors[MAX_N];
vector<vector<int> > components;
bool visited[MAX_N];
int component;
int order[MAX_N];
bool componentUsed[MAX_N];

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

void visit(int node) {
    components[component].push_back(node);
    FOR(i, (int)neighbors[node].size()) {
        int neighbor = neighbors[node][i];
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            visit(neighbor);
        }
    }
}

int cmp(const void *v1, const void *v2) {
     int o1 = *(int *)v1;
     int o2 = *(int *)v2;
     return (int)components[o2].size() - (int)components[o1].size();
}


int main(void) {
    int n = getInt();
    int m = getInt();
    FOR(i, m) {
        int a = getInt();
        int b = getInt();
        getInt();
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
    int half = n >> 1;

    FOR(i, n) {
        if (!visited[i]) {
            components.push_back(vector<int>());
            visited[i] = true;
            visit(i);
            component++;
        }
    }

    FOR(i, component) order[i] = i;
    qsort(order, component, sizeof(order[0]), cmp);


    int totalNodes = 0;
    FOR(i, component) {
        int c = order[i];
        if (totalNodes + (int)components[c].size() <= half) {
            FOR(j, (int)components[c].size()) {
                first[components[c][j]] = true;
            }
            totalNodes += components[c].size();
            componentUsed[c] = true;
        }
    }

    int minSize = n + 1;
    int selectedComponent = -1;
    FOR(i, component) {
        if (!componentUsed[i] && (int)components[i].size() < minSize) {
            minSize = components[i].size();
            selectedComponent = i;
        }
    }

    FOR(i, (int)components[selectedComponent].size()) {
        if (totalNodes < half) {
            first[components[selectedComponent][i]] = true;
            totalNodes++;
        }
    }

    FOR(i, n)
        if (first[i])
            printf("%d ", i);
}
