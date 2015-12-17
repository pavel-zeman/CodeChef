// Brute force solution, which works just for the small inputs
// https://www.codechef.com/DEC15/problems/WAYPA
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int


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

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 100020

vector<pair<int, int> > neighbors[MAX_N];

int result;
int path[MAX_N];

bool checkPalindrome(int size) {
    int i = 0;
    int j = size - 1;
    while (i < j) {
        if (path[i] != path[j]) return false;
        i++;
        j--;
    }
    return true;
}

void dfs(int node, int previous, int pos) {
    if (pos > result && checkPalindrome(pos)) result = pos;
    FOR(i, neighbors[node].size()) {
        pair<int, int> n = neighbors[node][i];
        if (n.first != previous) {
            path[pos] = n.second;
            dfs(n.first, node, pos + 1);
        }
    }
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        FOR(i, n) neighbors[i].clear();
        result = 0;
        FOR(i, n - 1) {
            int a = getInt() - 1;
            int b = getInt() - 1;
            int c = getInt();
            neighbors[a].push_back(make_pair(b, c));
            neighbors[b].push_back(make_pair(a, c));
        }
        FOR(i, n) dfs(i, -1, 0);
        print(result + 1);
    }
}

