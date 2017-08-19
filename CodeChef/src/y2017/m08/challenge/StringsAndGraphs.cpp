// Calculate A position by position. For each position consider the closest previous item with no edge and farthest previous item with an edge.
// https://www.codechef.com/AUG17/problems/STRINGRA
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
set<int> predecessors[MAX_N];
set<int> used[MAX_N];
int a[MAX_N];

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        FOR(i, n + 1) predecessors[i].clear(), used[i].clear();
        bool ok = true;
        FOR(i, m) {
            int a = getInt();
            int b = getInt();
            if (a >= b || predecessors[b].find(a) != predecessors[b].end()) ok = false;
            else predecessors[b].insert(a);
        }

        if (ok) {
            int mm = 2;
            FORE(i, 1, n + 1) {
                if (predecessors[i].empty()) { ok = false; break; }
                int first = *predecessors[i].begin();
                int ind = i - 1;
                while (ind >= 0 && predecessors[i].find(ind) != predecessors[i].end()) ind--;
                bool found = false;
                int v = 0;
                if (ind >= 0) {
                    for(auto it = used[ind].begin(); it != used[ind].end(); it++)
                        if (used[first].find(*it) == used[first].end()) {
                            found = true;
                            v = *it;
                        }
                } else {
                    FORE(j, 1, mm)
                        if (used[first].find(j) == used[first].end()) {
                            found = true;
                            v = j;
                        }
                }
                if (!found) { ok = false; break; }
                a[i] = v;
                mm = max(a[i] + 2, mm);
                for(auto it = predecessors[i].begin(); it != predecessors[i].end(); it++) used[*it].insert(v);
            }
        }

        if (ok) FORE(i, 1, n + 1) print(a[i]); else print(-1);
    }
}

