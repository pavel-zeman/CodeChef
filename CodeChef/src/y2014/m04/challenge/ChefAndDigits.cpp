// Calculate cummulative counts of each digit and then use it to calculate result
// http://www.codechef.com/APRIL14/problems/ADIGIT
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010

int input[MAX_N];
int digitCount[MAX_N][10];

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

void getString() {
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    int i = 0;
    while (c >= '0' && c <= '9') {
        input[i++] = c - '0';
        c = getc_unlocked(stdin);
    }
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int main(void) {
    int n = getInt(), m = getInt();
    getString();
    FOR(i, 10) digitCount[0][i] = 0;
    FORE(i, 1, n) {
        FOR(j, 10) digitCount[i][j] = digitCount[i - 1][j];
        digitCount[i][input[i - 1]]++;
    }
    FOR(i, m) {
        int x = getInt() - 1;
        int result = 0;
        FOR(j, 10) result += digitCount[x][j] * abs(input[x] - j);
        printf("%d\n", result);
    }
}
