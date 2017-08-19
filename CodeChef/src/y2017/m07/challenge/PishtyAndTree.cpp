// Order the queries by increasing K and maintain current XOR to root for all vertices in levels divisible by sqrt(N)
// https://www.codechef.com/JULY17/problems/PSHTTR
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
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

#define MAX_N 100010


// Tree with support for search of a lowest common ancestor (LCA).
#define MAX_NODES MAX_N
#define MAX_LOG_NODES 17

int superH;

struct Node {
    vector<int> neighbor;
    int parent;
    int level;
    int x;
    bool superNode;
    int c;
    vector<int> superChildren;
    vector<int> nextSuper;
};

class LcaTree {
public:
    int totalNodes;
    Node nodes[MAX_NODES];

    // Sets the number of totalNodes and resets all neighbor lists
    void reset(int totalNodes) {
        FOR(i, totalNodes) {
            nodes[i].neighbor.clear();
            nodes[i].x = 0;
            nodes[i].c = 0;
            nodes[i].superNode = false;
            nodes[i].superChildren.clear();
            nodes[i].nextSuper.clear();
        }
        nodes[0].parent = -1;
        this->totalNodes = totalNodes;
    }

    // Adds a single edge to the tree
    void addEdge(int a, int b) {
        nodes[a].neighbor.push_back(b);
        nodes[b].neighbor.push_back(a);
    }

    // Calculates parent and depth for each node using DFS
    void dfs(int node, int previous, int l, int previousSuper) {
        nodes[node].parent = previous;
        nodes[node].level = l;
        if (l % superH == 0) {
            nodes[node].superNode = true;
            if (previousSuper >= 0) nodes[previousSuper].superChildren.push_back(node);
            previousSuper = node;
            int node2 = previous;
            nodes[node].nextSuper.push_back(node);
            while (node2 >= 0 && !nodes[node2].superNode) {
                nodes[node2].nextSuper.push_back(node);
                node2 = nodes[node2].parent;
            }
        }
        FOR(i, nodes[node].neighbor.size())
            if (nodes[node].neighbor[i] != previous)
                dfs(nodes[node].neighbor[i], node, l + 1, previousSuper);
    }

    void distribute(int node, int c) {
        nodes[node].c = c;
        for(auto it = nodes[node].nextSuper.begin(); it != nodes[node].nextSuper.end(); it++)
            dfs2(*it, c);
    }

    void dfs2(int node, int c) {
        nodes[node].x ^= c;
        FOR(i, nodes[node].superChildren.size())
            dfs2(nodes[node].superChildren[i], c);
    }

    int getXor(int node) {
        int result = 0;
        while (!nodes[node].superNode) {
            result ^= nodes[node].c;
            node = nodes[node].parent;
        }
        result ^= nodes[node].x;
        return result;
    }

} lcaTree;

int n;

struct Edge {
    int u, v;
    int c;

    bool operator<(const Edge & other) const {
        return this->c < other.c;
    }
} edge[MAX_N];


struct Query {
    int u, v;
    int k;
    int i;

    bool operator<(const Query & other) const {
        return this->k < other.k;
    }

} query[MAX_N];

int answer[MAX_N];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        superH = sqrt(n) + 1;
        lcaTree.reset(n);
        FOR(i, n - 1) {
            edge[i].u = getInt() - 1;
            edge[i].v = getInt() - 1;
            edge[i].c = getInt();
            lcaTree.addEdge(edge[i].u, edge[i].v);
        }
        lcaTree.dfs(0, -1, 0, -1);
        sort(edge, edge + n - 1);
        int m = getInt();
        FOR(i, m) {
            query[i].u = getInt() - 1;
            query[i].v = getInt() - 1;
            query[i].k = getInt();
            query[i].i = i;
        }
        sort(query, query + m);
        int ep = 0;
        FOR(i, m) {
            while (ep < n - 1 && edge[ep].c <= query[i].k) {
                int u = edge[ep].u;
                int v = edge[ep].v;
                if (lcaTree.nodes[u].level > lcaTree.nodes[v].level) swap(u, v);
                lcaTree.distribute(v, edge[ep].c);
                ep++;
            }
            answer[query[i].i] = lcaTree.getXor(query[i].u) ^ lcaTree.getXor(query[i].v);
        }

        FOR(i, m) print(answer[i]);
    }
}

