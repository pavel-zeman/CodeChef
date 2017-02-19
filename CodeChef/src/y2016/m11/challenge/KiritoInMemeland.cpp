// Traverse the tree while accumulating partial results in a vector (i-th element of the vector represents number of routes with exactly i "spikes")
// https://www.codechef.com/NOV16/problems/KIRMEME
#include <bits/stdc++.h>
#include <sys/resource.h>
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

typedef vector<int> mm;

#define MAX_N 50010
int a[MAX_N];
vector<int> neighbors[MAX_N];
unsigned int result;
int parent[MAX_N];
int l, r;


void ensureSize(mm &v, int s) {
    int origSize = v.size();
    if (origSize < s) {
        int toAdd = s - origSize;
        v.resize(s, 0);
        for(int i = s - 1; i >= toAdd; i--) v[i] = v[i - toAdd];
        FOR(i, toAdd) v[i] = 0;
    }
}

void add(mm &dst, mm &src) {
    if (dst.empty()) {
        dst = src;
    }  else if (dst.size() == 1) {
        int x = dst[0];
        dst = src;
        ensureSize(dst, 1);
        dst[dst.size() - 1] += x;
    } else {
        ensureSize(dst, src.size());
        FOR(i, src.size()) dst[dst.size() - (src.size() - i)] += src[i];
    }
}


pair<mm, mm> solve(int node, int previous, mm down, mm up) {
    int stepsDown = 0;
    parent[node] = previous;
    if (previous >= 0) {
        if (a[previous] > a[node]) {
            // Going down
            up.push_back(0);
            add(down, up);
            up.clear();
        } else if (a[previous] < a[node]) {
            // Going up
            add(up, down);
            down.clear();
        } else {
            // Equal
            add(down, up);
            up.clear();
        }
        int localResult = 0;
        FOR(i, down.size()) {
            int x = down.size() - 1 - i;
            if (x >= l && x <= r) localResult += down[i];
        }
        FOR(i, up.size()) {
            int x = up.size() - 1 - i;
            if (x >= l && x <= r) localResult += up[i];
        }

        if (neighbors[node].size() == 2) {
            int xResult = localResult;
            mm *pDown = &down;
            mm *pUp = &up;
            a:
            int nextNode = neighbors[node][0];
            if (nextNode == previous) nextNode = neighbors[node][1];
            ensureSize(*pDown, 1);
            (*pDown)[pDown->size() - 1]++;
            previous = node;
            node = nextNode;
            stepsDown++;
            parent[node] = previous;

            if (a[previous] > a[node]) {
                // Going down
                if (!pUp->empty()) {
                    pUp->push_back(1);
                    if ((int)pUp->size() >= l + 1) xResult += (*pUp)[pUp->size() - l - 1];
                    if ((int)pUp->size() >= r + 2) xResult -= (*pUp)[pUp->size() - r - 2];
                    swap(pUp, pDown);
                    pUp->clear();
                }
            } else if (a[previous] < a[node]) {
                // Going up
                if (pUp->empty()) swap(pUp, pDown);
                else {
                    add(*pUp, *pDown);
                    pDown->clear();
                }
            } else {
                // Equal
                if (!pUp->empty()) {
                    add(*pUp, *pDown);
                    swap(pUp, pDown);
                    pUp->clear();
                }
            }
            localResult += xResult;

            if (neighbors[node].size() == 2) goto a;
            if (pUp != &up) {
                if (pUp->empty()) {
                    down = up;
                    up.clear();
                } else {
                    up = down;
                    down.clear();
                }
            }
        }
        result += localResult;
    }
    mm resultUp;
    mm resultDown;
    ensureSize(down, 1);
    ensureSize(resultDown, 1);
    down[down.size() - 1]++;
    resultDown[0]++;

    FOR(i, neighbors[node].size()) {
        int neighbor = neighbors[node][i];
        if (neighbor != previous) {
            pair<mm, mm> r = solve(neighbor, node, down, up);

            if (a[node] > a[neighbor]) {
                // Going up (from son)
                add(up, r.first);
                add(resultUp, r.first);
                add(up, r.second);
                add(resultUp, r.second);
            } else if (a[node] < a[neighbor]) {
                // Going down (from son)
                add(down, r.first);
                add(resultDown, r.first);
                r.second.push_back(0);
                add(down, r.second);
                add(resultDown, r.second);
            } else {
                // Equal
                add(down, r.first);
                add(resultDown, r.first);
                add(down, r.second);
                add(resultDown, r.second);
            }
        }
    }
    FOR(i, stepsDown) {
        int neighbor = node;
        node = parent[node];
        if (a[node] > a[neighbor]) {
            // Going up (from son)
            add(resultUp, resultDown);
            resultDown.clear();
        } else if (a[node] < a[neighbor]) {
            // Going down (from son)
            resultUp.push_back(0);
            add(resultDown, resultUp);
            resultUp.clear();
        } else {
            // Equal
            add(resultDown, resultUp);
            resultUp.clear();
        }
        ensureSize(resultDown, 1);
        resultDown[resultDown.size() - 1]++;
    }
    return make_pair(resultDown, resultUp);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        l = getInt();
        r = getInt();
        if (r > n) r = n;
        if (l > n) l = n;
        FOR(i, n) a[i] = getInt();
        FOR(i, n) neighbors[i].clear();
        FOR(i, n - 1) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            neighbors[u].push_back(v);
            neighbors[v].push_back(u);
        }
        result = 0;
        mm down;
        mm up;
        solve(0, -1, down, up);
        print(result);
    }
}
