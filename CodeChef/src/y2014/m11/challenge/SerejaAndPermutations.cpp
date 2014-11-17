// Deduplicate input permutations, take them one by one and consider each of them as the last one (i.e. the one with the number N removed). Calculate the position of number N and then test, if it is valid (i.e. generate all the q[i] permutations).
// http://www.codechef.com/NOV14/problems/SEAPERM2
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

#define MAX_N 300

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

int n, n2;
int q[MAX_N][MAX_N];
int order[MAX_N];

struct perm {
    int data[MAX_N];
    int count;
} perms[MAX_N];

struct lastNumberType {
    int pos;
    int count;
} lastNumber[10];

int lastNumberCount;

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

int cmp(int *a, int *b) {
    FOR(i, n - 1) if (a[i] != b[i]) return a[i] - b[i];
    return 0;
}

int cmp(const void *p1, const void *p2) {
    int *i1 = (int *)p1;
    int *i2 = (int *)p2;
    return cmp(q[*i1], q[*i2]);
}

void copy(int *dst, int *src) {
    memcpy(dst, src, sizeof(int) * (n - 1));
}

int find(int *data) {
    int a = 0, b = n2 - 1;
    while (a <= b) {
        int mid = (a + b) >> 1;
        int r = cmp(data, perms[mid].data);
        if (r == 0) return mid;
        if (r < 0) b = mid - 1; else a = mid + 1;
    }
    return -1;
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) FOR(j, n - 1) q[i][j] = getInt();
        FOR(i, n) order[i] = i;
        // sort data
        qsort(order, n, sizeof(order[0]), cmp);

        // remove duplicates
        n2 = 0;
        copy(perms[0].data, q[order[0]]);
        perms[0].count = 1;
        FORE(i, 1, n) {
            if (!cmp(q[order[i]], q[order[i - 1]])) perms[n2].count++; else {
                n2++;
                copy(perms[n2].data, q[order[i]]);
                perms[n2].count = 1;
            }
        }
        n2++;

        // calculate position of last number
        int freq[MAX_N];
        FOR(i, n) freq[i] = 0;
        FOR(i, n2)
            FOR(j, n - 1) if (perms[i].data[j] == n - 1) {
                freq[j] += perms[i].count;
                break;
            }

        lastNumberCount = 0;
        FOR(i, n) if (freq[i] > 0) {
            lastNumber[lastNumberCount].pos = i;
            lastNumber[lastNumberCount].count = freq[i];
            lastNumberCount++;
        }

        // crash, if the assumption is incorrect
        if (lastNumberCount > 3) *((char *)0) = 0;

        bool found = false;
        // now try each permutation as the last one
        FOR(i, n2) {
            // find the location of the last number
            int lastPos = 0;
            while (perms[i].data[lastNumber[lastPos].pos] != n - 1) lastPos++;
            lastNumber[lastPos].count--;

            int j = 0;
            while (lastNumber[j].count == 0) j++;
            int a = lastNumber[j].pos;
            int b = lastNumber[j].pos + 1;
            j++;
            while (j < lastNumberCount) {
                if (lastNumber[j].count > 0) a = lastNumber[j].pos;
                j++;
            }
            if (a <= b) {
                FORE(j, a, b + 1) {
                    int localPerm[MAX_N];

                    // generate permutation to test
                    FOR(k, j) localPerm[k] = perms[i].data[k];
                    localPerm[j] = n;
                    FORE(k, j + 1, n) localPerm[k] = perms[i].data[k - 1];

                    // and test it
                    int remains[MAX_N];
                    FOR(k, n2) remains[k] = perms[k].count;
                    bool localFound = true;
                    FORE(k, 1, n + 1) {
                        int testPerm[MAX_N];
                        int dst = 0;
                        FOR(src, n) {
                            if (localPerm[src] > k) testPerm[dst++] = localPerm[src] - 1;
                            else if (localPerm[src] < k) testPerm[dst++] = localPerm[src];
                        }
                        int index = find(testPerm);
                        if (index < 0 || remains[index] == 0) {
                            localFound = false;
                            break;
                        }
                        remains[index]--;
                    }
                    if (localFound) {
                        FOR(i, n) printf("%d ", localPerm[i]);
                        printf("\n");
                        found = true;
                        break;
                    }
                }

            }
            lastNumber[lastPos].count--;
            if (found) break;
        }
    }
}

