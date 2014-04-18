// Hackenbush game and the algorithm to calculate game value as described at http://www.geometer.org/mathcircles/hackenbush.pdf (chapter 10) - unfortunately this does not work, because the double precision is not sufficient
// http://www.codechef.com/APRIL14/problems/GERALD08
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010

using namespace std;

vector<pair<int,bool> > neighbor[MAX_N];
bool used[MAX_N];
int n;

char c = 0;
int getInt() {
    int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

long double calcValue(int node, bool red) {
    used[node] = true;
    long double total = 0;
    FOR(i, (int)neighbor[node].size()) {
        int child = neighbor[node][i].first;
        if (!used[child]) {
            total += calcValue(child, neighbor[node][i].second);
        }
    }
    if (red) {
        if (total < 0)
            return total - 1;
        else {
            long double temp = floor(total + 1) + 1;
            return (total - temp) * pow(2, - (temp - 1));
        }
    } else {
        if (total > 0)
            return total + 1;
        else {
            long double temp = floor(1 - total) + 1;
            return (total + temp) * pow(2, - (temp - 1));
        }
    }
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) {
            neighbor[i].clear();
            used[i] = false;
        }
        n--;
        FOR(i, n) {
            int u = getInt() - 1;
            int v = getInt() - 1;
            int c = getInt();
            neighbor[u].push_back(make_pair(v, c == 1));
            neighbor[v].push_back(make_pair(u, c == 1));
        }
        used[0] = true;
        long double total = 0;
        FOR(i, (int)neighbor[0].size()) {
            int child = neighbor[0][i].first;
            total += calcValue(child, neighbor[0][i].second);
        }
        if (total == 0) {
            puts("Ksen Chef");
        } else if (total < 0) {
            puts("Ksen Ksen");
        } else {
            puts("Chef Chef");
        }
    }
}
