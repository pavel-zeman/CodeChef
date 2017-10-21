// Based on Tarjan's paper at ftp://ftp.cs.princeton.edu/reports/1989/228.pdf
// https://www.codechef.com/OCT17/problems/LKYEDGE
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(int)(t);c++)
#define LLI long long int
#define MOD 1000000007


char ccc = 0;
int getInt() {
    int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}

int getString(char *start) {
    char *data = start;
    while (!(ccc > ' ' && ccc <= '~')) ccc = getc_unlocked(stdin);
    while (ccc > ' ' && ccc <= '~') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *data = 0;
    return data - start;
}


int getSignedInt() {
    int r = 0;
    while (!(ccc == '-' || (ccc >= '0' && ccc <= '9'))) ccc = getc_unlocked(stdin);
    bool minus = ccc == '-';
    if (minus) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

long long int getLongLongInt() {
    long long int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}


template <class type> void print(type a) {
    if (a < 0) {
        putc_unlocked('-', stdout);
        a = -a;
    }
    if (a == 0) {
        putc_unlocked('0', stdout);
    } else {
        char result[20];
        int resSize = 0;
        while (a > 0) {
            result[resSize++] = '0' + a % 10;
            a /= 10;
        }
        while (--resSize >= 0) putc_unlocked(result[resSize], stdout);
    }
    putc_unlocked('\n', stdout);
}

void printString(const char *str) {
    while (*str) putc_unlocked(*str++, stdout);
    putc_unlocked('\n', stdout);
}

int power(int a, int b) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % MOD;
        sq = sq * (LLI)sq % MOD;
        b >>= 1;
    }
    return result;
}

int inv(int a) {
    return power(a, MOD - 2);
}

template <class type> type gcd(type a, type b) {
    return b == 0 ? a : gcd(b, a % b);
}

void fail() {
    *((char *)0) = 0;
}

double cpu() {
    return clock() / (double)CLOCKS_PER_SEC;
}

#define MAX_V 10010
#define MAX_M 5010
vector<int> neighbor[MAX_V];
struct Edge {
    int u, v;
} edge[MAX_M];

vector<int> componentEdges[MAX_M];
int component[MAX_M];
int result[MAX_M];
int minSteps[MAX_M];
bool inCycle[MAX_M];
int prevEdge[MAX_V];
int qq[MAX_V];

int m;
int maxv;
int totalComponents;
bool visited[MAX_V];
int visited2[MAX_V];
int visited2Cnt;
bool bridge[MAX_M];
int pre[MAX_V];
int low[MAX_V];
int preCnt;
struct Block {
    int parentNode;
    int parentEdge;
    int parentCounter;
} parentBlocks[MAX_V];
int globalParentCounter;

#define MAX_N MAX_V
class DisjointSet {
public:
    int prev[MAX_N];
    int depth[MAX_N];

    int root(int a) {
        while (prev[a] != a) a = prev[a];
        return a;
    }

    void add(int x, int y) {
        x = root(x);
        y = root(y);
        if (x != y) {
            if (depth[x] > depth[y]) prev[y] = x;
            else if (depth[y] > depth[x]) prev[x] = y;
            else {
                prev[y] = x;
                depth[x]++;
            }
        }
    }

    void clear(int n) {
        FOR(i, n) {
            prev[i] = i;
            depth[i] = 0;
        }
    }
} ds;

class DisjointSetWithLabel {
public:
    int prev[MAX_N];
    int depth[MAX_N];
    int label[MAX_N];

    int root(int a) {
        while (prev[a] != a) a = prev[a];
        return a;
    }

    void add(int x, int y) {
        x = root(x);
        y = root(y);
        if (x != y) {
            if (depth[x] > depth[y]) {
                prev[y] = x;
                label[x] = label[y];
            } else if (depth[y] > depth[x]) {
                prev[x] = y;
                //label[y] = min(label[x], label[y]);
            } else {
                label[x] = label[y];
                prev[y] = x;
                depth[x]++;
            }
        }
    }

    int getLabel(int x) {
        return x < 0 ? x : label[root(x)];
    }

    void clear(int n) {
        FOR(i, n) {
            prev[i] = i;
            label[i] = i;
            depth[i] = 0;
        }
    }
} ds2;


void visit(int node, int prevEdge) {
    visited[node] = true;
    low[node] = pre[node] = preCnt++;

    FOR(i, neighbor[node].size()) {
        int e = neighbor[node][i];
        if (e != prevEdge) {
            int n = edge[e].u == node ? edge[e].v : edge[e].u;
            component[e] = totalComponents;
            if (!visited[n]) {
                visit(n, e);
                if (low[node] > low[n]) low[node] = low[n];
                if (low[n] == pre[n]) bridge[e] = true;
            } else {
                if (low[node] > pre[n]) low[node] = pre[n];
            }
        }
    }
}

int joinBlock(int b) {
    ds2.add(b, parentBlocks[b].parentNode);
    return ds2.getLabel(parentBlocks[b].parentNode);
    //return parentBlocks[b].parentNode;
}

void evert(int b) {
    if (parentBlocks[b].parentNode >= 0) {
        int last = -1;
        int lastEdge = -1;
        while (b >= 0) {
            int origParent = ds2.getLabel(parentBlocks[b].parentNode);
            int origEdge = parentBlocks[b].parentEdge;
            parentBlocks[b].parentNode = last;
            parentBlocks[b].parentEdge = lastEdge;
            last = b;
            lastEdge = origEdge;
            b = origParent;
        }
    }
}

int findParent(int b1, int b2) {
    globalParentCounter++;

    while (true) {
        if (b1 >= 0) {
            if (parentBlocks[b1].parentCounter == globalParentCounter) return b1;
            parentBlocks[b1].parentCounter = globalParentCounter;
            b1 = ds2.getLabel(parentBlocks[b1].parentNode);
        }
        if (b2 >= 0) {
            if (parentBlocks[b2].parentCounter == globalParentCounter) return b2;
            parentBlocks[b2].parentCounter = globalParentCounter;
            b2 = ds2.getLabel(parentBlocks[b2].parentNode);
        }
    }
}

int ts;

void calc(int component, int mv) {
    int edges = componentEdges[component].size();
    //printf("Total edges: %d\n", edges);
    FOR(i, edges) {
        ds.clear(mv);
        ds2.clear(mv);
        FOR(j, mv) parentBlocks[j].parentNode = -1;
        FORE(j, i, edges) inCycle[componentEdges[component][j]] = false;
        FORE(j, i, edges) {
            int e = componentEdges[component][j];
            int u = edge[e].u;
            int v = edge[e].v;
            int r1 = ds.root(u);
            int r2 = ds.root(v);
            //FOR(i, 5) printf("Block: %d, parent: %d, parent label: %d\n", i, parentBlocks[i].parentNode, ds2.getLabel(parentBlocks[i].parentNode));
            if (r1 == r2) {
                // new cycle
                //printf("%d, %d: Edge %d adds a cycle\n", i, j, e);
                //FOR(k, mv) visited[k] = false;

                int r21 = ds2.root(u);
                int r22 = ds2.root(v);
                int toAdd = (i > 0 ? componentEdges[component][i] - componentEdges[component][i - 1] : componentEdges[component][0] + 1) * (m - e);
                if (r21 != r22) {
                    //ds2.add(r21, r22);
                    //r21 = ds2.root(u);
                    int lu = ds2.getLabel(r21);
                    int lv = ds2.getLabel(r22);
                    int lp = findParent(lu, lv);
                    //printf("Label: %d %d %d %d %d\n", lu, lv, parentBlocks[lu].parentNode, parentBlocks[lv].parentNode, lp);
                    while (lu != lp) {
                        int e2 = parentBlocks[lu].parentEdge;
                        inCycle[e2] = true;
                        //printf("Adding to edge1 %d at %d, %d\n", e2, lu, parentBlocks[lu].parentNode);
                        result[e2] += toAdd;
                        lu = joinBlock(lu);
                    }
                    while (lv != lp) {
                        int e2 = parentBlocks[lv].parentEdge;
                        //printf("Adding to edge2 %d at %d\n", e2, lv);
                        inCycle[e2] = true;
                        result[e2] += toAdd;
                        lv = joinBlock(lv);
                    }
                    //FOR(i, 5) printf("Block: %d, parent: %d, parent label: %d\n", i, parentBlocks[i].parentNode, ds2.getLabel(parentBlocks[i].parentNode));
                }
                inCycle[e] = true;
                result[e] += toAdd;


            } else {
                ds.add(r1, r2);
                int l1 = ds2.getLabel(u);
                int l2 = ds2.getLabel(v);
                //printf("Adding edge: %d %d, %d %d\n", u, v, l1, l2);
                evert(l1);
                parentBlocks[l1].parentNode = l2;
                parentBlocks[l1].parentEdge = e;
            }
        }
        //printf("TS: %d %d\n", i, ts);
        //ts = 0;
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        m = getInt();
        maxv = 0;
        FOR(i, MAX_V) neighbor[i].clear();

        FOR(i, m) {
            edge[i].u = getInt() - 1;
            edge[i].v = getInt() - 1;
            neighbor[edge[i].u].push_back(i);
            neighbor[edge[i].v].push_back(i);
            maxv = max(maxv, max(edge[i].u, edge[i].v));
            bridge[i] = false;
            result[i] = 0;
        }
        maxv++;

        totalComponents = 0;
        preCnt = 0;
        FOR(i, maxv) visited[i] = false;
        FOR(i, maxv) if (!visited[i] && !neighbor[i].empty()) {
            visit(i, -1);
            totalComponents++;
        }

        // Repeat search for connected components without bridges
        FOR(i, maxv) visited[i] = false;
        FOR(i, MAX_V) neighbor[i].clear();
        FOR(i, m) if (!bridge[i]) {
            neighbor[edge[i].u].push_back(i);
            neighbor[edge[i].v].push_back(i);
        }
        totalComponents = 0;
        preCnt = 0;
        FOR(i, maxv) if (!visited[i] && !neighbor[i].empty()) {
            visit(i, -1);
            totalComponents++;
        }


        FOR(i, totalComponents) componentEdges[i].clear();
        FOR(i, m) componentEdges[component[i]].push_back(i);
        FOR(i, totalComponents) {
            sort(componentEdges[i].begin(), componentEdges[i].end());
            map<int, int> vmap;
            for(auto it = componentEdges[i].begin(); it != componentEdges[i].end(); it++) {
                vmap[edge[*it].u] = 0;
                vmap[edge[*it].v] = 0;
            }
            int index = 0;
            for(auto it = vmap.begin(); it != vmap.end(); it++) it->second = index++;
            for(auto it = componentEdges[i].begin(); it != componentEdges[i].end(); it++) {
                edge[*it].u = vmap[edge[*it].u];
                edge[*it].v = vmap[edge[*it].v];
            }
            calc(i, index);
        }

        FOR(i, m) print(result[i]);
        //print(ts);
    }
}

