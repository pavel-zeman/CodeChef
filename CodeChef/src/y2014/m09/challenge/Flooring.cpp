// Unfinished and rewritten to Java to be able to work with big integers
// http://www.codechef.com/SEPT14/problems/FLOORI4
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
long long int getInt() {
    long long int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

long long int n;
int m;


long long int pow(long long int i) {
    long long int result = i * i % m;
    return result * result % m;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();

        long long int result = 0;
        long long int c = 1;
        while (c * c < n) {
            result += pow(c) * (n / c) % m;
            int start = n / (c + 1) + 1;
            int end = n / c;
            c++;
        }
        // sum_(i=a)^b i^4 = 1/30 (-6 a^5+15 a^4-10 a^3+a+6 b^5+15 b^4+10 b^3-b)

    }
}
