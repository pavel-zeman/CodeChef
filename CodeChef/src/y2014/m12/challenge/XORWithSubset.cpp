// Maintain a set of all numbers reachable from the inital K and update it with each A, then select the maximum one
// http://www.codechef.com/DEC14/problems/XORSUB
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

#define MAX_NUMBER 1026

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

bool used[MAX_NUMBER];

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
        FOR(i, MAX_NUMBER) used[i] = false;
        int n = getInt();
        int k = getInt();
        used[k] = true;
        FOR(i, n) {
            int a = getInt();
            FOR(j, MAX_NUMBER) if (used[j]) used[j ^ a] = true;
        }
        int result = MAX_NUMBER - 1;
        while (!used[result]) result--;
        printf("%d\n", result);
    }
}
