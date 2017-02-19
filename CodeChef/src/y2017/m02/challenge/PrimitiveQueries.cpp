// Brute force solution is sufficient for most cases. If there is a "snake" tree (i.e. a single long chain), use sqrt decomposition to speed up the brute force approach.
// https://www.codechef.com/FEB17/problems/DISTNUM3
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
vector<int> neighbors[MAX_N];

struct Node {
    int v;
    int parent;
} nodes[MAX_N];

int parent[MAX_N][17];
int n;
int depth[MAX_N];
int totalDistinct;
char queryOrder;
char used[MAX_N];
int allValues[MAX_N];
int mappedCount[MAX_N];
int reverseMap[MAX_N];
int snakeValues[MAX_N];
unordered_map<int, int> mapping;
int firstFree;
unordered_set<int> freeValues;

int sqrSize;
int squares[400][400];
int prevPosition[MAX_N];
int nextPosition[MAX_N];
int prevWithSameValue[MAX_N];

void dfs(int node, int parent, int d) {
    nodes[node].parent = parent;
    depth[node] = d;
    FOR(i, neighbors[node].size()) {
        int n = neighbors[node][i];
        if (n != parent) dfs(n, node, d + 1);
    }
}

void fillParents() {
    FOR(i, n) for(int j = 0; (1 << j) < n; j++) parent[i][j] = -1;
    FOR(i, n) parent[i][0] = nodes[i].parent;
    for(int j = 1; (1 << j) < n; j++) FOR(i, n)
        if (parent[i][j - 1] >= 0) parent[i][j] = parent[parent[i][j - 1]][j - 1];
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for(int i = 16; i >= 0; i--) if (depth[a] - (1 << i) >= depth[b]) a = parent[a][i];
    if (a == b) return a;
    for(int i = 16; i >= 0; i--)
        if (parent[a][i] >= 0 && parent[a][i] != parent[b][i]) {
            a = parent[a][i];
            b = parent[b][i];
        }
    return parent[a][0];
}


//LLI totalIterations = 0;

void addDistinct(int start, int end) {
    while (start != end) {
        int vv = nodes[start].v;
        totalDistinct += used[vv] != queryOrder;
        used[vv] = queryOrder;
        //totalDistinct += used[0] != queryOrder;
        start = nodes[start].parent;
    }
}

int calcDistinct(int pos, int maxv) {
    //printf("Calculating %d %d\n", pos, maxv);
    int posSquare = pos / sqrSize;
    int maxVSquare = maxv / sqrSize;
    int result = 0;
    if (posSquare == 0) {
        //printf("Post square is 0: %d\n", pos);
        FORE(i, 0, pos + 1) if (prevWithSameValue[i] <= maxv) result++;
        //printf("Result1: %d\n", result);
    } else if (maxVSquare == 0) {
        FOR(i, posSquare) result += squares[i][0];
        //printf("Result1: %d, Square: %d\n", result, sqrSize);
        //printf("Squares: %d\n", squares[2][1]);
        FORE(i, posSquare * sqrSize, pos + 1) if (prevWithSameValue[i] <= maxv) result++;
        //printf("Result2: %d, Square: %d\n", result, sqrSize);
        //printf("Counting %d\n", maxv + 1 - maxVSquare * sqrSize);
        FORE(i, maxv + 1, sqrSize) if (nextPosition[i] < posSquare * sqrSize && nextPosition[i] != 0) {
            //printf("Adding %d %d\n", i, nextPosition[i]);
            result--;
        }
    } else {
        FOR(i, posSquare) FOR(j, maxVSquare) result += squares[i][j];
        //printf("Result1: %d, Square: %d\n", result, sqrSize);
        //printf("Squares: %d\n", squares[2][1]);
        FORE(i, posSquare * sqrSize, pos + 1) if (prevWithSameValue[i] <= maxv) {
            //printf("Adding at %d\n", i);
            result++;
        }
        //printf("Result2: %d, Square: %d\n", result, sqrSize);
        //printf("Counting %d\n", maxv + 1 - maxVSquare * sqrSize);
        FORE(i, maxVSquare * sqrSize, maxv + 1) if (nextPosition[i] < posSquare * sqrSize && nextPosition[i] != 0) {
            //printf("Adding %d %d\n", i, nextPosition[i]);
            result++;
        }
        //printf("Result3: %d, Square: %d\n", result, sqrSize);
    }
    return result - maxv;
}

void prepareSnake() {
    sqrSize = sqrt(n + 1) + 2;
    FOR(i, n) prevPosition[i] = -1;
    FOR(i, n) {
        int v = snakeValues[i];
        squares[i / sqrSize][(prevPosition[v] + 1) / sqrSize]++;
        prevWithSameValue[i] = prevPosition[v] + 1;
        //printf("Setting nextPosition[%d] to %d\n", prevPosition[v] + 1, i);
        nextPosition[prevPosition[v] + 1] = i;
        prevPosition[v] = i;
    }
}

void updateSnake(int pos, int value) {
    if (snakeValues[pos] != value) {
        //printf("Setting value at pos %d to %d\n", pos, value);
        int origValue = snakeValues[pos];
        int i = pos + 1;
        squares[pos / sqrSize][prevWithSameValue[pos] / sqrSize]--;
        nextPosition[prevWithSameValue[pos]] = 0;

        while (i < n && snakeValues[i] != origValue) i++;
        if (i < n) {
            squares[i / sqrSize][prevWithSameValue[i] / sqrSize]--;
            nextPosition[prevWithSameValue[i]] = 0;

            //printf("1Setting prev at %d to %d\n", i, prevWithSameValue[pos]);
            prevWithSameValue[i] = prevWithSameValue[pos];
            nextPosition[prevWithSameValue[i]] = i;
            squares[i / sqrSize][prevWithSameValue[i] / sqrSize]++;
        }
        i = pos + 1;
        while (i < n && snakeValues[i] != value) i++;
        if (i < n) {
            squares[i / sqrSize][prevWithSameValue[i] / sqrSize]--;
            int origPrev = prevWithSameValue[i];
            nextPosition[prevWithSameValue[i]] = 0;

            prevWithSameValue[i] = pos + 1;
            nextPosition[prevWithSameValue[i]] = i;
            squares[i / sqrSize][prevWithSameValue[i] / sqrSize]++;

            prevWithSameValue[pos] = origPrev;
        } else {
            i = pos - 1;
            while (i >= 0 && snakeValues[i] != value) i--;
            prevWithSameValue[pos] = i + 1;
        }
        //printf("Prevwithsamevalue = %d\n", prevWithSameValue[pos]);
        nextPosition[prevWithSameValue[pos]] = pos;
        squares[pos / sqrSize][prevWithSameValue[pos] / sqrSize]++;
        snakeValues[pos] = value;
    }
}


int main(void) {
    n = getInt();
    int q = getInt();
    FOR(i, n) allValues[i] = nodes[i].v = getInt();
    FOR(i, n - 1) {
        int u = getInt() - 1;
        int v = getInt() - 1;
        neighbors[u].push_back(v);
        neighbors[v].push_back(u);
    }
    bool snake = true;
    FOR(i, n) if (neighbors[i].size() > 2) { snake = false; break; }
    if (snake) {
        int first = -1;
        FOR(i, n) if (neighbors[i].size() == 1) { first = i; break;}
        dfs(first, -1, 0);
    } else dfs(0, -1, 0);
    fillParents();
    sort(allValues, allValues + n);
    int lastValue = allValues[0];
    int cc = 0;
    int ss;
    FOR(i, n) {
        if (allValues[i] != lastValue) {
            mappedCount[mapping.size()] = cc;
            reverseMap[mapping.size()] = allValues[i - 1];
            ss = mapping.size();
            mapping[allValues[i - 1]] = ss;
            lastValue = allValues[i];
            cc = 0;
        }
        cc++;
    }
    mappedCount[mapping.size()] = cc;
    reverseMap[mapping.size()] = allValues[n - 1];
    ss = mapping.size();
    mapping[allValues[n - 1]] = ss;

    firstFree = mapping.size();
    FOR(i, n) snakeValues[depth[i]] = nodes[i].v = mapping[nodes[i].v];
    if (snake) {
        prepareSnake();
    }

    FOR(i, q) {
        int op = getInt();
        int u = getInt() - 1;
        int v = getInt();
        if (op == 1) {
            queryOrder++;
            if (queryOrder >= 100) {
                queryOrder = 1;
                memset(used, 0, n);
            }
            // find
            v--;
            totalDistinct = 0;
            if (snake) {
                int i1 = depth[u];
                int i2 = depth[v];
                if (i1 > i2) swap(i1, i2);
                totalDistinct = calcDistinct(i2, i1);
            } else {
                int ll = lca(u, v);
                if (depth[u] - depth[ll] + depth[v] - depth[ll] + 1 == n) {
                    totalDistinct = mapping.size();
                } else {
                    ll = nodes[ll].parent;
                    addDistinct(u, ll);
                    addDistinct(v, ll);
                }
            }

            print(totalDistinct);
        } else {
            // update
            if (--mappedCount[nodes[u].v] == 0) {
                freeValues.insert(nodes[u].v);
                mapping.erase(reverseMap[nodes[u].v]);
            }
            auto it = mapping.find(v);
            if (it == mapping.end()) {
                int mappedValue;
                if (!freeValues.empty()) {
                    auto it2 = freeValues.begin();
                    mappedValue = *it2;
                    freeValues.erase(it2);
                } else {
                    mappedValue = firstFree++;
                }
                it = mapping.insert(make_pair(v, mappedValue)).first;
                reverseMap[mappedValue] = v;
                mappedCount[mappedValue] = 0;
            }
            mappedCount[it->second]++;
            nodes[u].v = it->second;
            if (snake) updateSnake(depth[u], it->second);
        }

    }
}

