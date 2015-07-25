// Tree with support for search of a lowest common ancestor (LCA).
#define MAX_NODES 100010
#define MAX_LOG_NODES 17

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
} lcaTree;
