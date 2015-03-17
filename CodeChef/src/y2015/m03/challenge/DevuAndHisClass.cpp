// If the number of B's differs from number of G's by more than 1, then there is no solution. Otherwise go from left and for each invalid B or G choose the closest invalid G or B and swap them. For type 0, the cost is 1. For type 1 and 2, the cost is j - i.
// http://www.codechef.com/MARCH15/problems/DEVCLASS
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

#define MAX_N 100010

char input[MAX_N];
char back[MAX_N];
int count[2];
int type, n;

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
    int pos = 0;
    count[0] = count[1] = 0;
    while (c != 'B' && c != 'G') c = getc_unlocked(stdin);
    while (c == 'B' || c == 'G') {
        c = c == 'B' ? 0 : 1;
        count[c]++;
        input[pos++] = c;
        c = getc_unlocked(stdin);
    }
    return pos;
}

long long int solve(int first) {
    if (n == 1) return 0;
    int nextInvalid[2];
    nextInvalid[0] = nextInvalid[1] = 0;
    long long int total = 0;

    FOR(i, n) {
        int search = (i + first) & 1;
        if (input[i] != search) {
            int j = nextInvalid[search];
            while (!(input[j] == search && ((j + first) & 1) != search)) j++;
            nextInvalid[search] = j;
            int temp = input[i];
            input[i] = input[j];
            input[j] = temp;
            total += type == 0 ? 1 : j - i;
        }
    }
    return total;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        type = getInt();
        n = getString();
        if (count[0] - count[1] > 1 || count[0] - count[1] < -1) {
            puts("-1");
        } else {
            long long int result = 0;
            if (count[0] > count[1]) result = solve(0);
            else if (count[1] > count[0]) result = solve(1);
            else {
                FOR(i, n) back[i] = input[i];
                result = solve(0);
                FOR(i, n) input[i] = back[i];
                long long int result2 = solve(1);
                if (result2 < result) result = result2;
            }
            printf("%lld\n", result);
        }
    }
}
