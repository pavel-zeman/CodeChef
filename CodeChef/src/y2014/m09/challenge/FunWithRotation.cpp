// Track the position of the start of the array
// http://www.codechef.com/SEPT14/problems/ROTATION
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

#define MAX_N 100010

int a[MAX_N];


int main(void) {
    int n, m;
    scanf("%d%d", &n, &m);
    FOR(i, n) scanf("%d", &a[i]);
    int start = 0;
    FOR(i, m) {
        char action[10];
        int d;
        scanf("%s%d", action, &d);
        switch (action[0]) {
            case 'A':
                start = (start - d + n) % n;
                break;

            case 'C':
                start = (start + d) % n;
                break;

            case 'R':
                printf("%d\n", a[(start + d - 1) % n]);
                break;
        }
    }
}
