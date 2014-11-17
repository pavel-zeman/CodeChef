// Simple binary tree and algorithm to find common ancestor
// http://www.codechef.com/NOV14/problems/RBTREE
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

int depth(int a) {
    int temp = 1;
    int d = 0;
    while (temp <= a) {
        d++;
        temp <<= 1;
    }
    return d;
}

int main(void) {
    int t;
    int status = 0;
    scanf("%d", &t);
    FOR(tt, t) {
        char operation[10];
        scanf("%s", operation);
        if (!strcmp(operation, "Qi")) status ^= 1; else {
            int countColor = !strcmp(operation, "Qb");
            int x, y;
            scanf("%d %d", &x, &y);
            int dx = depth(x), dy = depth(y);
            int total[2];
            total[0] = total[1] = 0;
            while (x != y) {
                if (x > y) {
                    total[dx & 1]++;
                    dx--;
                    x >>= 1;
                } else {
                    total[dy & 1]++;
                    dy--;
                    y >>= 1;
                }
            }
            total[dx & 1]++;
            printf("%d\n", total[countColor ^ status]);
        }
    }
}
