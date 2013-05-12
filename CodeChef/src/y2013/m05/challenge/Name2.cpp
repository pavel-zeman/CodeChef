#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXL 30000

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        char m[MAXL], w[MAXL];
        char *a, *b;
        scanf("%s%s", m, w);
        int la = strlen(m), lb = strlen(w);
        if (la > lb) {
            int x = la;
            la = lb;
            lb = x;
            a = w;
            b = m;
        } else {
            a = m;
            b = w;
        }
        bool ok = true;
        int pa = 0, pb = 0;
        while (pa < la) {
            while (pb < lb && a[pa] != b[pb]) pb++;
            if (pb == lb) {
                ok = false;
                break;
            }
            pa++;
            pb++;
        }
        printf("%s\n", ok ? "YES" : "NO");
    }
}
