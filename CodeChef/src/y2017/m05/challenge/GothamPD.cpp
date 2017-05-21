// Use trie to find min/max xor, store the trie in every node with depth, which is a power of 2 greater than 8
// https://www.codechef.com/MAY17/problems/GPD
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

#define MAX_N 300010

struct Pp {
    int v[2];

    Pp(int a, int b) {
        v[0] = a;
        v[1] = b;
    }
};

struct Node {
    int parent;
    int key;
    int depth;
    vector<Pp> trie;
    int trieParent;
} nodes[MAX_N];

int totalNodes;
unordered_map<int, int> nodeMapping;

void addNode(int node, int parent, int k) {
    int parentIndex = nodeMapping[parent];
    nodes[totalNodes].parent = parentIndex;
    nodes[totalNodes].key = k;
    int depth = nodes[parentIndex].depth + 1;
    nodes[totalNodes].depth = depth;
    nodeMapping[node] = totalNodes;
    if ((depth & ((1 << 8) - 1)) == 0) {
        int numZeros = 0;
        while ((depth & 1) == 0) depth >>= 1, numZeros++;
        int diff = 1 << numZeros;
        nodes[totalNodes].trie.push_back(Pp(0, 0));
        int prevNode = totalNodes;
        FOR(i, diff) {
            int bit = 1 << 30;
            int triePos = 0;
            int k = nodes[prevNode].key;
            while (bit > 0) {
                Pp l = nodes[totalNodes].trie[triePos];
                int b = (k & bit) == 0 ? 0 : 1;
                if (l.v[b] == 0) {
                    int newPos = nodes[totalNodes].trie.size();
                    nodes[totalNodes].trie.push_back(Pp(0, 0));
                    nodes[totalNodes].trie[triePos].v[b] = newPos;
                    triePos = newPos;
                } else triePos = l.v[b];
                bit >>= 1;
            }
            prevNode = nodes[prevNode].parent;
        }
        nodes[totalNodes].trieParent = prevNode;
    }
    totalNodes++;
}

int findMinMax(int node, int k, int var) {
    int pos = 0;
    int v = 0;
    int bit = 1 << 30;
    while (bit > 0) {
        int b = (k & bit) == 0 ? 0 : 1;
        int path = b ^ var;
        bit >>= 1;
        if (nodes[node].trie[pos].v[path] == 0) path ^= 1;
        v <<= 1;
        v |= b ^ path;
        pos = nodes[node].trie[pos].v[path];
    }
    return v;
}


pair<int, int> findMM(int v, int k) {
    int index = nodeMapping[v];
    int mn = nodes[0].key ^ k;
    int mx = mn;
    while (index > 0) {
        if (nodes[index].trie.size() > 0) {
            int v = findMinMax(index, k, 0);
            if (v < mn) mn = v;
            v = findMinMax(index, k, 1);
            if (v > mx) mx = v;
            index = nodes[index].trieParent;
        } else {
            int v = nodes[index].key ^ k;
            if (v > mx) mx = v;
            if (v < mn) mn = v;
            index = nodes[index].parent;
        }
    }
    return make_pair(mn, mx);
}

int main(void) {
    int n = getInt();
    int q = getInt();
    int r = getInt();
    nodes[0].key = getInt();
    nodes[0].parent = -1;
    nodes[0].depth = 0;
    nodes[0].trie.push_back(Pp(0, 0));
    nodeMapping[r] = 0;
    totalNodes = 1;
    FOR(i, n - 1) {
        int u = getInt();
        int v = getInt();
        int k = getInt();
        addNode(u, v, k);
    }
    int la = 0;
    FOR(i, q) {
        int t = getInt();
        t ^= la;
        if (t == 0) {
            int v = getInt();
            int u = getInt();
            int k = getInt();
            u ^= la;
            v ^= la;
            k ^= la;
            addNode(u, v, k);
        } else {
            int v = getInt();
            int k = getInt();
            v ^= la;
            k ^= la;
            pair<int, int> r = findMM(v, k);
            print(r.first);
            print(r.second);
            la = r.first ^ r.second;
        }
    }
}
