// Recursion for each combination of node and heavy segment length, which is a parent of this node. To speed-up the recursion, we maintain vector of all different results for each node based on heavy segment length.
// https://www.codechef.com/APRIL17/problems/HLD
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
vector<int> neighbors2[MAX_N];

vector<pair<int, int> > resCache[MAX_N];

void fillNeighbors2(int node, int prevNode) {
    if (neighbors[node].size() == 1 && node != 0) return;
    FOR(i, neighbors[node].size())
        if (neighbors[node][i] != prevNode) {
            neighbors2[node].push_back(neighbors[node][i]);
            fillNeighbors2(neighbors[node][i], node);
        }
}

int findCache(int node, int heavySegments, int lastPos) {
    int s = resCache[node].size();
    FORE(i, lastPos, s)
        if (resCache[node][i].first > heavySegments) return i - 1;
    return s - 1;
}

void insertCache(int node, int heavySegments, int value) {
    int s = resCache[node].size();
    FOR(i, s)
        if (resCache[node][i].first > heavySegments) {
            resCache[node].insert(resCache[node].begin() + i, make_pair(heavySegments, value));
            return;
        }
    resCache[node].push_back(make_pair(heavySegments, value));
}

void solveInternal(int node, int child, int mx1, int depth) {
    int last = -1;
    int cs = resCache[child].size();
    int lastIndex = -1;
    int lastPos = 0;
    FOR(i, cs) {
        FORE(j, resCache[child][i].first - 1, resCache[child][i].first + 2) {
            if (j > lastIndex && j <= depth) {
                int segmentAdd = j == 0 || (j & (j - 1)) == 0 ? 1 : 0;
                lastPos = findCache(child, j + 1, lastPos);
                int l = max(resCache[child][lastPos].second + segmentAdd, mx1);
                if (l != last) {
                    last = l;
                    resCache[node].push_back(make_pair(j, last));
                }
                lastIndex = j;
            }
        }
    }
    int pp = 1;
    lastIndex = -1;
    lastPos = 0;
    int newPos = 0;
    while (pp <= depth) {
        FORE(j, pp, pp + 2) {
            if (j > lastIndex && j <= depth) {
                int segmentAdd = j == 0 || (j & (j - 1)) == 0 ? 1 : 0;
                lastPos = findCache(child, j + 1, lastPos);
                int l = max(resCache[child][lastPos].second + segmentAdd, mx1);
                newPos = findCache(node, j, newPos);
                if (resCache[node][newPos].second != l) insertCache(node, j, l);
                lastIndex = j;
            }
        }
        pp <<= 1;
    }

}


int solve(int node, int prevNode, int depth) {
    if (neighbors2[node].size() == 0) resCache[node].push_back(make_pair(0, 0));
    else {
        if (neighbors2[node].size() == 1) {
            int child = neighbors2[node][0];
            solve(child, node, depth + 1);
            solveInternal(node, child, 0, depth);
       } else {
            int mx1 = 0;
            int mx2 = 0;
            int mx2Pos = 0;
            FOR(i, neighbors2[node].size()) {
                int ll = solve(neighbors2[node][i], node, depth + 1) + 1;
                if (ll > mx2) {
                    mx1 = mx2;
                    mx2 = ll;
                    mx2Pos = i;
                } else if (ll > mx1) {
                    mx1 = ll;
                }
            }

            if (mx2 == mx1) resCache[node].push_back(make_pair(0, mx1));
            else solveInternal(node, neighbors2[node][mx2Pos], mx1, depth);
        }
    }
    return resCache[node][0].second;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        FOR(i, n) neighbors[i].clear();
        FOR(i, n) neighbors2[i].clear();
        FOR(i, n - 1) {
            int a = getInt() - 1;
            int b = getInt() - 1;
            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }
        FOR(x, 1) {
            FOR(i, n) neighbors2[i].clear();
            FOR(i, n) resCache[i].clear();
            fillNeighbors2(0, -1);
            print(solve(0, -1, 0));
            /*FOR(i, n) {
                printf("%d ", i);
                for(auto it = resCache[i].begin(); it != resCache[i].end(); it++) {
                    printf("(%d, %d), ", it->first, it->second);
                }
                printf("\n");
            }*/

        }
    }
}

