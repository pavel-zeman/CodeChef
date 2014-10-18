// The children numbers are parent * 2 and parent * 2 + 2 for odd level and parent * 2 - 1 and parent * 2 + 1 for even level
// http://www.codechef.com/SEPT14/problems/CHEFLR
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 1000000007

char buf[100010];

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        scanf("%s", buf);
        int level = 1;
        long long int number = 1;
        char *tmp = buf;

        while (*tmp) {
            number = (number << 1) - ((level & 1) ^ 1);
            if (*tmp++ == 'r') number += 2;
            number %= MOD;
            level++;
        }
        printf("%lld\n", number);
    }
}
