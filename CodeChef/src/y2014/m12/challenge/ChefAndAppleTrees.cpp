// The answer is the count of distinct numbers of apples
// http://www.codechef.com/DEC14/problems/CAPPLE
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

#define MAX_APPLES 100010

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

bool used[MAX_APPLES];

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
        FOR(i, MAX_APPLES) used[i] = false;
        int n = getInt();
        int total = 0;
        FOR(i, n) {
            int a = getInt();
            if (!used[a]) {
                used[a] = true;
                total++;
            }
        }
        printf("%d\n", total);
    }
}
