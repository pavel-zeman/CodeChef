// Unfortunately this simple algorithm does not work
// http://www.codechef.com/OCT13/problems/CAOS3
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_SIZE 23
#define MONSTER '^'

int r, c;
char map[MAX_SIZE][MAX_SIZE];
bool monster[MAX_SIZE][MAX_SIZE];
int result[MAX_SIZE - 2][MAX_SIZE - 2][MAX_SIZE - 2][MAX_SIZE - 2];
int totalMonsters;


int solve(int row, int column, int rows, int columns) {
    if (rows == 0 || columns == 0) return 0;
    if (result[row][column][rows][columns] != -1) return result[row][column][rows][columns];
    int data = 0;
    FOR(i, rows) FOR(j, columns) {
        if (monster[row + i][column + j]) {
            int temp[4];
            temp[0] = solve(row, column, i, j);
            temp[1] = solve(row + i + 1, column, rows - i - 1, j);
            temp[2] = solve(row, column + j + 1, i, columns - j - 1);
            temp[3] = solve(row + i + 1, column + j + 1, rows - i - 1, columns - j - 1);

            int oddCount = 0;
            int bothCount = 0;
            FOR(k, 4) {
                if (temp[k] == 1) oddCount ^= 1;
                else if (temp[k] == 3) bothCount ^= 1;
            }
            int temp2;
            /*if (oddCount == 1) {
                temp2 = bothCount == 0 ? 2 : 1;
            } else {
                temp2 = bothCount == 0 ? 1 : 2;
            }*/
            if (bothCount == 1) temp2 = 2;
            else temp2 = oddCount == 1 ? 2 : 1;
            //if (rows == r && columns == c && temp2 == 2) printf("%d %d, ", i, j);
            data |= temp2;
            //if (row == 3 && column == 5 && rows == 5 && columns == 3) printf("Data: %d %d = %d\n", row + i, column + j, temp2);
        }
    }
    //printf("%d %d %d %d = %d\n", row, column, rows, columns, data);
    return result[row][column][rows][columns] = data;
}

void generateMonsters() {
    FOR(i, r) FOR(j, c) monster[i][j] = false;
    FORE(i, 2, r - 2) FORE(j, 2, c - 2) {
        if (map[i][j] == MONSTER) {
            int count = 0;
            FORE(k, 1, 3) {
                count += map[i - k][j] == MONSTER;
                count += map[i + k][j] == MONSTER;
                count += map[i][j - k] == MONSTER;
                count += map[i][j + k] == MONSTER;
            }
            if (count == 8) { monster[i][j] = true; totalMonsters++; }
        }
    }

    char test[MAX_SIZE][MAX_SIZE];
    FOR(i, r) FOR(j, c) {
        test[i][j] = monster[i][j] ? '^' : '.';
    }
    FOR(i, r) {
        test[i][c] = 0;
        printf("%s\n", test[i]);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        scanf("%d%d", &r, &c);
        FOR(i, r) scanf("%s", map[i]);

        totalMonsters = 0;
        generateMonsters();

        FOR(i, r) FOR(j, c) FOR(k, r - i + 1) FOR(l, c - j + 1) result[i][j][k][l] = -1;

        int res = solve(0, 0, r, c);
        //printf("%d %s\n", res, res == 1 || res == 3 ? "Asuna" : "Kirito");
        printf("%s\n", res == 1 || res == 3 ? "Asuna" : "Kirito");

        /*printf("3 5 5 3 %d\n", result[3][5][5][3]);
        printf("3 0 5 5 %d\n", result[3][0][5][5]);
        printf("3 4 5 4 %d\n", result[3][4][5][4]);*/
    }
}
