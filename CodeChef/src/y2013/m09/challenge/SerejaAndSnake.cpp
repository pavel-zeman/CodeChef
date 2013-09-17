// No magic here - simply go row by row or column by column (try all 8 possibilities and choose the best one)
// http://www.codechef.com/SEPT13/problems/SEASNAKE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define APPLES 900
#define MAX_PROGRAM (900 * 900)
#define MAX_N 30

int n, m;

int dirx[] = {-1, 1, 0, 0};
int diry[] = {0, 0, -1, 1};
int board[MAX_N][MAX_N];

struct apple {
    int x, y;
} apples[APPLES];


int tries[8][4] = {
    {1, 3, 0, 3}, {0, 3, 1, 3}, {1, 2, 0, 2}, {0, 2, 1, 2},
    {3, 1, 2, 1}, {3, 0, 2, 0}, {2, 1, 3, 1}, {2, 0, 3, 0}
};

int tempProgram[MAX_PROGRAM];
int tempProgramCount;
int program[MAX_PROGRAM];
int programCount;



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


void crash() {
    *(char *)0 = 0;
}

int main(void) {
    n = getInt();
    m = getInt();
    FOR(i, n * m - 1) {
        apples[i].x = getInt();
        apples[i].y = getInt();
    }

    int programCount = INT_MAX;
    FOR(i, (int)(sizeof(tries) / sizeof(tries[0]))) {
    //FOR(i, 1) {
        int x = 0;
        int y = 0;
        int apple = 0;
        int pos = 0;
        int *plan = tries[i];
        tempProgramCount = 0;
        FOR(j, n) FOR(k, m) board[j][k] = 0;

        if (!(n % 2 == 1 && dirx[plan[1]] != 0 || m % 2 == 1 && diry[plan[1]] != 0)) {
            while (apple < n * m - 1) {
                int nextX = x + dirx[plan[pos]];
                int nextY = y + diry[plan[pos]];
                if (nextX < 0 || nextX >= n || nextY < 0 || nextY >= m) {
                    pos++;
                    nextX = (x + dirx[plan[pos]] + n) % n;
                    nextY = (y + diry[plan[pos]] + m) % m;
                    if (nextX == x && nextY == y) {
                        pos--;
                        nextX = (x + dirx[plan[pos]] + n) % n;
                        nextY = (y + diry[plan[pos]] + m) % m;
                        tempProgram[tempProgramCount++] = plan[pos];
                    } else {
                        tempProgram[tempProgramCount++] = plan[pos];
                        pos = (pos + 1) & 3;
                    }
                } else {
                    tempProgram[tempProgramCount++] = plan[pos];
                }
                if (board[nextX][nextY] > tempProgramCount - apple - 1) {
                    printf("%d %d %d %d %d\n", nextX, nextY, board[nextX][nextY], tempProgramCount, apple);
                    crash();
                }
                //printf("%d %d: ", nextX, nextY);*/
                x = nextX;
                y = nextY;
                board[x][y] = tempProgramCount;
                if (apples[apple].x == x && apples[apple].y == y) apple++;
            }
            if (tempProgramCount < programCount) {
                programCount = tempProgramCount;
                memcpy(program, tempProgram, programCount * sizeof(int));
            }
        }
    }
    /*FOR(i, programCount - 1) {
        if (program[i] == 0 && program[i + 1] == 1 || program[i] == 1 && program[i + 1] == 0 || program[i] == 2 && program[i + 1] == 3 || program[i] == 3 && program[i + 1] == 2) crash();
    }*/
    printf("%d\n", programCount);
    FOR(i, programCount - 1) printf("%d ", program[i]);
    printf("%d\n", program[programCount - 1]);
}
