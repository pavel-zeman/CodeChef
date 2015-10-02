// Chooses best position based on score 
// https://www.codechef.com/SEPT15/problems/CHTTRS
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


char ccc = 0;
int getInt() {
    int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) {
        ccc = getc_unlocked(stdin);
        if (ccc == 'G') return -1;
    }
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}

char getCharacter() {
    while (!(ccc >= 'a' && ccc <= 'z')) ccc = getc_unlocked(stdin);
    char r = ccc;
    ccc = getc_unlocked(stdin);
    return r;
}


int getSignedInt() {
    int r = 0;
    while (!(ccc == '-' || (ccc >= '0' && ccc <= '9'))) ccc = getc_unlocked(stdin);
    bool minus = ccc == '-';
    if (minus) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

long long int getLongLongInt() {
    long long int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}


template <class type> void print(type a) {
    if (a < 0) {
        putc_unlocked('-', stdout);
        a = -a;
    }
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
    putc_unlocked('\n', stdout);
}

void printString(const char *str) {
    while (*str) putc_unlocked(*str++, stdout);
    putc_unlocked('\n', stdout);
}


void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}


#define NORMAL 1
#define FIXED 2
#define FIGURES 7
#define GRID_SIZE 4
#define FIELD_SIZE 15

char figureData[FIGURES][GRID_SIZE][GRID_SIZE] = {
    {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}
};

char figureRorations[FIGURES][4][GRID_SIZE][GRID_SIZE];
int width[FIGURES][4];
int height[FIGURES][4];
int cellsOccupied[FIGURES][4][GRID_SIZE];
int rotations[FIGURES] = {2, 4, 4, 1, 2, 4, 2};
char field[16][17];
int fieldOccupied[FIELD_SIZE];


void moveUp(int figure, int rotation) {
    bool empty = true;
    while (empty) {
        FOR(i, GRID_SIZE)
            if (figureRorations[figure][rotation][0][i]) {
                empty = false;
                break;
            }
        if (empty) {
            FOR(i, GRID_SIZE - 1) FOR(j, GRID_SIZE)
                figureRorations[figure][rotation][i][j] = figureRorations[figure][rotation][i + 1][j];
            FOR(i, GRID_SIZE)
                figureRorations[figure][rotation][GRID_SIZE - 1][i] = 0;
        }
    }
}

void moveLeft(int figure, int rotation) {
    bool empty = true;
    while (empty) {
        FOR(i, GRID_SIZE)
            if (figureRorations[figure][rotation][i][0]) {
                empty = false;
                break;
            }
        if (empty) {
            FOR(i, GRID_SIZE) FOR(j, GRID_SIZE - 1)
                figureRorations[figure][rotation][i][j] = figureRorations[figure][rotation][i][j + 1];
            FOR(i, GRID_SIZE)
                figureRorations[figure][rotation][i][GRID_SIZE - 1] = 0;
        }
    }
}

void calcWidth(int figure, int rotation) {
    int right = GRID_SIZE - 1;
    bool empty = true;
    while (empty) {
        FOR(i, GRID_SIZE)
            if (figureRorations[figure][rotation][i][right]) {
                empty = false;
                break;
            }
        if (empty) right--;
    }
    width[figure][rotation] = right + 1;
}

void calcHeight(int figure, int rotation) {
    int bottom = GRID_SIZE - 1;
    bool empty = true;
    while (empty) {
        FOR(i, GRID_SIZE)
            if (figureRorations[figure][rotation][bottom][i]) {
                empty = false;
                break;
            }
        if (empty) bottom--;
    }
    height[figure][rotation] = bottom + 1;
}

void calcCellsOccupied(int figure, int rotation) {
    FOR(i, height[figure][rotation])
        FOR(j, GRID_SIZE)
            cellsOccupied[figure][rotation][i] += figureRorations[figure][rotation][i][j];
}

void switchRotations(int figure, int rotation1, int rotation2) {
    char temp[GRID_SIZE][GRID_SIZE];
    FOR(i, GRID_SIZE) FOR(j, GRID_SIZE)
        temp[i][j] = figureRorations[figure][rotation1][i][j];
    FOR(i, GRID_SIZE) FOR(j, GRID_SIZE)
        figureRorations[figure][rotation1][i][j] = figureRorations[figure][rotation2][i][j];
    FOR(i, GRID_SIZE) FOR(j, GRID_SIZE)
        figureRorations[figure][rotation2][i][j] = temp[i][j];
}

void calcRotations() {
    FOR(i, FIGURES) {
        FOR(j, GRID_SIZE) FOR(k, GRID_SIZE) figureRorations[i][0][j][k] = figureData[i][j][k];
        FORE(j, 1, rotations[i]) {
            FOR(k, GRID_SIZE) FOR(l, GRID_SIZE)
                figureRorations[i][j][k][l] = figureRorations[i][j - 1][3 - l][k];
            moveUp(i, j);
            moveLeft(i, j);
        }
    }
    // fix the rotations for second figure
    switchRotations(1, 1, 2);
    switchRotations(1, 1, 3);

    FOR(i, FIGURES) {
        FOR(j, rotations[i]) {
            calcHeight(i, j);
            calcWidth(i, j);
            calcCellsOccupied(i, j);
        }
    }

}

void printFigures() {
    FOR(i, FIGURES) {
        FOR(j, rotations[i]) {
            printf("%d %d, %d %d\n", i, j, width[i][j], height[i][j]);
            FOR(k, height[i][j]) {
                FOR(l, width[i][j])
                    printf("%c", figureRorations[i][j][k][l] ? '#' : ' ');
                printf("\n");
            }
        }
    }
}

// add walls
void initField() {
    FOR(i, FIELD_SIZE) field[i][0] = field[i][FIELD_SIZE + 1] = 1;
    FOR(i, FIELD_SIZE + 2) field[FIELD_SIZE][i] = 1;
}

bool isOk(int figure, int rotation, int c, int y) {
    FOR(i, height[figure][rotation])
        if (i + y >= 0) {
            FOR(j, width[figure][rotation])
                if (figureRorations[figure][rotation][i][j] && field[i + y][j + c])
                    return false;
        }
    return true;
}

int calcLost(int figure, int rotation, int c, int y) {
    int result = 0;
    FOR(i, width[figure][rotation]) {
        int j = 0;
        while (j < GRID_SIZE && (!figureRorations[figure][rotation][j][i] || fieldOccupied[j + y] + cellsOccupied[figure][rotation][j] == FIELD_SIZE)) j++;
        if (j == GRID_SIZE) continue;
        while (j < GRID_SIZE && figureRorations[figure][rotation][j][i]) j++;
        while (!field[y + j][c + i]) {
            j++;
            result++;
        }
    }
    return result;
}

int calcCleared(int figure, int rotation, int c, int y) {
    int result = 0;
    FOR(i, height[figure][rotation]) {
        if (fieldOccupied[i + y] + cellsOccupied[figure][rotation][i] == FIELD_SIZE) result++;
    }
    return result;
}

void apply(int figure, int rotation, int c, int y) {
    FOR(i, height[figure][rotation])
        FOR(j, width[figure][rotation])
            if (figureRorations[figure][rotation][i][j]) field[y + i][c + j] = 1;
    bool clear = false;
    FOR(i, height[figure][rotation]) {
        fieldOccupied[i + y] += cellsOccupied[figure][rotation][i];
        if (fieldOccupied[i + y] == FIELD_SIZE) clear = true;
    }
    if (clear) {
        for(int i = FIELD_SIZE - 1; i >= 0; i--) {
            if (fieldOccupied[i] == FIELD_SIZE) {
                for(int j = i; j > 0; j--) {
                    fieldOccupied[j] = fieldOccupied[j - 1];
                    FOR(k, FIELD_SIZE) field[j][k + 1] = field[j - 1][k + 1];
                }
                FOR(k, FIELD_SIZE) field[0][k + 1] = 0;
                fieldOccupied[0] = 0;
                i++;
            }
        }
    }
}

int sqr(int a) {
    return a * a;
}

int calcWell() {
    int result = 0;
    FOR(i, FIELD_SIZE) {
        int c = i + 1;
        int y = 0;
        while (!field[y][c]) y++;
        y--;
        int yStart = y;
        while (y >= 0 && field[y][c - 1] && field[y][c + 1]) y--;
        if (yStart - y >= 2) result += sqr(yStart - y - 1);
    }
    return result;
}

int calcWell(int figure, int rotation, int c, int y) {
    FOR(i, height[figure][rotation])
        FOR(j, width[figure][rotation])
            if (figureRorations[figure][rotation][i][j]) field[y + i][c + j] = 1;

    int result = calcWell();

    FOR(i, height[figure][rotation])
        FOR(j, width[figure][rotation])
            if (figureRorations[figure][rotation][i][j]) field[y + i][c + j] = 0;

    return result;
}


struct Decision {
    int c;
    int y;
    int rot;

    int score;
} decision;

int currentWell = 0;

void printField() {
    printf("Well: %d\n", currentWell);
    FOR(i, FIELD_SIZE + 1) {
        FOR(j, FIELD_SIZE + 2) printf("%c", field[i][j] ? '#' : ' ');
        printf("\n");
    }
}

int main(void) {
    calcRotations();
    initField();

    int steps = 0;
    while (true) {
        steps++;
        int type = getInt();
        if (type == -1) break;

        int figure = getInt() - 1;
        int rot = 0;
        if (type == FIXED) rot = getCharacter() - 'a';

        decision.score = -1;
        FOR(r, rotations[figure]) {
            if ((type == FIXED && r == rot) || type == NORMAL) {
                FOR(c, FIELD_SIZE - width[figure][r] + 1) {
                    int y = -height[figure][r] + 1;
                    while (isOk(figure, r, c + 1, y)) y++;
                    y--;
                    if (y >= 0) {
                        int lost = calcLost(figure, r, c + 1, y);
                        int cleared = calcCleared(figure, r, c + 1, y);
                        int well = calcWell(figure, r, c + 1, y) - currentWell;
                        int score = 1000 - 3 * sqr(lost) - well + cleared * FIELD_SIZE + y;

                        //printf("Testing rotation %d, row: %d, column: %d, clear: %d, lost: %d\n", r, y, c, cleared, lost);
                        if (score > decision.score ||
                            (score == decision.score && y > decision.y)) {
                            decision.c = c;
                            decision.y = y;
                            decision.rot = r;
                            decision.score = score;
                        }
                    }
                }
            }
        }
        if (decision.score < 0) {
            printf("x 0 0\n");
            break;
        } else {
            printf("%c %d %d\n", decision.rot + 'a', decision.y + height[figure][decision.rot], decision.c + 1);
            //printf("Cleared: %d, Lost: %d\n", decision.rowsCleared, decision.cellsLost);
            apply(figure, decision.rot, decision.c + 1, decision.y);
            currentWell = calcWell();
            //printField();
        }
        fflush(stdout);
        //if (steps > 10) fail();
    }
}

