// Brute-force algorithm with expontential time complexity
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
bool lava[MAX_SIZE][MAX_SIZE];
int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};


int generateMonsters() {
    FOR(i, r) FOR(j, c) monster[i][j] = false, lava[i][j] = false;
    int totalMonsters = 0;
    FORE(i, 2, r - 2) FORE(j, 2, c - 2) {
        if (map[i][j] == MONSTER) {
            int count = 0;
            FORE(k, 1, 3) {
                count += map[i - k][j] == MONSTER;
                count += map[i + k][j] == MONSTER;
                count += map[i][j - k] == MONSTER;
                count += map[i][j + k] == MONSTER;
            }
            if (count == 8) {
                monster[i][j] = true;
                totalMonsters++;
            }
        }
    }
    return totalMonsters;
}

bool wins(int monsters, int level) {
    if (monsters == 0) return false;
    FOR(i, r) FOR(j, c) {
        if (monster[i][j] && !lava[i][j]) {
            int counts[4];
            int subMonsters = 1;
            FOR(k, 4) {
                int rr = i + directions[k][0];
                int cc = j + directions[k][1];
                counts[k] = 0;
                while (rr >= 0 && rr < r && cc >= 0 && cc < c && !lava[rr][cc]) {
                    counts[k]++;
                    lava[rr][cc] = true;
                    if (monster[rr][cc]) subMonsters++;
                    rr += directions[k][0];
                    cc += directions[k][1];
                }
            }
            lava[i][j] = true;
            bool result = wins(monsters - subMonsters, level + 1);
            FOR(k, 4) {
                int rr = i;
                int cc = j;
                FOR(l, counts[k]) {
                    rr += directions[k][0];
                    cc += directions[k][1];
                    lava[rr][cc] = false;
                }
            }
            lava[i][j] = false;
            if (!result) return true;
        }
    }
    return false;
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        scanf("%d%d", &r, &c);
        FOR(i, r) scanf("%s", map[i]);

        int m = generateMonsters();
        //printf("Total monsters: %d\n", m);
        printf("%s\n", wins(m, 0) ? "Asuna" : "Kirito");
    }
}
