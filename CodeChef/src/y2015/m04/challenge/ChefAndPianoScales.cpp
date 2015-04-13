// Calculate scale size and then try all the possible starts and for each of them all the possible cycles
// http://www.codechef.com/APRIL15/problems/PIANO1
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


int getString() {
    int total = 0;
    while (c != 'S' && c != 'T') c = getc_unlocked(stdin);
    while (c == 'S' || c == 'T') {
        total += c == 'S' ? 1 : 2;
        c = getc_unlocked(stdin);
    }
    return total;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int s = getString();
        int n = getInt() * 12;
        int total = 0;
        FOR(i, n) total += (n - i - 1) / s;
        printf("%d\n", total);
    }
}
