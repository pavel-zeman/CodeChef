// There are 2 cases - When S is an old city, then any shortest path can use at most one old road and the old road must be the first one in the path. So use only old roads from S to all other old cities and run Dijkstra's algorithm. When S is a new city, then every shortest path must use at most one old road and the road must start at the old city closest to S. Find this city using Dijkstra's algorithm, then add all old roads from this city to all other old cities and solve the problem using Dijkstra's algorithm.
// https://www.codechef.com/APRIL17/problems/CLIQUED
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
vector<pair<int, int> > neighbors[MAX_N];
LLI dist[MAX_N];
int n, k, x, m, s;
LLI inf;
set<pair<LLI, int> > todo;

void solve() {
    todo.clear();
    FOR(i, n) dist[i] = inf;
    dist[s] = 0;
    FOR(i, n) todo.insert(make_pair(dist[i], i));
    while (!todo.empty()) {
        pair<LLI, int> f = *todo.begin();
        LLI d = f.first;
        if (d == inf) break;
        int node = f.second;
        todo.erase(todo.begin());
        FOR(i, neighbors[node].size()) {
            pair<int, int> neigh = neighbors[node][i];
            if (d + neigh.second < dist[neigh.first]) {
                todo.erase(make_pair(dist[neigh.first], neigh.first));
                dist[neigh.first] = d + neigh.second;
                todo.insert(make_pair(dist[neigh.first], neigh.first));
            }
        }
    }
}

int main(void) {
    inf = 1000000000;
    inf *= 1000000000;
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        k = getInt();
        x = getInt();
        m = getInt();
        s = getInt() - 1;
        FOR(i, n) neighbors[i].clear();
        FOR(i, m) {
            int a = getInt() - 1;
            int b = getInt() - 1;
            int c = getInt();
            neighbors[a].push_back(make_pair(b, c));
            neighbors[b].push_back(make_pair(a, c));
        }
        if (s < k) {
            FOR(i, k) if (i != s) {
                neighbors[s].push_back(make_pair(i, x));
                neighbors[i].push_back(make_pair(s, x));
            }
            solve();
        } else {
            solve();
            int minPos = min_element(dist, dist + k) - dist;
            FOR(i, k) if (i != minPos) {
                neighbors[minPos].push_back(make_pair(i, x));
                neighbors[i].push_back(make_pair(minPos, x));
            }
            solve();
        }
        FOR(i, n) printf("%lld ", dist[i]);
        printf("\n");
    }
}

