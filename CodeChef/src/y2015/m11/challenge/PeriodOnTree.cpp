// Just brute force
// https://www.codechef.com/NOV15/problems/TREEP
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


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

char getChar() {
    while (!(ccc >= 'a' && ccc <= 'z')) ccc = getc_unlocked(stdin);
    char result = ccc;
    ccc = getc_unlocked(stdin);
    return result;
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


void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}

#define MAX_N 100010

vector<pair<int, char> > neighbor[MAX_N];
pair<int, char> parent[MAX_N];
int depth[MAX_N];
int n;

char path1[MAX_N], path2[MAX_N];
char path[MAX_N];


void dfs(int node, int previous, int d, char c) {
    parent[node] = make_pair(previous, c);
    depth[node] = d;
    for(vector<pair<int, char> >::iterator it = neighbor[node].begin(); it != neighbor[node].end(); it++)
        if (it->first != previous)
            dfs(it->first, node, d + 1, it->second);
}

int getPeriod(int u, int v) {
    int d1 = depth[u];
    int d2 = depth[v];
    int l1 = 0;
    int l2 = 0;
    while (d1 > d2) {
        path1[l1++] = parent[u].second;
        u = parent[u].first;
        d1--;
    }
    while (d2 > d1) {
        path2[l2++] = parent[v].second;
        v = parent[v].first;
        d2--;
    }
    while (u != v) {
        path1[l1++] = parent[u].second;
        u = parent[u].first;
        path2[l2++] = parent[v].second;
        v = parent[v].first;
    }
    FOR(i, l1) path[i] = path1[i];
    FOR(i, l2) path[i + l1] = path2[l2 - i - 1];
    int l = l1 + l2;
    FORE(i, 1, l + 1) {
        if (l % i == 0) {
            bool ok = true;
            FOR(j, i)
                for(int k = j; k < l;k+= i)
                    if (path[j] != path[k]) {
                        ok = false;
                        goto end;
                    }
            end:
            if (ok) return i;
        }
    }
    return 0;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) neighbor[i].clear();
        FOR(i, n - 1) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            char c = getChar();
            neighbor[u].push_back(make_pair(v, c));
            neighbor[v].push_back(make_pair(u, c));
        }
        dfs(0, -1, 0, 'x');
        int m = getInt();
        FOR(i, m) {
            int op = getInt();
            int u = getInt() - 1;
            int v = getInt() - 1;
            switch (op) {
                case 1:
                    print(getPeriod(u, v));
                    break;

                case 2:
                    if (parent[u].first != v) swap(u, v);
                    parent[u].second = getChar();
                    break;
            }
        }
    }
}

