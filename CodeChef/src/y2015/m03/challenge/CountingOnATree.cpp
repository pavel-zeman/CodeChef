// Naive brute-force algorithm
// http://www.codechef.com/MARCH15/problems/TREECNT2
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

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010

int n;

struct Neighbor {
    int node;
    int valueIndex;

    Neighbor(int node, int valueIndex) {
        this->node = node;
        this->valueIndex = valueIndex;
    }
};

vector<Neighbor> neighbors[MAX_N];
int values[MAX_N];

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

int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int visit(int node, int previous, int currentGcd) {
    int result = currentGcd == 1 ? 1 : 0;
    FOR(i, (int)neighbors[node].size()) {
        Neighbor n = neighbors[node][i];
        if (n.node != previous) result += visit(n.node, node, gcd(currentGcd, values[n.valueIndex]));
    }
    return result;
}

long long int calcTotal() {
    long long int total = 0;
    FOR(i, n) total += visit(i, -1, 0);
    return total >> 1;
}

int main(void) {
    n = getInt();
    FOR(i, n - 1) {
        int x = getInt() - 1;
        int y = getInt() - 1;
        int z = getInt();
        values[i] = z;
        neighbors[x].push_back(Neighbor(y, i));
        neighbors[y].push_back(Neighbor(x, i));
    }
    printf("%lld\n", calcTotal());
    int q = getInt();
    FOR(i, q) {
        int a = getInt() - 1;
        int c = getInt();
        values[a] = c;
        printf("%lld\n", calcTotal());
    }


}
