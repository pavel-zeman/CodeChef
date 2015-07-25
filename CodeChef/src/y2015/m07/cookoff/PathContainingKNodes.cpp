// The path must start at some "left" node, have a root and end at some "right" node. Use an incremental algorithm to maintain these nodes using LCA.
// https://www.codechef.com/COOK60/problems/KNODES
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


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

void printString(const char *s) {
    while (*s) putc_unlocked(*s++, stdout);
    putc_unlocked('\n', stdout);
}

void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}

#define MAX_NODES 100010
#define MAX_LOG_NODES 17

class LcaTree {
public:
    vector<int> neighbor[MAX_NODES];
    int nodes;
    int parent[MAX_NODES];
    int level[MAX_NODES];
    int genericParent[MAX_LOG_NODES][MAX_NODES];

    void reset(int nodes) {
        FOR(i, nodes) neighbor[i].clear();
        this->nodes = nodes;
    }

    void addEdge(int a, int b) {
        neighbor[a].push_back(b);
        neighbor[b].push_back(a);
    }

    void dfs(int node, int previous, int l) {
        parent[node] = previous;
        level[node] = l;
        FOR(i, neighbor[node].size())
            if (neighbor[node][i] != previous)
                dfs(neighbor[node][i], node, l + 1);
    }


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


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        lcaTree.reset(n);
        FOR(i, n - 1) {
            int a = getInt() - 1;
            int b = getInt() - 1;
            lcaTree.addEdge(a, b);
        }

        lcaTree.prepareLca();

        int q = getInt();
        FOR(i, q) {
            bool possible = true;
            int k = getInt();

            int l = -1, r = -1, m = -1;
            l = getInt() - 1;
            k--;
            int tmp = getInt() - 1;
            k--;
            int tmpLca = lcaTree.lca(l, tmp);
            if (tmpLca == l || tmpLca == tmp) {
                m = tmpLca;
                if (tmpLca == l) l = tmp;
                while (k-- > 0) {
                    tmp = getInt() - 1;
                    tmpLca = lcaTree.lca(l, tmp);
                    if (tmpLca == l) l = tmp;
                    else if (tmpLca == tmp) m = lcaTree.lca(tmp, m);
                    else {
                        if (lcaTree.level[tmpLca] > lcaTree.level[m]) {
                            possible = false;
                            goto end;
                        } else {
                            m = tmpLca;
                            r = tmp;
                            break;
                        }
                    }
                }
            } else {
                m = tmpLca;
                r = tmp;
            }
            while (k-- > 0) {
                tmp = getInt() - 1;
                int lcaL = lcaTree.lca(l, tmp);
                int lcaR = lcaTree.lca(r, tmp);
                if (lcaL == l) l = tmp;
                else if (lcaR == r) r = tmp;
                else {
                    int lcaM = lcaTree.lca(m, tmp);
                    if ((lcaL == tmp || lcaR == tmp) && lcaM == m) { /* nothing */ }
                    else {
                        possible = false;
                        break;
                    }
                }
            }

            end:
            while (k-- > 0) getInt();
            printString(possible ? "Yes" : "No");
        }
    }
}

