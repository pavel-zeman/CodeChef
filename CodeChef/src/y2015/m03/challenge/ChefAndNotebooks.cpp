// No magic - simply try all the notebooks one by one
// http://www.codechef.com/MARCH15/problems/CNOTE
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
        int x = getInt();
        int y = getInt();
        int k = getInt();
        int n = getInt();
        int remain = x - y;
        bool found = false;
        FOR(i, n) {
            int p = getInt();
            int c = getInt();
            if (p >= remain && c <= k) found = true;
        }
        puts(found ? "LuckyChef" : "UnluckyChef");
    }
}
