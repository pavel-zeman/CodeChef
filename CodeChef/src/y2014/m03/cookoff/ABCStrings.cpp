// Go through the input string character after character, calculate the difference of B's - A's and C's - A's and find the same differences in a map
// http://www.codechef.com/COOK44/problems/ABCSTR
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <map>
#include <utility>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

using namespace std;

map< pair<int, int>, int > occ;

char s[1000010];

int main(void) {
    scanf("%s", s);
    int a = 0, b = 0, c = 0;
    char *t = s;
    long long int total = 0;
    occ.insert(make_pair(make_pair(0, 0), 1));

    while (*t) {
        switch (*t) {
            case 'A': a++; break;
            case 'B': b++; break;
            case 'C': c++; break;
        }
        t++;

        map<pair<int, int>, int>::iterator it = occ.find(make_pair(b - a, c - a));
        if (it != occ.end()) total += it->second;
        if (it != occ.end()) it->second++; else {
            occ.insert(make_pair(make_pair(b - a, c - a), 1));
        }
    }
    printf("%lld\n", total);
}
