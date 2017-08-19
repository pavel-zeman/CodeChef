// Description
// URL
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

#define MAX_N 10010
int n, m;
int cost[MAX_N];
vector<int> neighbor[MAX_N];
bool used[MAX_N];
bool visited[MAX_N];


bool isCycle(int node, int prev) {
    if (visited[node]) return true;
    visited[node] = true;
    for(auto it = neighbor[node].begin(); it != neighbor[node].end(); it++) {
        if (*it != prev && used[*it]) {
            if (isCycle(*it, node)) return true;
        }
    }
    return false;
}

bool isConnected() {
    FOR(i, n) if (used[i] && !visited[i]) return false;
    return true;
}

void solveSmall() {
    int mx = 1 << n;
    int minCost = 0;
    int minCostSetup = 0;
    FOR(i, n) minCost += cost[i];
    FORE(i, 1, mx) {
        int t = i;
        int curCost = 0;
        FOR(j, n) {
            if ((t & 1) == 0) {
                used[j] = false;
                curCost += cost[j];
            } else used[j] = true;
            t >>= 1;
        }
        if (curCost < minCost) {
            FOR(j, n) visited[j] = false;
            int firstUsed = 0;
            while (!used[firstUsed]) firstUsed++;
            if (!isCycle(firstUsed, -1) && isConnected()) {
                minCost = curCost;
                minCostSetup = i;
            }
        }
    }
    vector<int> notUsed;
    FOR(j, n) {
        if ((minCostSetup & 1) == 0) notUsed.push_back(j);
        minCostSetup >>= 1;
    }
    print(notUsed.size());
    FOR(i, notUsed.size()) print(notUsed[i] + 1);
}


int almostNode;
bool current[MAX_N];
int prevNode[MAX_N];

int getSize(int node) {
    int res = 0;
    FOR(i, neighbor[node].size()) if (used[neighbor[node][i]]) res++;
    return res;
}

bool findCycle(int node, int prev) {
    if (visited[node]) {
        vector<int> cycleNodes;
        int n2 = node;
        while (!current[n2]) {
            cycleNodes.push_back(n2);
            n2 = prevNode[n2];
        }
        int n3 = prev;
        while (n3 != n2) {
            cycleNodes.push_back(n3);
            n3 = prevNode[n3];
        }
        cycleNodes.push_back(n3);
        int minCost = 1000000000;
        almostNode = -1;
        FOR(i, cycleNodes.size()) {
            int n4 = cycleNodes[i];
            if (getSize(n4) < 3 && cost[n4] < minCost) {
                minCost = cost[n4];
                almostNode = n4;
            }
        }
        return true;
    } else {
        prevNode[node] = prev;
        current[node] = true;
        visited[node] = true;
        for(auto it = neighbor[node].begin(); it != neighbor[node].end(); it++) {
            if (*it != prev && used[*it]) {
                if (findCycle(*it, node)) return true;
            }
        }
        current[node] = false;
        return false;
    }
}


void solveAlmostTree() {
    FOR(i, n) used[i] = true;
    vector<int> res;
    while (findCycle(0, -1)) {
        res.push_back(almostNode);
        used[almostNode] = false;
        FOR(i, n) visited[i] = current[i] = false;
        //printf("Removed %d\n", almostNode);
    }
    print(res.size());
    FOR(i, res.size()) print(res[i] + 1);
}

void solveComplete() {
    int minCost1 = 0, minCost1Pos = -1;
    int minCost2 = 0, minCost2Pos = -1;
    FOR(i, n) if (cost[i] > minCost1) {
        minCost1 = cost[i];
        minCost1Pos = i;
    }
    FOR(i, n) if (i != minCost1Pos && cost[i] > minCost2) {
        minCost2 = cost[i];
        minCost2Pos = i;
    }
    print(n - 2);
    FOR(i, n) if (i != minCost1Pos && i != minCost2Pos) print(i + 1);
}

int isWheel() {
    if (m != 2 * (n - 1)) return -1;
    int center = -1;
    FOR(i, n) if ((int)neighbor[i].size() == n - 1) {
        center = i;
        break;
    }
    if (center < 0) return -1;
    FOR(i, n) if (i != center && neighbor[i].size() != 3) return -1;
    return center;
}

void solveWheel() {
    int center = isWheel();
    vector<int> res;
    res.push_back(center);
    int minCost = 1000000000;
    int minCostPos = -1;
    FOR(i, n) if (i != center && cost[i] < minCost) {
        minCost = cost[i];
        minCostPos = i;
    }
    res.push_back(minCostPos);
    print(2);
    FOR(i, res.size()) print(res[i] + 1);
    // TODO Remove other vertices
}

int main(void) {
    n = getInt();
    m = getInt();
    FOR(i, n) cost[i] = getInt();
    FOR(i, m) {
        int u = getInt() - 1;
        int v = getInt() - 1;
        neighbor[u].push_back(v);
        neighbor[v].push_back(u);
    }
    if (n <= 25) solveSmall();
    else if (m <= n + 3) solveAlmostTree();
    else if (m == n * (n - 1) / 2) solveComplete();
    else if (isWheel() >= 0) solveWheel();
    else {
        auto maxEl = max_element(cost, cost + n);
        int maxPos = maxEl - cost;
        print(n - 1);
        FOR(i, n) if (i != maxPos) print(i + 1);
    }
}

