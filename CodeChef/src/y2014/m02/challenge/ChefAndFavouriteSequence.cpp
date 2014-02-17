// Unfortunately, this does not work
// http://www.codechef.com/FEB14/problems/CHSEQ22
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 1000000007
#define MAX_M 100010



#define MAX_U 65536
bool used[MAX_U];

int data[][2] = {{1,3}, {1,2}, {2, 3}};

#define N ((int)(sizeof(data) / sizeof(data[0])))
int x[N];

int n, m;

struct Segment {
    int l, r;
} segments[MAX_M];

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


void generate(int level, int curr) {
    if (level == N) {
        used[curr] = true;
    } else {
        generate(level + 1, curr);
        generate(level + 1, curr ^ x[level]);
    }
}

int power(int a, int b) {
    long long int result = 1;
    long long int temp = a;
    while (b > 0) {
        if ((b & 1) == 1) {
            result = result * temp % MOD;
        }
        temp = temp * temp % MOD;
        b >>= 1;
    }
    return (int)result;
}


int cmp(const void *p1, const void *p2) {
    struct Segment *s1 = (Segment *)p1;
    struct Segment *s2 = (Segment *)p2;

    return s1->l == s2->l ? s1->r - s2->r : s1->l - s2->l;
}

int main(void) {
    /*FOR(i, MAX_U) used[i] = false;
    FOR(i, N) {
        x[i] = 0;
        FORE(j, data[i][0], data[i][1] + 1) { x[i] <<= 1; x[i] |= 1;}
        FOR(j, data[i][0]) x[i] <<= 1;
    }
    generate(0, 0);

    int total = 0;
    FOR(i, MAX_U) total += used[i];
    printf("%d\n", total);*/
    n = getInt();
    m = getInt();
    FOR(i, m) {
        segments[i].l = getInt() - 1;
        segments[i].r = getInt() - 1;
    }
    qsort(segments, m, sizeof(segments[0]), cmp);
    int t = 0;
    FOR(i, m) {
        //printf("%d %d\n", segments[i].l, segments[i].r);
        t++;
        if (i > 0 && segments[i].l == segments[i - 1].l && segments[i].r == segments[i - 1].r) t--;
    }
    if (t > n) t = n;
    printf("%d\n", power(2, t));
}
