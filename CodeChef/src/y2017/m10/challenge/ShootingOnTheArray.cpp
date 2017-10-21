// Combination of 2 approaches - first one uses read-only sqrt decomposition, which is discarded after first update. Second one tries the updated the pre-calculated sqrt-decomposition values.
// https://www.codechef.com/OCT17/problems/SHTARR
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

#define MAX_N 1000010
#define MAX_L 21
#define NONE -1
#define MAX_SQ_N 2048
#define MAX_Q 100010
int a[MAX_N];
int aOrig[MAX_N];
int parent[MAX_N];
int parent2[MAX_N];
int n, sqn;
int path[MAX_N];
set<int> children[MAX_N];
set<int> toCalculate;
bool modified;
int result[MAX_Q];
int resultPos;
struct Query {
    char operation;
    int pos;
    int l, r;
} query[MAX_Q];


void findParents() {
    vector<int> s;
    s.push_back(0);
    FOR(i, n + 1) FOR(j, MAX_L) parent[i] = n;
    FORE(i, 1, n + 1) {
        while (!s.empty() && a[s.back()] < a[i]) {
            parent[s.back()] = i;
            children[i].insert(s.back());
            s.pop_back();
        }
        s.push_back(i);
    }
}

int getDepth(int pos) {
    int res = 0;
    for(auto it = children[pos].cbegin(); it != children[pos].cend(); it++) {
        int l = getDepth(*it);
        if (l > res) res = l;
    }
    return res + 1;
}

void genParent2(int pos, int depth) {
    path[depth] = pos;
    parent2[pos] = depth >= sqn ? path[depth - sqn] : n;
    for(auto it = children[pos].cbegin(); it != children[pos].cend(); it++)
        genParent2(*it, depth + 1);
}

int findStart(int pos, int l) {
    while (a[parent2[pos]] < l) pos = parent2[pos];
    while (a[parent[pos]] < l) pos = parent[pos];
    return parent[pos];
}

int countEnd(int pos, int r) {
    if (pos == n) return 0;
    int result = 1;
    while (a[parent2[pos]] < r) result += sqn, pos = parent2[pos];
    while (a[parent[pos]] < r) result++, pos = parent[pos];
    if (a[pos] < r && parent[pos] != n) result++;
    return result;
}

void calculatePath(int pos) {
    int pathIndex = sqn;
    path[pathIndex] = pos;
    while (pathIndex > 0) {
        pos = parent[pos];
        path[--pathIndex] = pos;
    }
}

void updateChildren(int node, int depth) {
    if (depth <= sqn) {
        parent2[node] = path[depth];
        for(auto it = children[node].cbegin(); it != children[node].cend(); it++)
            updateChildren(*it, depth + 1);
    }
}



int query2(int pos, int l, int r) {
    for(auto it = toCalculate.cbegin(); it != toCalculate.cend(); it++) {
        calculatePath(*it);
        updateChildren(*it, 0);
    }
    toCalculate.clear();

    int start = pos;
    if (a[start] < l) start = findStart(pos, l);
    return start == n ? 0 : countEnd(start, r);
}




void update2(int pos, int x) {
    bool pathCalculated = false;
    a[pos] += x;
    int ppos = parent[pos];
    if (a[pos] >= a[ppos]) {
        children[ppos].erase(pos);
        while (a[pos] >= a[ppos]) {
            auto it = children[ppos].cbegin();
            while (it != children[ppos].cend() && *it < pos) {
                parent[*it] = pos;
                children[pos].insert(*it);
                it = children[ppos].erase(it);
            }
            ppos = parent[ppos];
        }
        parent[pos] = ppos;
        children[ppos].insert(pos);
        //calculatePath(pos);
        pathCalculated = true;
        //updateChildren(pos, 0);
        toCalculate.insert(pos);
    }

    auto it = children[ppos].find(pos);
    if (it != children[ppos].begin()) it--;
    while (it != children[ppos].begin() && a[*it] < a[pos]) {
        parent[*it] = pos;
        children[pos].insert(*it);
        if (!pathCalculated) toCalculate.insert(*it);
        children[ppos].erase(it--);
    }
    if (a[*it] < a[pos]) {
        parent[*it] = pos;
        if (!pathCalculated) toCalculate.insert(*it);
        children[pos].insert(*it);
        children[ppos].erase(it);
    }
}


int query1(int pos, int l, int r) {
    if (modified) {
        while (a[pos] < l) pos = parent[pos];
        int result = 0;
        while (a[pos] < r) result++, pos = parent[pos];
        if (pos < n) result++;
        return result;
    } else {
        int start = pos;
        if (a[start] < l) start = findStart(pos, l);
        return start == n ? 0 : countEnd(start, r);
    }
}

void update1(int pos, int x) {
    modified = true;
    a[pos] += x;
    int ppos = parent[pos];
    if (a[pos] >= a[ppos]) {
        children[ppos].erase(pos);
        while (a[pos] >= a[ppos]) {
            auto it = children[ppos].cbegin();
            while (it != children[ppos].cend() && *it < pos) {
                parent[*it] = pos;
                children[pos].insert(*it);
                it = children[ppos].erase(it);
            }
            ppos = parent[ppos];
        }
        parent[pos] = ppos;
        children[ppos].insert(pos);
    }

    auto it = children[ppos].find(pos);
    if (it != children[ppos].begin()) it--;
    while (it != children[ppos].begin() && a[*it] < a[pos]) {
        parent[*it] = pos;
        children[pos].insert(*it);
        children[ppos].erase(it--);
    }
    if (a[*it] < a[pos]) {
        parent[*it] = pos;
        children[pos].insert(*it);
        children[ppos].erase(it);
    }
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();

        int q = getInt();
        FOR(i, n) {
            a[i] = getInt();
            children[i].clear();
        }
        a[n] = 2000000001;
        FOR(i, q) {
            char op[3];
            getString(op);
            query[i].operation = op[0];
            query[i].pos = getInt() - 1;
            query[i].l = getInt();
            if (op[0] == '?') query[i].r = getInt();
        }
        memcpy(aOrig, a, (n + 1) * sizeof(a[0]));


        modified = false;
        findParents();
        int d = getDepth(n);
        sqn = min(((int)sqrt(d) + 1) * 1, n);
        genParent2(n, 0);

        bool ok = true;
        resultPos = 0;
        FOR(i, q) {
            switch (query[i].operation) {
                case '?':
                    result[resultPos++] = query1(query[i].pos, query[i].l, query[i].r);
                    break;
                case '+':
                    update1(query[i].pos, query[i].l);
                    break;
            }
            if (i % 100 == 0 && cpu() > 0.6) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            memcpy(a, aOrig, (n + 1) * sizeof(a[0]));
            FOR(i, n + 1) children[i].clear();

            findParents();
            genParent2(n, 0);
            toCalculate.clear();
            resultPos = 0;
            FOR(i, q) {
                switch (query[i].operation) {
                    case '?':
                        result[resultPos++] = query2(query[i].pos, query[i].l, query[i].r);
                        break;
                    case '+':
                        update2(query[i].pos, query[i].l);
                        break;
                }
            }
        }

        FOR(i, resultPos) print(result[i]);
    }
}

