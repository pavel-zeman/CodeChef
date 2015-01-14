// Calculate the profit for each kind and choose the highest one
// http://www.codechef.com/JAN15/problems/CHEFSTON
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

int a[MAX_N];

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

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int k = getInt();
        FOR(i, n) a[i] = getInt();
        long long int maxProfit = 0;
        FOR(i, n) {
            int b = getInt();
            long long int localProfit = k;
            localProfit /= a[i];
            localProfit *= b;
            if (localProfit > maxProfit) maxProfit = localProfit;
        }
        printf("%lld\n", maxProfit);
    }
}
