// Simple hungry algorithm
// http://www.codechef.com/COOK41/problems/GERALD03
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_OUT 10000000

char output[MAX_OUT];
int outPos;
int operations;


char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

void add(const char *operation) {
    operations++;
    output[outPos++] = operation[0];
    output[outPos++] = operation[1];
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int cl = getInt(), cr = getInt();
        operations = 0;
        outPos = 0;
        FORE(i, 1, n) {
            int nl = getInt(), nr = getInt();
            while (cl != nl || nr != cr) {
                if (cl > nl) {
                    add("L-");
                    cl--;
                } else if (cl < nl && cl < cr - 1) {
                    add("L+");
                    cl++;
                } else if (cr > nr && cr > cl + 1) {
                    add("R-");
                    cr--;
                } else if (cr < nr) {
                    add("R+");
                    cr++;
                } else {
                    printf("Error\n");
                }
            }
        }
        output[outPos] = 0;
        printf("%d\n%s\n", operations, output);
    }
}

