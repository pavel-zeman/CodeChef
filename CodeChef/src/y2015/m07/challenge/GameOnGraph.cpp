// Brute force solution, which is way to slow even for the smallest input.
// http://www.codechef.com/JULY15/problems/HAMILG
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

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

void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}


#define MAX_N 2048
vector<int> neighbor[MAX_N];
bool visited[MAX_N];


bool win(int node, int level) {
    visited[node] = true;
    if (level == 4) printf("%d\n", node);
    FOR(i, neighbor[node].size()) {
        int j = neighbor[node][i];
        if (!visited[j]) {
            if (win(j, level + 1)) {
                visited[node] = false;
                return false;
            }
        }
    }
    visited[node] = false;
    return true;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        if (n > 18) fail();
        int m = getInt();
        FOR(i, m) {
            int a = getInt() - 1;
            int b = getInt() - 1;
            neighbor[a].push_back(b);
            neighbor[b].push_back(a);
        }
        int winning = 0;
        FOR(i, n) {
            printf("Checking %d\n", i);
            if (win(i, 0)) winning++;
        }
        printf("%d\n", winning);

        FOR(i, n) neighbor[i].clear();
    }
}

