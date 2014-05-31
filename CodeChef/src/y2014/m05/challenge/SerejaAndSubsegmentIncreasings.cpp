// Just an unsuccessful attempt
// http://www.codechef.com/MAY14/problems/SEINC
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
int a2[MAX_N];
int b[MAX_N];

int n;
int count[4];

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

int findFirst(int start, int value) {
    while (b[start] != value) start++;
    return start;
}

int findLast(int value) {
    int index = n - 1;
    while (b[index] != value) index--;
    return index;
}

int findLast() {
    int index = n - 1;
    //while (b[index] != 2 && b[index] != 3) index--;
    while (b[index] == 0) index--;
    return index;
}


bool check(int x, int y) {
    bool ok = false;
    if (count[x] > 0 && count[y] > 0) {
        int ia = findFirst(0, x);
        int ib = findLast(y);
        //printf("Checking %d %d: %d %d\n", x, y, ok);
        if (ia < ib) {
            b[ia]++;
            b[ib]--;
            count[x]--;
            count[y]--;
            count[(x + 1) & 3]++;
            count[(y - 1 + 4) & 3]++;
            ok = true;
        }
    }
    return ok;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) a[i] = getInt();
        FOR(i, n) a[i] = (a[i] - getInt() + 4) & 3;
        FOR(i, 4) count[i] = 0;

        a[n] = 0;
        b[0] = a[0];
        n++;
        FORE(i, 1, n) b[i] = (a[i] - a[i - 1] + 4) & 3;
        FOR(i, n) count[b[i]]++;

        //FOR(i, n) printf("%d ", a[i]);
        //printf("\n");

        int total = 0;
        int plus = 0;
        FOR(i, n) {
            if (b[i] != 0) {
                if (total >= b[i]) { total -= b[i]; plus += b[i];} else total += 4 - b[i];
            }
        }
        //printf("Total: %d %d\n", total, plus);


        int steps = 0;
        while (count[0] != n) {
            //FOR(i, n) printf("%d ", b[i]);
            //printf("\n");
            bool ok = check(3, 1);
            if (!ok) ok = check(3, 2);
            if (!ok) ok = check(2, 1);
            if (!ok) ok = check(1, 1);
            if (!ok) ok = check(3, 3);
            if (!ok) ok = check(2, 2);
            if (!ok) ok = check(2, 3);
            if (!ok) ok = check(1, 2);
            if (!ok) ok = check(1, 3);
            if (!ok) exit(-1);
            steps++;
        }
        int steps1 = steps;
        n--;

        FOR(i, n) a2[i] = a[n - 1 - i];
        FOR(i, n) a[i] = a2[i];
        a[n] = 0;
        b[0] = a[0];
        n++;
        FORE(i, 1, n) b[i] = (a[i] - a[i - 1] + 4) & 3;
        FOR(i, 4) count[i] = 0;
        FOR(i, n) count[b[i]]++;


        steps = 0;
        while (count[0] != n) {
            //FOR(i, n) printf("%d ", b[i]);
            //printf("\n");
            bool ok = check(3, 1);
            if (!ok) ok = check(3, 2);
            if (!ok) ok = check(2, 1);
            if (!ok) ok = check(1, 1);
            if (!ok) ok = check(3, 3);
            if (!ok) ok = check(2, 2);
            if (!ok) ok = check(2, 3);
            if (!ok) ok = check(1, 2);
            if (!ok) ok = check(1, 3);
            if (!ok) exit(-1);
            steps++;
        }
        int steps2 = steps;
        if (steps1 < steps) steps = steps1;

        /*FOR(i, n) {
            if (b[i] != 0) {
                count[b[i]]--;
                while (b[i] != 0) {
                    if (count[1] != 0) {
                        int index = findFirst(i + 1, 1);
                        b[index] = 0;
                        count[1]--;
                    } else if (count[3] != 0 || count[2] != 0) {
                        int index = findLast();
                        //int orig = b[index];
                        b[index]--;
                        //count[orig]--;
                        //count[orig-1]++;
                    } else if (count[2] != 0) {
                        int index = findLast(2);
                        b[index]--;
                        count[2]--;
                        count[1]++;
                    }
                    b[i]++;
                    b[i] &= 3;
                    steps++;
                }
            }
        }*/
        printf("%d\n", steps);
    }
}

