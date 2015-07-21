// We only get a zero by multiplying 5 by 2. So we calculate number of 5s in the number, number of 2s and multiply by 4 for every 2 5s.
// http://www.codechef.com/JULY15/problems/LCKYST
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

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        long long int a = getInt();
        int fives = 0;
        int twos = 0;
        int temp = a;
        while (temp % 5 == 0) { temp /= 5; fives++; }
        temp = a;
        while ((temp & 1) == 0) { temp >>= 1; twos++; }
        while (fives > twos) { a <<= 2; fives -= 2; }
        printf("%lld\n", a);
    }
}
