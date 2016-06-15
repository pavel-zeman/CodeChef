// Just brute force solution of the small input
// https://www.codechef.com/JUNE16
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

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 200010
#define MAX_G 1000010

int n, e;
int g[MAX_N];
int totalResidents[MAX_G];
vector<int> neighbors[MAX_N];

int totalSadNeighbors[MAX_N];
int used[MAX_N];

map<int, vector<int> > componentsForG[MAX_G];
vector<int> componentResidents[MAX_N];
int totalComponents;

int component[MAX_N];
int searchNum;
LLI result[MAX_N];

void findComponent(int node) {
    used[node] = searchNum;
    component[node] = totalComponents;
    FOR(i, neighbors[node].size()) {
        int neighbor = neighbors[node][i];
        if (used[neighbor] != searchNum) findComponent(neighbor);
    }
}


void findComponent2(int node, int forbidden) {
    used[node] = searchNum;
    //printf("Assign: %d = %d\n", node, totalComponents);
    component[node] = totalComponents;
    FOR(i, neighbors[node].size()) {
        int neighbor = neighbors[node][i];
        if (neighbor != forbidden && used[neighbor] != searchNum) findComponent2(neighbor, forbidden);
    }
}

int main(void) {
    n = getInt();
    e = getInt();
    FOR(i, n) {
        g[i] = getInt();
        totalResidents[g[i]]++;
    }
    FOR(i, e) {
        int a = getInt() - 1;
        int b = getInt() - 1;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
    searchNum = 1;
    FOR(i, n) {
        if (used[i] != searchNum) {
            findComponent(i);
            totalComponents++;
        }
        int c = component[i];
        componentsForG[g[i]][c].push_back(i);
        componentResidents[c].push_back(i);
    }
    LLI totalSad = 0;
    FOR(i, n) {
        int totalG = totalResidents[g[i]];
        totalSadNeighbors[i] = totalG - componentsForG[g[i]][component[i]].size();
        totalSad += totalSadNeighbors[i];
    }
    totalSad >>= 1;

    int originalTotalComponents = totalComponents;
    FOR(i, originalTotalComponents) {
        FOR(j, componentResidents[i].size()) {
            searchNum++;
            totalComponents = 0;
            FOR(k, componentResidents[i].size()) {
                int node = componentResidents[i][k];
                if (used[node] != searchNum && k != j) {
                    findComponent2(node, componentResidents[i][j]);
                    totalComponents++;
                }
            }
            //printf("%d = %d\n", componentResidents[i][j], totalComponents);
            component[componentResidents[i][j]] = -1;
            int newSad = 0;
            FOR(k, componentResidents[i].size()) {
                FORE(l, k + 1, (int)componentResidents[i].size())
                    if (g[componentResidents[i][k]] == g[componentResidents[i][l]] && component[componentResidents[i][k]] != component[componentResidents[i][l]])
                        newSad++;
            }
            result[componentResidents[i][j]] = totalSad + newSad;
        }
    }
    FOR(i, n) printf("%lld\n", result[i]);


}

