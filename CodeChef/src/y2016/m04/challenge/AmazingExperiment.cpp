// When considering a subtree, the node with the minimum strategic cost must be on the longest path to a leaf. Moreover, when going one level up, the node with the minimum strategic cost may only go up as well (or stay the same).
// https://www.codechef.com/APRIL16/problems/AMAEXPER
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

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 100010
struct Node {
    int parent;
    vector<pair<int, int> > children;
    int result;
    int resultBrute;
    int resultNode;
    int depth;
} nodes[MAX_N];

vector<pair<int, int> > neighbor[MAX_N];


int buildTree(int node, int parent) {
    nodes[node].parent = parent;
    int depth = 0;
    for(vector<pair<int, int> >::iterator it = neighbor[node].begin(); it != neighbor[node].end(); it++) {
        if (it->first != parent) {
            nodes[node].children.push_back(*it);
            depth = max(depth, buildTree(it->first, node) + it->second);
        }
    }
    nodes[node].depth = depth;
    return depth;
}

void calc(int node) {
    FOR(i, nodes[node].children.size()) calc(nodes[node].children[i].first);
    if (nodes[node].children.empty()) {
        nodes[node].result = 0;
        nodes[node].resultNode = node;
    } else if (nodes[node].children.size() == 1) {
        int child = nodes[node].children[0].first;
        int resultNode = nodes[child].resultNode;
        int mx = max(nodes[node].depth - nodes[resultNode].depth, nodes[resultNode].depth);
        while (resultNode != node) {
            int parent = nodes[resultNode].parent;
            int localMax = max(nodes[node].depth - nodes[parent].depth, nodes[parent].depth);
            if (localMax > mx) break;
            mx = localMax;
            resultNode = parent;
        }
        // TODO
        nodes[node].result = max(mx, nodes[nodes[node].children[0].first].result);
        nodes[node].resultNode = resultNode;
    } else {
        int mx = 0;
        int mxIndex = -1;
        int mx2 = 0;
        FOR(i, nodes[node].children.size()) {
            pair<int, int> child = nodes[node].children[i];
            int childDepth = nodes[child.first].depth + child.second;
            if (childDepth > mx) {
                mx2 = mx;
                mx = childDepth;
                mxIndex = i;
            } else if (childDepth > mx2) {
                mx2 = childDepth;
            }
        }
        if (mx == mx2) {
            nodes[node].result = mx;
            nodes[node].resultNode = node;
        } else {
            int resultNode = nodes[nodes[node].children[mxIndex].first].resultNode;
            mx = max(nodes[node].depth - nodes[resultNode].depth + mx2, nodes[resultNode].depth);
            while (resultNode != node) {
                int parent = nodes[resultNode].parent;
                int localMax = max(nodes[node].depth - nodes[parent].depth + mx2, nodes[parent].depth);
                if (localMax > mx) break;
                mx = localMax;
                resultNode = parent;
            }
            // TODO
            nodes[node].result = max(mx, nodes[nodes[node].children[mxIndex].first].result);
            nodes[node].resultNode = resultNode;
        }
    }
}

int calcBruteMax(int node, int root, int previous) {
    int res = 0;
    FOR(i, neighbor[node].size()) {
        pair<int, int> nn = neighbor[node][i];
        if (nn.first != previous && (node != root || nn.first != nodes[node].parent))
            res = max(res, calcBruteMax(nn.first, root, node) + nn.second);
    }
    return res;
}

int calcBruteInternal(int node, int root) {
    int res = 1000000010;
    FOR(i, nodes[node].children.size()) res = min(res, calcBruteInternal(nodes[node].children[i].first, root));
    res = min(res, calcBruteMax(node, root, -1));
    return res;
}

void calcBrute(int node) {
    FOR(i, nodes[node].children.size()) calcBrute(nodes[node].children[i].first);
    nodes[node].resultBrute = calcBruteInternal(node, node);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        FOR(i, n) neighbor[i].clear();
        FOR(i, n) nodes[i].children.clear();

        FOR(i, n - 1) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            int w = getInt();
            neighbor[u].push_back(make_pair(v, w));
            neighbor[v].push_back(make_pair(u, w));
        }
        buildTree(0, -1);
        calc(0);
        //calcBrute(0);
        FOR(i, n) print(nodes[i].result);
        /*FOR(i, n) {
            printf("%d %d\n", nodes[i].result, nodes[i].resultBrute);
            if (nodes[i].result != nodes[i].resultBrute) {
                printf("Error\n");
                return 1;
            }
        }*/
    }
}

