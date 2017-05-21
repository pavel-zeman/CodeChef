// Recursively calculate minimum cost for each subtree, when the root of the subtree is painted with the color of each node in the subtree.
// https://www.codechef.com/MAY17/problems/KILLER
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

LLI getSignedLongLongInt() {
    LLI r = 0;
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
#define MAX_C 100010
#define MAX_LOG_H 17
int h;
int n;

struct Node {;
    vector<int> neighbors;
    LLI res;
    int resC;
    vector<pair<int, LLI> > resMap;
    LLI h;
    int c;
    LLI c2;
    int parent[MAX_LOG_H];
    int lastCalculatedDepth;
    int lastCalculatedNode;
    LLI lastValue;
    LLI childSum;
} nodes[MAX_N];
bool ok[MAX_N];

int maxs;

struct Cq {
    vector<int> data;
    int first, firstEmpty;

    Cq() {
        first = firstEmpty = 0;
    }

    void push(int v) {
        if (firstEmpty < (int)data.size()) data[firstEmpty] = v;
        else data.push_back(v);
        firstEmpty++;
    }

    int front() {
        return data[first];
    }

    void pop() {
        first++;
    }

    void clear() {
        first = firstEmpty = 0;
    }

    int size() {
        return data.size() - first;
    }
};

Cq currentNodes[MAX_N];
int segmentData[MAX_N * 3];
pair<int, LLI> v1[MAX_N];
int v1Size;
vector<int> todo[MAX_N];

LLI getValue(int node, int depth) {
    return nodes[node].c2 + nodes[node].c * (LLI)(h - depth);
}

int clr(int node, int parent, int depth) {
    nodes[node].parent[0] = parent;
    int x = 2;
    FORE(i, 1, MAX_LOG_H) {
        if (x <= depth) {
            nodes[node].parent[i] = nodes[nodes[node].parent[i - 1]].parent[i - 1];
        } else break;
        x <<= 1;
    }
    for(auto it = nodes[node].neighbors.begin(); it != nodes[node].neighbors.end(); it++)
        if (*it == parent) {
            nodes[node].neighbors.erase(it);
            break;
        }
    int d = 0;
    for(auto it = nodes[node].neighbors.begin(); it != nodes[node].neighbors.end(); it++) d = max(d, clr(*it, node, depth + 1) + 1);
    return d;
}

void updateSegment(int segNode, int a, int b, int target, int v) {
    segmentData[segNode] += v;
    if (a != b) {
        int mid = (a + b) >> 1;
        if (target <= mid) updateSegment(segNode * 2 + 1, a, mid, target, v);
        else updateSegment(segNode * 2 + 2, mid + 1, b, target, v);
    }
}

void removeSegments(int segNode, int a, int b, int mn) {
    if (mn <= b && segmentData[segNode] > 0) {
        if (a == b) {
            segmentData[segNode] = 0;
            FOR(i, currentNodes[a].size()) {
                ok[currentNodes[a].front()] = false;
                currentNodes[a].pop();
            }
            currentNodes[a].clear();
        } else {
            int mid = (a + b) >> 1;
            removeSegments(segNode * 2 + 1, a, mid, mn);
            removeSegments(segNode * 2 + 2, mid + 1, b, mn);
            segmentData[segNode] = segmentData[segNode * 2 + 1] + segmentData[segNode * 2 + 2];
        }

    }
}

bool compare(pair<int, LLI> a, pair<int, LLI> b) {
    return a.second < b.second || (a.second == b.second && nodes[a.first].c < nodes[b.first].c);
}

// v1 < v2
int getNextPosition(int c1, LLI v1, int c2, LLI v2, int inh) {
    int curH = h - inh;
    double a = (c1 - c2) / 2.0;
    double b = (curH + 1/2.0) * (c1 - c2) + c1 * (LLI)c1 - c2 * (LLI)c2;
    double c = -(v2 - v1);
    double r = (-b + sqrt(b * b - 4 * a * c)) / 2 / a - 1;
    if (r < 0) return inh;
    if (r > inh) return -1;
    return inh - r;
}

void calc(int node, int depth) {
    if (nodes[node].neighbors.empty()) {
        LLI v = getValue(node, depth) + nodes[node].h;
        nodes[node].res = v;
        nodes[node].resMap.push_back(make_pair(node, v));
    } else {
        for(auto it = nodes[node].neighbors.begin(); it != nodes[node].neighbors.end(); it++) calc(*it, depth + 1);
        LLI childSum = 0;
        for(auto it = nodes[node].neighbors.begin(); it != nodes[node].neighbors.end(); it++) childSum += nodes[*it].res;
        LLI res = childSum + getValue(node, depth) + nodes[node].h;
        int bestC = nodes[node].c;
        LLI bestV = res;
        nodes[node].lastCalculatedDepth = depth;
        nodes[node].lastCalculatedNode = node;
        nodes[node].lastValue = res;
        nodes[node].childSum = childSum;
        v1Size = 0;
        v1[v1Size++] = make_pair(node, res);
        for(auto it = nodes[node].neighbors.begin(); it != nodes[node].neighbors.end(); it++) {
            childSum -= nodes[*it].res;
            for(auto it2 = nodes[*it].resMap.begin(); it2 != nodes[*it].resMap.end(); it2++) {
                LLI v = childSum + it2->second + getValue(it2->first, depth);
                nodes[it2->first].lastCalculatedDepth = depth;
                nodes[it2->first].lastValue = v;
                nodes[it2->first].lastCalculatedNode = node;
                if (nodes[it2->first].c >= bestC && v >= bestV) {
                    // do nothing
                } else {
                    v1[v1Size++] = make_pair(it2->first, v);
                    if (v < res) res = v;
                    if (nodes[it2->first].c <= bestC && v <= bestV) {
                        bestC = nodes[it2->first].c;
                        bestV = v;
                    }
                }
            }
            childSum += nodes[*it].res;
            nodes[*it].resMap.clear();
        }
        for(auto it = todo[depth].begin(); it != todo[depth].end(); it++) {
            int d2 = nodes[*it].lastCalculatedDepth;
            LLI v = nodes[*it].lastValue;
            int n2 = nodes[*it].lastCalculatedNode;
            bool ok = true;
            while (--d2 >= depth) {
                int n3 = nodes[n2].parent[0];
                v += nodes[n3].childSum - nodes[n2].res + getValue(*it, d2);
                n2 = n3;
                if (n2 != node && nodes[n2].res <= v && nodes[n2].resC <= nodes[*it].c) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                nodes[*it].lastCalculatedDepth = depth;
                nodes[*it].lastValue = v;
                nodes[*it].lastCalculatedNode = node;
                if (nodes[*it].c >= bestC && v >= bestV) {
                    // do nothing
                } else {
                    v1[v1Size++] = make_pair(*it, v);
                    if (v < res) res = v;
                    if (nodes[*it].c <= bestC && v <= bestV) {
                        bestC = nodes[*it].c;
                        bestV = v;
                    }
                }
            }
        }
        todo[depth].clear();
        if (node > 0) {
            FOR(i, v1Size) ok[i] = true;
            if (v1Size <= 50) {
                int bestC = MAX_C;
                FOR(i, v1Size) {
                    FORE(j, i + 1, v1Size) {
                        if (ok[j] && nodes[v1[i].first].c <= nodes[v1[j].first].c && v1[i].second <= v1[j].second) ok[j] = false;
                        else if (ok[i] && nodes[v1[i].first].c >= nodes[v1[j].first].c && v1[i].second >= v1[j].second) {
                            ok[i] = false;
                            break;
                        }
                    }
                    if (ok[i] && v1[i].second == res) bestC = nodes[v1[i].first].c;
                }
                nodes[node].resC = bestC;
                FOR(i, v1Size) if (ok[i]) {
                    if (v1[i].second == res)
                        nodes[node].resMap.push_back(v1[i]);
                    else {
                        int nextPosition = getNextPosition(bestC, res, nodes[v1[i].first].c, v1[i].second, depth);
                        if (nextPosition >= depth - 1) nodes[node].resMap.push_back(v1[i]);
                        else if (nextPosition >= 0) todo[nextPosition].push_back(v1[i].first);
                    }
                }
            } else {
                sort(v1, v1 + v1Size, compare);
                int bestC = nodes[v1[0].first].c;
                nodes[node].resC = bestC;
                FOR(i, v1Size) {
                    currentNodes[nodes[v1[i].first].c].push(i);
                    updateSegment(0, 0, MAX_C, nodes[v1[i].first].c, 1);
                }
                nodes[node].resMap.reserve(v1Size);
                FOR(i, v1Size) if (ok[i]) {
                    currentNodes[nodes[v1[i].first].c].pop();
                    updateSegment(0, 0, MAX_C, nodes[v1[i].first].c, -1);
                    removeSegments(0, 0, MAX_C, nodes[v1[i].first].c);
                    if (v1[i].second == res)
                        nodes[node].resMap.push_back(v1[i]);
                    else {
                        int nextPosition = getNextPosition(bestC, res, nodes[v1[i].first].c, v1[i].second, depth);
                        if (nextPosition >= depth - 1) nodes[node].resMap.push_back(v1[i]);
                        else if (nextPosition >= 0) todo[nextPosition].push_back(v1[i].first);
                    }
                }
            }
        }
        nodes[node].res = res;
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) {
            nodes[i].h = -getSignedLongLongInt();
            nodes[i].c = getInt();
            nodes[i].c2 = nodes[i].c * (LLI)nodes[i].c;
        }
        FOR(i, n) nodes[i].neighbors.clear(), nodes[i].resMap.clear();
        FOR(i, n - 1) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            nodes[u].neighbors.push_back(v);
            nodes[v].neighbors.push_back(u);
        }
        h = clr(0, -1, 0);
        calc(0, 0);
        print(nodes[0].res);
    }
}

