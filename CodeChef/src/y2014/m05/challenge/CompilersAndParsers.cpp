// Simple parenthesis matching
// http://www.codechef.com/MAY14/problems/COMPILER
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


char buffer[1000002];

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(i, t) {
        scanf("%s", buffer);
        int max = 0;
        int pos = 0;
        int balance = 0;
        while (buffer[pos] != 0) {
            balance += buffer[pos] == '<' ? 1 : -1;
            if (balance < 0) break;
            if (balance == 0) max = pos + 1;
            pos++;
        }
        printf("%d\n", max);
    }
}
