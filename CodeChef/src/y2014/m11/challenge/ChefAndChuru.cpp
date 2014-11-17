//
// http://www.codechef.com/NOV14/problems/FNCS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

#define MAX_N 100010

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

long long int tree[MAX_N];
int l[MAX_N], r[MAX_N];
int a[MAX_N];
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

long long read(int idx) {
	long long int sum = 0;
	while (idx > 0){
		sum += tree[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void update(int idx, long long int val) {
	while (idx <= n){
		tree[idx] += val;
		idx += (idx & -idx);
	}
}

int main(void) {
    n = getInt();
    FOR(i, n) tree[i] = 0;
    tree[n + 1] = 0;
    FOR(i, n) update(i + 1, a[i + 1] = getInt());
    FOR(i, n) l[i] = getInt(), r[i] = getInt();
    int q = getInt();
    FOR(i, q) {
        int operation = getInt();
        switch (operation) {
            case 1: {
                int x = getInt();
                int y = getInt();
                update(x, y - a[x]);
                a[x] = y;
                }
                break;
            case 2:
                int m = getInt() - 1;
                int n = getInt();
                long long int result = 0;
                FORE(i, m, n) result += read(r[i]) - read(l[i] - 1);
                //FORE(i, m, n) printf("%lld ", read(r[i]) - read(l[i] - 1));
                printf("%lld\n", result);
                break;
        }
    }
}
