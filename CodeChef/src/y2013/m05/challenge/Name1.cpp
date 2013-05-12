#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXL 50000
#define CHARS 26

int counts[CHARS];


int add(char *t, int c) {
    while (*t) {
        counts[*t++ - 'a'] += c;
    }
}

int main(void) {
    int cases;
    scanf("%d", &cases);
    for(int c=1;c<=cases;c++) {
        char a[MAXL], b[MAXL];
        scanf("%s%s", a, b);
        FOR(i, CHARS) counts[i] = 0;
        add(a, 1);
        add(b, 1);

        int n;
        scanf("%d", &n);
        FOR(i, n) {
            scanf("%s", a);
            add(a, -1);
        }
        bool ok = true;
        FOR(i, CHARS) if (counts[i] < 0) { ok = false; break;}
        printf("%s\n", ok ? "YES" : "NO");
    }
}
