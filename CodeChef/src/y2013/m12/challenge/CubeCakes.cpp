// O(n^4) algorithm, which simply checks all the possible sub-cubes with a lot of memoization
// http://www.codechef.com/DEC13/problems/CUBE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 42


char cube1[MAX_N][MAX_N][MAX_N], cube2[MAX_N][MAX_N][MAX_N];

char common1[MAX_N][MAX_N][MAX_N], common2[MAX_N][MAX_N][MAX_N], common3[MAX_N][MAX_N][MAX_N];
int common21[MAX_N][MAX_N][MAX_N], common22[MAX_N][MAX_N][MAX_N], common23[MAX_N][MAX_N][MAX_N];
int minRequired[MAX_N + 2];

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

char getChar() {
    while (!isalpha(c)) c = getc_unlocked(stdin);
    char result = c;
    c = getc_unlocked(stdin);
    return result;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt(), p = getInt();
        FOR(i, n) FOR(j, n) FOR(k, n) cube1[i][j][k] = getChar();
        FOR(i, n) FOR(j, n) FOR(k, n) cube2[i][j][k] = getChar();

        FOR(i, n + 2) {
            int m = i * i * i * p;
            if (m % 100 == 0) m /= 100; else m = m / 100 + 1;
            minRequired[i] = m;
        }

        FOR(i, n) FOR(j, n) {
            int c1 = 0;
            int c2 = 0;
            int c3 = 0;
            common1[i][j][0] = common2[i][j][0] = common3[i][j][0];
            FOR(k, n) {
                c1 += cube1[i][j][k] == cube2[i][j][k];
                c2 += cube1[i][k][j] == cube2[i][k][j];
                c3 += cube1[k][i][j] == cube2[k][i][j];
                common1[i][j][k + 1] = c1;
                common2[i][j][k + 1] = c2;
                common3[i][j][k + 1] = c3;
            }

        }
        FOR(i, n) FOR(j, n) {
            int c1 = 0;
            int c2 = 0;
            int c3 = 0;
            FOR(k, n) {
                c1 += common1[i][k][j + 1];
                c2 += common1[k][i][j + 1];
                c3 += common2[k][i][j + 1];
                common21[i][j][k] = c1;
                common22[i][j][k] = c2;
                common23[i][j][k] = c3;
            }
        }


        //printf("Checking %d %d %c %c\n", n, p, cube1[0][0][0], cube2[0][0][0]);
        int maxS = -1;
        int count = 0;

        FOR(i, n) FOR(j, n) FOR(k, n) {
            int maxL = min(n - i, n - j);
            maxL = min(maxL, n - k);
            int common = 0;
            if (maxL - 1 >= maxS) {
                FOR(l, maxL) {
                    /*FOR(a, l) FOR(b, l) {
                        common += cube1[i + l][j + a][k + b] == cube2[i + l][j + a][k + b];
                        common += cube1[i + a][j + l][k + b] == cube2[i + a][j + l][k + b];
                        common += cube1[i + a][j + b][k + l] == cube2[i + a][j + b][k + l];
                    }
                    FOR(a, l) {
                        common += cube1[i + l][j + l][k + a] == cube2[i + l][j + l][k + a];
                        common += cube1[i + l][j + a][k + l] == cube2[i + l][j + a][k + l];
                        common += cube1[i + a][j + l][k + l] == cube2[i + a][j + l][k + l];
                    }
                    common += cube1[i + l][j + l][k + l] == cube2[i + l][j + l][k + l];*/
                    /*FOR(a, l) {
                        common += common1[i + l][j + a][k + l - 1];
                        common += common1[i + a][j + l][k + l - 1];
                        common += common2[i + a][k + l][j + l - 1];
                        if (k > 0) common -= common1[i + l][j + a][k - 1] + common1[i + a][j + l][k - 1];
                        if (j > 0) common -= common2[i + a][k + l][j - 1];
                    }*/
                    if (l > 0) {
                        common += common21[i + l][k + l - 1][j + l - 1];
                        if (j > 0) common -= common21[i + l][k + l - 1][j - 1];
                        common += common22[j + l][k + l - 1][i + l - 1];
                        if (i > 0) common -= common22[j + l][k + l - 1][i - 1];
                        common += common23[k + l][j + l - 1][i + l - 1];
                        if (i > 0) common -= common23[k + l][j + l - 1][i - 1];

                        if (k > 0) {
                            common -= common21[i + l][k - 1][j + l - 1];
                            if (j > 0) common += common21[i + l][k - 1][j - 1];
                            common -= common22[j + l][k - 1][i + l - 1];
                            if (i > 0) common += common22[j + l][k - 1][i - 1];
                        }
                        if (j > 0) {
                            common -= common23[k + l][j - 1][i + l - 1];
                            if (i > 0) common += common23[k + l][j - 1][i - 1];
                        }

                        common += common1[i + l][j + l][k + l + 1] - common1[i + l][j + l][k];
                        common += common2[i + l][k + l][j + l] - common2[i + l][k + l][j];
                        common += common3[j + l][k + l][i + l] - common3[j + l][k + l][i];
                    } else {
                        common += cube1[i + l][j + l][k + l] == cube2[i + l][j + l][k + l];
                    }


                    if (l >= maxS && common >= minRequired[l + 1]) {
                        if (l > maxS) maxS = l, count = 0;
                        count++;
                    }
                }
            }
        }
        //printf("%d ", total);
        if (maxS == -1) printf("-1\n"); else printf("%d %d\n", maxS + 1, count);
    }
}

