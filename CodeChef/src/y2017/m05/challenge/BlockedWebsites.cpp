// Use trie to represent the sites and generate the prefixes
// https://www.codechef.com/MAY17/problems/WSITES01
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

#define MAX_N 200010
char blocked[10];
char site[MAX_N];

struct Node {
    int children[26];
    bool site;
    bool blocked;
    int blockedChildren;
    int allowedChildren;
} nodes[MAX_N];
int totalNodes = 1;
bool valid = true;
vector<string> result;

pair<int, int> calcChildren(int node) {
    pair<int, int> r = make_pair(0, 0);
    FOR(i, 26) if (nodes[node].children[i] != 0) {
        pair<int, int> t = calcChildren(nodes[node].children[i]);
        r.first += t.first;
        r.second += t.second;
    }
    if (nodes[node].site) {
        if (nodes[node].blocked && r.second > 0) valid = false;
        if (nodes[node].blocked) r.first++; else r.second++;
    }
    nodes[node].blockedChildren = r.first;
    nodes[node].allowedChildren = r.second;
    return r;
}

void gen(int node, int depth) {
    if (nodes[node].blockedChildren == 0) return;
    if (nodes[node].blockedChildren > 0 && nodes[node].allowedChildren == 0) {
        site[depth] = 0;
        result.push_back(string(site));
        return;
    }
    FOR(i, 26) if (nodes[node].children[i] != 0) {
        site[depth] = i + 'a';
        gen(nodes[node].children[i], depth + 1);
    }
}

int main(void) {
    int n = getInt();
    FOR(i, n) {
        getString(blocked);
        int l = getString(site);
        int node = 0;
        FOR(j, l) {
            int c = site[j] - 'a';
            if (nodes[node].children[c] == 0) nodes[node].children[c] = totalNodes++;
            node = nodes[node].children[c];
        }
        nodes[node].site = true;
        nodes[node].blocked = blocked[0] == '-';
    }
    calcChildren(0);
    if (valid) {
        gen(0, 0);
        print(result.size());
        FOR(i, result.size()) printString(result[i].c_str());
    } else print(-1);
}

