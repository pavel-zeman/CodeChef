// The solution exists for all m >= 3 and cycle size >= 3. However, there is one special case, which must be handled (m = 4 and cycle size = 3).
// http://www.codechef.com/JULY14/problems/LUCKG
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

#define MAX_N 1000


int p[MAX_N];
bool used[MAX_N];
int result[MAX_N][MAX_N];


int special[][4] = {{1, 3, 10, 11}, {2, 7, 8, 9}, {4, 5, 6, 12}};

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

// fast print
void print(int a) {
    if (a == 0) {
        putc_unlocked('0', stdout);
    } else {
        char result[20];
        int resSize = 0;
        while (a > 0) {
            result[resSize++] = '0' + a % 10;
            a /= 10;
        }
        while (--resSize >= 0) putc_unlocked(result[resSize], stdout);
    }
    putc_unlocked(' ', stdout);
}

void print(char c) {
    putc_unlocked(c, stdout);
}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt(), m = getInt();
        FOR(i, n) p[i] = getInt();

        bool possible = false;
        if (m >= 3) {
            int lastValue = 1;

            possible = true;
            FOR(i, n) used[i] = false;

            FOR(i, n) if (!used[i]) {
                int perm[MAX_N];
                int permSize = 1;
                perm[0] = i;
                used[i] = true;
                int curr = p[i];

                while (curr != i) {
                    used[curr] = true;
                    perm[permSize++] = curr;
                    curr = p[curr];
                }

                if (permSize >= 3) {
                    if (permSize == 3 && m == 4) {
                        FOR(j, m) {
                            FOR(k, permSize) {
                                result[perm[k]][j] = special[k][j] + lastValue - 1;
                            }
                        }
                        lastValue += permSize * m;
                    } else {
                        int lastPos = 0;
                        FOR(j, m) {
                            FOR(k, permSize) {
                                result[perm[lastPos--]][j] = lastValue++;
                                if (lastPos < 0) lastPos += permSize;
                            }
                            if (++lastPos >= permSize) lastPos -= permSize;
                        }
                    }
                } else {
                    possible = false;
                    break;
                }
            }
        }
        if (possible) {
            FOR(i, n) {
                FOR(j, m) print(result[i][j]);
                print('\n');
            }
        } else {
            printf("No Solution\n");
        }
    }
}
