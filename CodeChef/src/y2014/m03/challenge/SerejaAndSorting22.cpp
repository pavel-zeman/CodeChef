// Solve the problem one-by-one position from left to right - for each position, choose the operation, that generates the most following characters in the correct position
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
int b[MAX_N];
struct Result {
    int l, r;
} result[MAX_N];
int operations;


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

void reverse(int l, int r) {
    result[operations].l = l + 1;
    result[operations].r = r + 1;
    operations++;
    while (l < r) {
        swap(l, r);
        l++;
        r--;
    }
}

int main(void) {
    n = getInt();
    FOR(i, n) b[i] = a[i] = getInt();

    qsort(b, n, sizeof(b[0]), cmp);

    FOR(i, n) {
        if (a[i] != b[i]) {
            int toFind = b[i];
            int j = i + 1;
            int pos = -1;
            int maxSameCount = 0;
            while (j < n) {
                while (j < n && a[j] != toFind) j++;
                if (a[j] == toFind) {
                    int k = j;
                    int sameCount;
                    while (k >= i && a[k] == b[i + (j - k)]) k--;
                    if (k >= i) sameCount = j - k; else {
                        k = j + 1;
                        while (k < n && a[k] == b[k]) k++;
                        sameCount = k - i;
                    }
                    if (sameCount > maxSameCount) {
                        maxSameCount = sameCount;
                        pos = j;
                    }
                }
                j++;
            }
            reverse(i, pos);
        }
    }

    printf("%d\n", operations);
    FOR(i, operations) printf("%d %d\n", result[i].l, result[i].r);
}
