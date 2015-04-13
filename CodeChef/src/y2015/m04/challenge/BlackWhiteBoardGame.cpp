// Just brute force approach
// http://www.codechef.com/APRIL15/problems/BWGAME
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

#define MAX_N 10

int n;
int l[MAX_N], r[MAX_N];
int value[MAX_N];
int even, odd;
bool used[MAX_N];

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

void generate(int level) {
    if (level < n) {
        FORE(i, l[level], r[level])
            if (!used[i]) {
                used[i] = true;
                value[level] = i;
                generate(level + 1);
                used[i] = false;
            }
    } else {
        int inversions = 0;
        FOR(i, n - 1) {
            int v = value[i];
            FORE(j, i + 1, n)
                if (v > value[j]) inversions++;
        }
        if (inversions & 1) odd++; else even++;
    }
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) l[i] = getInt() - 1, r[i] = getInt();
        even = odd = 0;
        FOR(i, n) used[i] = false;
        generate(0);
        if (even == odd) puts("Draw");
        else puts(even < odd ? "Fedor" : "Alex");
    }
}
