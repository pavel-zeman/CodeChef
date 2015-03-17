// Use union set to detect walls, that split existing connected component. Then go backwards through the list of operations and use union set again to "connect" split components and answers all the queries.
// http://www.codechef.com/MARCH15/problems/MTRWY
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1024
#define HORIZONTAL_WALL 1
#define VERTICAL_WALL 2
#define CHECK_CONNECTED 3
#define LARGEST_COMPONENT 4
#define JOIN 5


int n, m;

int totalComponents;
int biggestComponent;
bool horizontalWall[MAX_N][MAX_N];
bool verticalWall[MAX_N][MAX_N];
bool processed[MAX_N][MAX_N];

struct UnionSet {
    int prev;
    int depth;
} unionSet[MAX_N * MAX_N];

struct ComponentUnionSet {
    int prev;
    int depth;
    int size;
} componentUnionSet[MAX_N * MAX_N];

struct Operation {
    int operation;
    int x1, y1, x2, y2;

    Operation(int operation, int x1, int y1, int x2, int y2) {
        this->operation = operation;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
};

queue<pair<int, int> > searchQueue;
stack<Operation> operations;


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

int root(int x, int y) {
    int pos = y * (n + 1) + x;
    while (unionSet[pos].prev != pos) pos = unionSet[pos].prev;
    return pos;
}

void join(int a, int b) {
    if (unionSet[a].depth > unionSet[b].depth) {
        unionSet[b].prev = a;
    } else if (unionSet[a].depth < unionSet[b].depth) {
        unionSet[a].prev = b;
    } else {
        unionSet[a].prev = b;
        unionSet[b].depth++;
    }
}


int componentRoot(int x, int y) {
    int pos = x + y * n;
    while (componentUnionSet[pos].prev != pos) pos = componentUnionSet[pos].prev;
    return pos;
}

int componentJoin(int a, int b) {
    int result = 0;
    if (componentUnionSet[a].depth > componentUnionSet[b].depth) {
        componentUnionSet[b].prev = a;
        componentUnionSet[a].size += componentUnionSet[b].size;
        result = componentUnionSet[a].size;
    } else if (componentUnionSet[a].depth < componentUnionSet[b].depth) {
        componentUnionSet[a].prev = b;
        componentUnionSet[b].size += componentUnionSet[a].size;
        result = componentUnionSet[b].size;
    } else {
        componentUnionSet[a].prev = b;
        componentUnionSet[b].depth++;
        componentUnionSet[b].size += componentUnionSet[a].size;
        result = componentUnionSet[b].size;
    }
    return result;
}


void recalcComponent(int x, int y) {
    int componentSize = 0;
    int root = x + y * n;
    searchQueue.push(make_pair(x, y));
    processed[x][y] = true;

    while (!searchQueue.empty()) {
        pair<int, int> p = searchQueue.front();
        searchQueue.pop();
        int sx = p.first;
        int sy = p.second;
        componentSize++;
        if (!verticalWall[sx + 1][sy] && !processed[sx + 1][sy]) {
            processed[sx + 1][sy] = true;
            searchQueue.push(make_pair(sx + 1, sy));
        }
        if (!verticalWall[sx][sy] && !processed[sx - 1][sy]) {
            processed[sx - 1][sy] = true;
            searchQueue.push(make_pair(sx - 1, sy));
        }
        if (!horizontalWall[sx][sy + 1] && !processed[sx][sy + 1]) {
            processed[sx][sy + 1] = true;
            searchQueue.push(make_pair(sx, sy + 1));
        }
        if (!horizontalWall[sx][sy] && !processed[sx][sy - 1]) {
            processed[sx][sy - 1] = true;
            searchQueue.push(make_pair(sx, sy - 1));
        }
        componentUnionSet[sx + sy * n].prev = root;
        componentUnionSet[sx + sy * n].depth = 2;
    }

    componentUnionSet[root].depth = 1;
    componentUnionSet[root].size = componentSize;
    if (componentSize > biggestComponent) biggestComponent = componentSize;
}


void calcComponents() {
    FOR(i, n) FOR(j, m) processed[i][j] = false;
    FOR(i, n) FOR(j, m)
        if (!processed[i][j])
            recalcComponent(i, j);
}

void readInput(int q) {
    FOR(i, q) {
        int type = getInt();
        int x1, y1, x2, y2;
        switch (type) {
            case HORIZONTAL_WALL:
                x1 = getInt() - 1;
                y1 = getInt() - 1;
                if (!horizontalWall[x1][y1 + 1]) {
                    horizontalWall[x1][y1 + 1] = true;
                    int r1 = root(x1, y1 + 1);
                    int r2 = root(x1 + 1, y1 + 1);
                    if (r1 == r2) {
                        operations.push(Operation(JOIN, x1, y1, x1, y1 + 1));
                    } else {
                        join(r1, r2);
                    }
                }
                break;

            case VERTICAL_WALL:
                x1 = getInt() - 1;
                y1 = getInt() - 1;
                if (!verticalWall[x1 + 1][y1]) {
                    verticalWall[x1 + 1][y1] = true;
                    int r1 = root(x1 + 1, y1);
                    int r2 = root(x1 + 1, y1 + 1);
                    if (r1 == r2) {
                        operations.push(Operation(JOIN, x1, y1, x1 + 1, y1));
                    } else {
                        join(r1, r2);
                    }
                }
                break;

            case CHECK_CONNECTED:
                x1 = getInt() - 1;
                y1 = getInt() - 1;
                x2 = getInt() - 1;
                y2 = getInt() - 1;
                operations.push(Operation(type, x1, y1, x2, y2));
                break;

            case LARGEST_COMPONENT:
                operations.push(Operation(type, 0, 0, 0, 0));
                break;
        }
    }
}


long long int processOperations() {
    long long int total = 0;
    int r1, r2, joinedSize;
    while (!operations.empty()) {
        Operation operation = operations.top();
        operations.pop();
        switch (operation.operation) {
            case JOIN:
                r1 = componentRoot(operation.x1, operation.y1);
                r2 = componentRoot(operation.x2, operation.y2);
                joinedSize = componentJoin(r1, r2);
                if (joinedSize > biggestComponent) biggestComponent = joinedSize;
                break;

            case CHECK_CONNECTED:
                r1 = componentRoot(operation.x1, operation.y1);
                r2 = componentRoot(operation.x2, operation.y2);
                if (r1 == r2) total++;
                break;

            case LARGEST_COMPONENT:
                total += biggestComponent;
                break;
        }
    }
    return total;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();
        int q = getInt();

        totalComponents = 0;
        FOR(i, n + 1) FOR(j, m + 1) horizontalWall[i][j] = verticalWall[i][j] = false;
        FOR(i, (n + 1) * (m + 1)) {
            unionSet[i].prev = i;
            unionSet[i].depth = 1;
        }
        FOR(i, m) {
            verticalWall[0][i] = verticalWall[n][i] = true;
            unionSet[i * (n + 1)].prev = unionSet[n + i * (n + 1)].prev = 0;
            unionSet[i * (n + 1)].depth = unionSet[n + i * (n + 1)].depth = 2;
        }
        FOR(j, n) {
            horizontalWall[j][0] = horizontalWall[j][m] = true;
            unionSet[j].prev = unionSet[j + m * (n + 1)].prev = 0;
            unionSet[j].depth = unionSet[j + m * (n + 1)].depth = 2;
        }
        unionSet[n + m * (n + 1)].prev = 0;
        unionSet[n + m * (n + 1)].depth = 2;
        unionSet[0].depth = 1;
        biggestComponent = 0;

        readInput(q);
        calcComponents();
        long long int total = processOperations();

        printf("%lld\n", total);
    }
}
