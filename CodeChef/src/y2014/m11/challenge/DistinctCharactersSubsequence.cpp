// Keep track of of characters that are used
// http://www.codechef.com/NOV14/problems/DISCHAR
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

#define MAX_N 100010
#define MAX_CHARS 26

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        char data[MAX_N];
        scanf("%s", data);
        char used[MAX_CHARS];
        FOR(i, MAX_CHARS) used[i] = 0;

        char *start = data;
        while (*start) used[*start++ - 'a'] = 1;
        int total = 0;
        FOR(i, MAX_CHARS) total += used[i];

        printf("%d\n", total);
    }
}
