// Just an attempt to solve first 2 subtasks
// https://www.codechef.com/SEPT17/problems/WEASELSC
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
#define MAX_K 55
#define INF 1000000
int hist[MAX_N];
int n;
pair<int, int> mins[MAX_N * 4]; // position, value
struct Node {
    int left, right;
    int a, b;
    map<int, LLI> cache;
} nodes[MAX_N * 2];
int totalNodes;

pair<int, int> buildMin(int node, int l, int r) {
    if (l == r) {
        mins[node] = make_pair(l, hist[l]);
    } else {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        auto r1 = buildMin(childNode, l, middle);
        auto r2 = buildMin(childNode + 1, middle + 1, r);
        mins[node] = r1.second <= r2.second ? r1 : r2;
    }
    return mins[node];
}

pair<int, int> getMin(int node, int l, int r, int tl, int tr) {
    if (tl > r || tr < l) return make_pair(-1, INF);
    else {
        if (l >= tl && r <= tr) return mins[node];
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        auto r1 = getMin(childNode, l, middle, tl, tr);
        auto r2 = getMin(childNode + 1, middle + 1, r, tl, tr);
        return r1.second <= r2.second ? r1 : r2;
    }
}


LLI calcValue(int node, int k, int prevHist) {
    if (node < 0) return 0;
    if (nodes[node].a == nodes[node].b) return k > 0 ? hist[nodes[node].a] : prevHist;
    auto cacheValue = nodes[node].cache.insert(make_pair((k << 20) | prevHist, 0));
    if (cacheValue.second) {
        LLI res = calcValue(nodes[node].left, k, prevHist);

        int middle = nodes[node].left >= 0 ? nodes[nodes[node].left].b + 1 : nodes[nodes[node].right].a - 1;
        LLI rr = 0;

        if (prevHist == 0) {
            rr = calcValue(nodes[node].right, k, prevHist);
            if (rr > res) res = rr;
        }


        if (k > 0) {
            if (hist[middle] > prevHist) {
                rr = (middle - nodes[node].a + 1) * (LLI)hist[middle] + calcValue(nodes[node].right, k - 1, hist[middle]);
                if (rr > res) res = rr;
            }
            rr = (middle - nodes[node].a + 1) * (LLI)prevHist + calcValue(nodes[node].right, k, prevHist);
            //printf("Going to right to %d, %lld %lld\n", nodes[node].right, rr, nodes[nodes[node].right].cache[k - 1]);
        } else {
            //rr = (nodes[node].b - nodes[node].a + 1) * (LLI)hist[middle]; // + calcValue(nodes[node].right, k, hist[middle], middle);
            //if (rr > res) res = rr;
            //rr = (middle - prevStart + 1) * (LLI)prevHist ;
            rr = (nodes[node].b - nodes[node].a + 1) * prevHist; // + calcValue(nodes[node].right, k, hist[middle], middle);
        }
        if (rr > res) res = rr;

        cacheValue.first->second = res;
        //nodes[node].cache[k] = res;
        //printf("Node %d: %d-%d (%d), prev: %d, k: %d = %lld\n", node, nodes[node].a, nodes[node].b, middle, prevHist, k, res);
    }
    return cacheValue.first->second;
}

int addNode(int k, int a, int b) {
    nodes[totalNodes].left = nodes[totalNodes].right = -1;
    nodes[totalNodes].a = a;
    nodes[totalNodes].b = b;
    //printf("Setting cache at %d to %d for %d\n", totalNodes, a == b ? hist[a] : -1, k);
    //FOR(i, k + 1) nodes[totalNodes].cache[i] = a == b ? hist[a] : -1;
    nodes[totalNodes].cache.clear();
    return totalNodes++;
}

void buildTree(int node, int a, int b, int k) {
    auto mm = getMin(0, 0, n - 1, a, b);
    if (mm.first > a) {
        nodes[node].left = addNode(k, a, mm.first - 1);
        buildTree(nodes[node].left, a, mm.first - 1, k);
    }
    if (mm.first < b) {
        nodes[node].right = addNode(k, mm.first + 1, b);
        buildTree(nodes[node].right, mm.first + 1, b, k);
    }
}


LLI solve(int k) {
    buildMin(0, 0, n - 1);
    totalNodes = 0;
    buildTree(addNode(k, 0, n - 1), 0, n - 1, k);
    return calcValue(0, k + 1, 0);
}

void reorder() {
    int i = 0;
    int j = n - 1;
    while (i < j) {
        swap(hist[i], hist[j]);
        i++, j--;
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        int k = getInt();
        FOR(i, n) hist[i] = getInt();
        LLI res1 = solve(k);
        reorder();
        LLI res2 = solve(k);
        print(max(res1, res2));
    }
}

