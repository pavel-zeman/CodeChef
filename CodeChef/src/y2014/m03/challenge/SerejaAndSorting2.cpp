// Simply go one by one choosing the lowest number (from the beginning) or the highest one (from the end)
// http://www.codechef.com/MARCH14/problems/SEASORT2
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 10002

int n;
int a[MAX_N];
int orig[MAX_N];
int b[MAX_N];
struct Result {
    int l, r;
} result[2][MAX_N];
int operations[2];


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

int cmp(const void *p1, const void *p2) {
    return (*(int *)p1) - (*(int *)p2);
}

void swap(int l, int r) {
    int temp = a[l];
    a[l] = a[r];
    a[r] = temp;
}

void reverse(int option, int l, int r) {
    result[option][operations[option]].l = l + 1;
    result[option][operations[option]].r = r + 1;
    operations[option]++;
    while (l < r) {
        swap(l, r);
        l++;
        r--;
    }
}

int cost(int option) {
    int total = 0;
    FOR(i, operations[option]) total += result[option][i].r - result[option][i].l + 1;
    return total / n + operations[option];
}

int main(void) {
    n = getInt();
    FOR(i, n) orig[i] = b[i] = a[i] = getInt();

    qsort(b, n, sizeof(b[0]), cmp);

    FOR(i, n) {
        if (a[i] != b[i]) {
            int toFind = b[i];
            int j = i + 1;
            while (a[j] != toFind) j++;
            reverse(0, i, j);
        }
    }
    FOR(i, n) a[i] = orig[i];

    for(int i=n-1;i>=0;i--) {
        if (a[i] != b[i]) {
            int toFind = b[i];
            int j = i - 1;
            while (a[j] != toFind) j--;
            reverse(1, j, i);
        }
    }

    int minOption = 0;
    int minValue = cost(0);
    if (cost(1) < minValue) minOption = 1;

    printf("%d\n", operations[minOption]);
    FOR(i, operations[minOption]) printf("%d %d\n", result[minOption][i].l, result[minOption][i].r);
}
