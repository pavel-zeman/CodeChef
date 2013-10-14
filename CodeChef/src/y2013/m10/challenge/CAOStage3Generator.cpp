// Generates assignments for this problem
// http://www.codechef.com/OCT13/problems/CAOS3
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_SIZE 60
#define MONSTER '^'

int r, c;
char map[MAX_SIZE][MAX_SIZE];
bool monster[MAX_SIZE][MAX_SIZE];
int result[MAX_SIZE - 2][MAX_SIZE - 2][MAX_SIZE - 2][MAX_SIZE - 2];
int totalMonsters;



int main(void) {
    srand(time(NULL));
    int t = 1000;
    printf("%d\n", t);
    FOR(tt, t) {
        int r = 5 + 4;
        int c = 5 + 3;
        printf("%d %d\n", r, c);
        FOR(i, r) map[i][c] = 0;
        FOR(i, r) FOR(j, c) map[i][j] = rand() % 20 <= 0 ? '#' : '^';
        FOR(i, r) printf("%s\n", map[i]);

    }
}
