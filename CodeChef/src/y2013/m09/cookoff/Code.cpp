// Repeated invocations of AND and OR do nothing, so we run them just once. For XOR, we have to distinguish between even and odd number of repetitions.
// http://www.codechef.com/COOK38/problems/RRCODE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 2000

#define AND 0
#define OR 1
#define XOR 2


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

void getString(char *dst) {
    while (c < 'A' || c >= 'Z') c = getc_unlocked(stdin);
    while (c >= 'A' && c <= 'Z') {
        *dst++ = c;
        c = getc_unlocked(stdin);
    }
    *dst = 0;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int k = getInt();
        int ans = getInt();
        int a[MAX_N];
        FOR(i, n) a[i] = getInt();
        char opName[10];
        getString(opName);
        int op = 0;
        if (!strcmp(opName, "AND")) op = AND;
        else if (!strcmp(opName, "OR")) op = OR;
        else op = XOR;

        if (k > 0) {
            int tot = a[0];
            FORE(i, 1, n) {
                switch (op) {
                    case AND: tot = tot & a[i]; break;
                    case OR: tot = tot | a[i]; break;
                    case XOR: tot = tot ^ a[i]; break;
                }
            }

            switch (op) {
                case AND: ans = ans & tot; break;
                case OR: ans = ans | tot; break;
                case XOR: ans = (k & 1) == 0 ? ans : ans ^ tot; break;
            }
        }
        printf("%d\n", ans);

    }
}
