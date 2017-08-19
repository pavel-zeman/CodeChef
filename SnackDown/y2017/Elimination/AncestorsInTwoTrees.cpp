// Description
// https://www.codechef.com/SNCKEL17/problems/ANCESTOR
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


// Tree with support for search of a lowest common ancestor (LCA).
#define MAX_NODES 500010
#define MAX_LOG_NODES 21

class LcaTree {
public:
    vector<int> neighbor[MAX_NODES];
    int nodes;
    int parent[MAX_NODES];
    int level[MAX_NODES];
    int genericParent[MAX_LOG_NODES][MAX_NODES];

    // Sets the number of nodes and resets all neighbor lists
    void reset(int nodes) {
        FOR(i, nodes) neighbor[i].clear();
        this->nodes = nodes;
    }

    // Adds a single edge to the tree
    void addEdge(int a, int b) {
        neighbor[a].push_back(b);
        neighbor[b].push_back(a);
    }

    // Calculates parent and depth for each node using DFS
    void dfs(int node, int previous, int l) {
        parent[node] = previous;
        level[node] = l;
        FOR(i, neighbor[node].size())
            if (neighbor[node][i] != previous)
                dfs(neighbor[node][i], node, l + 1);
    }


    // Prepares structures needed for the LCA (including DFS)
    void prepareLca() {
        dfs(0, -1, 0);

        for(int j=0;1<<j < nodes;j++)
            FOR(i, nodes)
                genericParent[j][i] = -1;

        FOR(i, nodes) genericParent[0][i] = parent[i];

        for(int j=1; 1<<j < nodes; j++)
            FOR(i, nodes)
                if (genericParent[j - 1][i] != -1)
                    genericParent[j][i] = genericParent[j - 1][genericParent[j - 1][i]];
    }

    // Calculates LCA
    int lca(int p, int q) {
        int tmp, log, i;

        if (level[p] < level[q]) tmp = p, p = q, q = tmp;

        for (log = 1; 1 << log <= level[p]; log++);
        log--;

        for (i = log; i >= 0; i--)
            if (level[p] - (1 << i) >= level[q])
                p = genericParent[i][p];

        if (p == q) return p;

        for (i = log; i >= 0; i--)
            if (genericParent[i][p] != -1 && genericParent[i][p] != genericParent[i][q])
                p = genericParent[i][p], q = genericParent[i][q];

        return parent[p];
    }
} tree1, tree2;


int res[MAX_NODES];



void dfs(int node, int previous, int common) {
    res[node] = common;
    FOR(i, tree1.neighbor[node].size())
        if (tree1.neighbor[node][i] != previous) {
            int lca = tree2.lca(tree1.neighbor[node][i], node);
            dfs(tree1.neighbor[node][i], node, common + (lca == node ? 1 : 0));
       }
}



int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        tree1.reset(n);
        tree2.reset(n);
        FOR(i, n - 1) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            tree1.addEdge(u, v);
        }
        FOR(i, n - 1) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            tree2.addEdge(u, v);
        }
        tree2.prepareLca();
        dfs(0, -1, 0);
        FOR(i, n) printf("%d ", res[i]);
        printf("\n");
    }
}

