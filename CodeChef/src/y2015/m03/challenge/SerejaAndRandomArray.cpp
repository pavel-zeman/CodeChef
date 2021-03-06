// The number of different sequences generated by LCG is limited - there are only 2^17 of them. The sequences generated for seed = x + k * 2^17 are the same for all k. So it is necessary to test only 2^17 of different seeds of LCG.
// http://www.codechef.com/MARCH15/problems/SEAPROAR
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

#define MAX_N 200010

char input[MAX_N];
int n;

unsigned X; // we assume that unsigned is a 32bit integer type

void srand1(unsigned S){
  X = S;
}

int nextInteger1(void){
  X = X * 1103515245 + 12345;
  return (X >> 16) & 1;
}

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
    n = 0;
    while (c != '0' && c != '1') c = getc_unlocked(stdin);
    while (c == '0' || c == '1') {
        input[n++] = c - '0';
        c = getc_unlocked(stdin);
    }
}

int main(void) {
    srand1(0);
    FOR(i, 10) {
        nextInteger1();
        printf("%u ", X);
    }
    printf("\n");
    srand1(1 << 17);
    FOR(i, 10) {
        nextInteger1();
        printf("%u ", X);
    }

    int t = getInt();
    FOR(tt, t) {
        getString();
        bool lcg = false;
        FOR(i, 1<<17) {
            srand1(i);
            bool found = true;
            FOR(j, n) {
                if (nextInteger1() != input[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                lcg = true;
                break;
            }
        }
        puts(lcg ? "LCG" : "Xorshift");
    }
}
