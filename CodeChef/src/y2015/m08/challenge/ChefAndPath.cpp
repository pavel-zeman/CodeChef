// Just brute force solution
// https://www.codechef.com/AUG15/problems/STETSKLX
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
#define MAX_RESULT 1000000010
vector<pair<int, int> > neighbors[MAX_N];

int n, l , r;
int lengths[MAX_N];
int lengthsTemp[MAX_N];
int result;
int startNode;

void check(int node, int previous, int depth) {
    if (depth >= l && startNode < node) {
        memcpy(lengthsTemp, lengths, depth * sizeof(int));
        sort(lengthsTemp, lengthsTemp + depth);
        int middle = depth >> 1;
        if (lengthsTemp[middle] < result) result = lengthsTemp[middle];
    }
    if (depth < r) {
        int totalNeighbors = neighbors[node].size();
        FOR(i, totalNeighbors) {
            if (neighbors[node][i].first != previous) {
                lengths[depth] = neighbors[node][i].second;
                check(neighbors[node][i].first, node, depth + 1);
            }
        }
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        l = getInt();
        r = getInt();
        FOR(i, n) neighbors[i].clear();

        FOR(i, n - 1) {
            int a = getInt() - 1;
            int b = getInt() - 1;
            int c = getInt();
            neighbors[a].push_back(make_pair(b, c));
            neighbors[b].push_back(make_pair(a, c));
        }
        result = MAX_RESULT;
        FOR(i, n) check(startNode = i, -1, 0);
        if (result == MAX_RESULT) result = -1;
        print(result);
    }
}

