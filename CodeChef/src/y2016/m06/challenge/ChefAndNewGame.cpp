// Try all possible positions for each group of 3 pieces.
// https://www.codechef.com/JUNE16/problems/CHNWGM
#include <bits/stdc++.h>
#include <sys/resource.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int
#define MOD 1000000007


char ccc = 0;
int getInt() {
    int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}

int getString(char *start) {
    char *data = start;
    while (!(ccc > ' ' && ccc <= '~')) ccc = getc_unlocked(stdin);
    while (ccc > ' ' && ccc <= '~') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *data = 0;
    return data - start;
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

int power(int a, int b) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % MOD;
        sq = sq * (LLI)sq % MOD;
        b >>= 1;
    }
    return result;
}

int inv(int a) {
    return power(a, MOD - 2);
}

void fail() {
    *((char *)0) = 0;
}


int pieces[][10][2] = {
    {{0,0}, {-1,-1}}, // 1
    {{0,0}, {1,0}, {-1,-1}}, // 2
    {{0,0}, {0,1}, {-1,-1}}, // 3
    {{0,0}, {1,0}, {2,0}, {-1,-1}}, // 4
    {{0,0}, {0,1}, {0,2}, {-1,-1}}, // 5
    {{0,0}, {1,0}, {2,0}, {3, 0}, {-1,-1}}, // 6
    {{0,0}, {0,1}, {0,2}, {0, 3}, {-1,-1}}, // 7
    {{0,0}, {1,0}, {2,0}, {3, 0}, {4, 0}, {-1,-1}}, // 8
    {{0,0}, {0,1}, {0,2}, {0, 3}, {0, 4}, {-1,-1}}, // 9
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {-1,-1}}, // 10
    {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}, {-1,-1}}, // 11
    {{0,0}, {0,1}, {0,2}, {1, 2}, {2, 2}, {-1,-1}}, // 12
    {{2,0}, {2,1}, {2,2}, {1, 2}, {0, 2}, {-1,-1}}, // 13
    {{0,0}, {1,0}, {2,0}, {2, 1}, {2, 2}, {-1,-1}}, // 14
    {{0,0}, {1,0}, {2,0}, {0, 1}, {0, 2}, {-1,-1}}, // 15
    {{0,0}, {1,0}, {0, 1}, {-1,-1}}, // 16
    {{0,0}, {0,1}, {1, 1}, {-1,-1}}, // 17
    {{1,0}, {1,1}, {0, 1}, {-1,-1}}, // 18
    {{0,0}, {1,0}, {1, 1}, {-1,-1}} // 19
};

int perms[][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

#define PIECES sizeof(pieces) / sizeof(pieces[0])
#define FIELD_SIZE 10
#define FULL_ROW 1023

int pieceSize[PIECES];
int height[PIECES];
int width[PIECES];

int field[FIELD_SIZE];
int pieceRow[PIECES][6];
int pieceColumnBlocks[PIECES][6];

int columnSize[FIELD_SIZE];

int p[3];

int maxValue;
int maxValue2;
int maxP[3];
int maxR[3], maxC[3];
int penalty[FIELD_SIZE + 1];
int numBits[1 << FIELD_SIZE];

int currP[3];
int currR[3], currC[3];


void printField() {
    printf("  ");
    FOR(i, FIELD_SIZE) printf("%d", columnSize[i]);
    printf("\n");
    FOR(i, FIELD_SIZE) {
        printf("%d ", numBits[field[i]]);
        int x = field[i];
        FOR(j, FIELD_SIZE) {
            printf(x & 1 ? "#" : ".");
            x >>= 1;
        }
        printf("\n");
    }
    printf("\n");
}


bool getField(int row, int column) {
    return (field[row] & (1 << column)) != 0;
}

int removeAll(bool *rowsToRemove, bool *columnsToRemove, int r1, int r2, int c1, int c2) {
    int rowsRemoved = 0, columnsRemoved = 0;
    FORE(i, r1, r2) rowsToRemove[i] = field[i] == FULL_ROW;
    FORE(i, c1, c2) columnsToRemove[i] = columnSize[i] == FIELD_SIZE;

    FORE(i, r1, r2)
        if (rowsToRemove[i]) {
            field[i] = 0;
            rowsRemoved++;
        }
    if (rowsRemoved > 0) FOR(i, FIELD_SIZE) columnSize[i] -= rowsRemoved;

    int removeMask = 0;
    FORE(i, c1, c2)
        if (columnsToRemove[i]) {
            removeMask |= 1 << i;
            columnSize[i] = 0;
            columnsRemoved++;
        }
    if (removeMask != 0) {
        removeMask = ~removeMask;
        FOR(i, FIELD_SIZE) field[i] &= removeMask;

    }
    return rowsRemoved * rowsRemoved + columnsRemoved * columnsRemoved + 5 * rowsRemoved * columnsRemoved;
}

int calcScore(int r1, int r2, int c1, int c2) {
    int rowsRemoved = 0, columnsRemoved = 0;
    FORE(i, r1, r2) if (field[i] == FULL_ROW) rowsRemoved++;
    FORE(i, c1, c2) if (columnSize[i] == FIELD_SIZE) columnsRemoved++;
    return rowsRemoved * rowsRemoved + columnsRemoved * columnsRemoved + 5 * rowsRemoved * columnsRemoved;
}

int removeAllFake(bool *rowsToRemove, bool *columnsToRemove, int r1, int r2, int c1, int c2) {
    int rowsRemoved = 0, columnsRemoved = 0;
    FORE(i, r1, r2) if (field[i] == FULL_ROW) {
        rowsToRemove[i] = true;
        field[i] = 0;
        rowsRemoved++;
    }

    FORE(i, c1, c2) columnsToRemove[i] = columnSize[i] == FIELD_SIZE;

    if (rowsRemoved > 0) {
        FOR(j, FIELD_SIZE) columnSize[j] -= rowsRemoved;
    }

    int removeMask = 0;
    FORE(i, c1, c2)
        if (columnsToRemove[i]) {
            removeMask |= 1 << i;
            columnSize[i] = 0;
            columnsRemoved++;
        }

    if (removeMask != 0) {
        removeMask = ~removeMask;
        FOR(i, FIELD_SIZE) field[i] &= removeMask;

    }
    return rowsRemoved * rowsRemoved + columnsRemoved * columnsRemoved + 5 * rowsRemoved * columnsRemoved;
}


/*int removeAllFake(bool *rowsToRemove, bool *columnsToRemove, int r1, int r2, int c1, int c2, int *rr, int *rc) {
    int rowsRemoved = 0, columnsRemoved = 0;
    FORE(i, r1, r2) if (field[i] == FULL_ROW) {
        rowsToRemove[i] = true;
        field[i] = 0;
        rowsRemoved++;
    }

    FORE(i, c1, c2) columnsToRemove[i] = columnSize[i] == FIELD_SIZE;

    if (rowsRemoved > 0) {
        FOR(j, FIELD_SIZE) columnSize[j] -= rowsRemoved;
    }

    int removeMask = 0;
    FORE(i, c1, c2)
        if (columnsToRemove[i]) {
            removeMask |= 1 << i;
            columnSize[i] = 0;
            columnsRemoved++;
        }

    if (removeMask != 0) {
        removeMask = ~removeMask;
        FOR(i, FIELD_SIZE) field[i] &= removeMask;

    }
    return rowsRemoved * rowsRemoved + columnsRemoved * columnsRemoved + 5 * rowsRemoved * columnsRemoved;
}*/



void revertRemoveAll(bool *rowsToRemove, bool *columnsToRemove, int r1, int r2, int c1, int c2) {
    int rowsRemoved = 0, columnsRemoved = 0;
    FORE(i, r1, r2)
        if (rowsToRemove[i]) {
            field[i] = FULL_ROW;
            rowsRemoved++;
            rowsToRemove[i] = false;
        }

    int removeMask = 0;
    FORE(i, c1, c2)
        if (columnsToRemove[i]) {
            removeMask |= 1 << i;
            columnSize[i] = FIELD_SIZE;
            columnsToRemove[i] = false;
            columnsRemoved++;
        }
    if (removeMask > 0) {
        FOR(i, FIELD_SIZE) field[i] |= removeMask;
    }

    if (rowsRemoved > 0) {
        FOR(j, FIELD_SIZE) if (columnSize[j] < FIELD_SIZE) columnSize[j] += rowsRemoved;
    }
}

void revertRemoveAllFake(bool *rowsToRemove, bool *columnsToRemove, int r1, int r2, int c1, int c2) {
    int rowsRemoved = 0;
    FORE(i, r1, r2)
        if (rowsToRemove[i]) {
            rowsToRemove[i] = false;
            rowsRemoved++;
            field[i] = FULL_ROW;
        }

    if (rowsRemoved > 0) {
        FOR(j, FIELD_SIZE) columnSize[j] += rowsRemoved;
    }

    int removeMask = 0;
    FORE(i, c1, c2)
        if (columnsToRemove[i]) {
            removeMask |= 1 << i;
            columnSize[i] = FIELD_SIZE;
            columnsToRemove[i] = false;
        }
    if (removeMask > 0) {
        FOR(i, FIELD_SIZE) field[i] |= removeMask;
    }
}



void place(int piece, int row, int column) {
    FOR(k, height[piece]) field[row + k] |= pieceRow[piece][k] << column;
    FOR(k, width[piece]) columnSize[column + k] += pieceColumnBlocks[piece][k];
}

void remove(int piece, int row, int column) {
    FOR(k, height[piece]) field[row + k] &= ~(pieceRow[piece][k] << column);
    FOR(k, width[piece]) columnSize[column + k] -= pieceColumnBlocks[piece][k];
}

int sqr(int a) {
    return a * a;
}

int calcValue2() {
    int result = 0;
    FOR(i, FIELD_SIZE) result += penalty[numBits[field[i]]];
    FOR(i, FIELD_SIZE) result += penalty[columnSize[i]];
    return result;
}


void check() {
    FOR(i, FIELD_SIZE) {
        int f = 0;
        FOR(j, FIELD_SIZE) f += getField(j, i);
        if (f != columnSize[i]) {
            printField();
            printf("Column %d, expected %d, got %d\n", i, columnSize[i], f);
            fail();
        }
    }
}


void findPosition(int level, int value) {
    bool rowsToRemove[FIELD_SIZE];
    bool columnsToRemove[FIELD_SIZE];
    FOR(k, FIELD_SIZE) rowsToRemove[k] = columnsToRemove[k] = false;

    int piece = p[currP[level]];
    value += pieceSize[piece];
    bool found = false;
    FOR(i, FIELD_SIZE - height[piece] + 1) FOR(j, FIELD_SIZE - width[piece] + 1) {
        bool ok = true;
        FOR(k, height[piece])
            if ((field[i + k] & (pieceRow[piece][k] << j)) != 0) {
                ok = false;
                break;
            }

        if (ok) {
            found = true;

            currR[level] = i;
            currC[level] = j;

            place(piece, i, j);
            if (level < 2) {
                int score = removeAll(rowsToRemove, columnsToRemove, i, i + height[piece], j, j + width[piece]);

                findPosition(level + 1, value + score);

                if (score > 0) {
                    revertRemoveAll(rowsToRemove, columnsToRemove, i, i + height[piece], j, j + width[piece]);
                    //i = FIELD_SIZE;
                    //j = FIELD_SIZE;
                }
            } else {
                int valueTemp = value + calcScore(i, i + height[piece], j, j + width[piece]);
                if (valueTemp >= maxValue) {
                    int cv2;
                    removeAllFake(rowsToRemove, columnsToRemove, i, i + height[piece], j, j + width[piece]);
                    if (valueTemp > maxValue) {
                        FOR(l, 3) maxP[l] = currP[l], maxR[l] = currR[l], maxC[l] = currC[l];
                        maxValue = valueTemp;
                        maxValue2 = calcValue2();
                    } else if (valueTemp == maxValue && (cv2 = calcValue2()) > maxValue2) {
                        maxValue2 = cv2;
                        FOR(l, 3) maxP[l] = currP[l], maxR[l] = currR[l], maxC[l] = currC[l];
                    }

                    revertRemoveAllFake(rowsToRemove, columnsToRemove, i, i + height[piece], j, j + width[piece]);
                }
            }
            remove(piece, i, j);
       }
    }

    if (!found && value > maxValue) {
        FOR(i, level) maxP[i] = currP[i], maxR[i] = currR[i], maxC[i] = currC[i];
        FORE(i, level, 3) maxP[i] = -1;
        maxValue = value;
        maxValue2 = calcValue2();
    }

}

int startTime;

int getTime() {
    struct rusage t;
    struct timeval tv;
    getrusage(RUSAGE_SELF, &t);
    tv = t.ru_utime;
    return t.ru_utime.tv_sec * 1000000 + t.ru_utime.tv_usec + t.ru_stime.tv_sec * 1000000 + t.ru_stime.tv_usec;
}

void startTimer() {
    startTime = getTime();
}

int currentTime() {
    return getTime() - startTime;
}




int main(void) {
    startTimer();
    FOR(i, 1 << FIELD_SIZE) {
        int x = i;
        int n = 0;
        while (x > 0) {
            if ((x & 1) == 1) n++;
            x >>= 1;
        }
        numBits[i] = n;
    }

    FOR(i, FIELD_SIZE) penalty[i] = sqr(abs(i - 6));
    penalty[FIELD_SIZE] = penalty[0];

    FOR(i, PIECES) {
        int s = 0;
        while (pieces[i][s][0] >= 0) {
            height[i] = max(height[i], pieces[i][s][0]);
            width[i] = max(width[i], pieces[i][s][1]);

            s++;
        }
        height[i]++;
        width[i]++;
        pieceSize[i] = s;
        FOR(j, s) pieceRow[i][pieces[i][j][0]] |= 1 << pieces[i][j][1];
        FOR(j, s) pieceColumnBlocks[i][pieces[i][j][1]]++;
    }


    int totalScore = 0;
    while (true) {
        scanf("%d %d %d", &p[0], &p[1], &p[2]);
        p[0]--; p[1]--; p[2]--;
        if (p[0] < 0) break;

        FOR(i, 3) maxP[i] = -1;
        maxValue = -1;

        if (currentTime() < 4900000) {
            int visited[6][3];
            FOR(xx, sizeof(perms) / sizeof(perms[0])) {
                FOR(i, 3) currP[i] = perms[xx][i];
                FOR(i, 3) visited[xx][i] = p[currP[i]];
                bool valid = true;
                FOR(j, xx) if (visited[j][0] == visited[xx][0] && visited[j][1] == visited[xx][1] && visited[j][2] == visited[xx][2]) {
                    valid = false;
                    break;
                }
                if (valid) findPosition(0, 0);
            }
        }
        //printf("%d\n", maxValue);
        FOR(i, 3) {
            if (maxP[i] >= 0) {
                //printf("Column1: %d\n", columnSize[0]);
                //printf("Placing %d at %d, %d, width: %d, height: %d\n", p[maxP[i]], maxR[i], maxC[i], width[p[maxP[i]]], height[p[maxP[i]]]);
                place(p[maxP[i]], maxR[i], maxC[i]);
                //printField();
                bool rowsToRemove[FIELD_SIZE];
                bool columnsToRemove[FIELD_SIZE];
                FOR(k, FIELD_SIZE) rowsToRemove[k] = columnsToRemove[k] = false;
                totalScore += removeAll(rowsToRemove, columnsToRemove, 0, FIELD_SIZE, 0, FIELD_SIZE) + pieceSize[p[maxP[i]]];
                //printf("Column1-2: %d\n", columnSize[0]);
            }
            check();
            //printField();
        }
        /*FOR(i, 3) {
            if (maxP[i] >= 0 && (maxR[i] + height[p[maxP[i]]] > 10 || maxR[i] + height[p[maxP[i]]] < 1)) fail();
            if (maxP[i] >= 0 && (maxC[i] + 1 > 10 || maxC[i] + 1 < 1)) fail();
            if (i > 0 && maxP[i] >= 0 && maxP[i - 1] < 0) fail();
            if (maxP[i] >= 0) FORE(j, i + 1, 3) if (maxP[i] == maxP[j]) fail();
        }*/

        FOR(i, 3) printf("%d %d %d ", maxP[i] < 0 ? -1 : maxP[i] + 1, maxP[i] < 0 ? -1  : maxR[i] + height[p[maxP[i]]], maxP[i] < 0 ? -1 : maxC[i] + 1);
        printf("\n");
        fflush(stdout);
        if (maxP[0] < 0 || maxP[1] < 0 || maxP[2] < 0) break;
    }
    printf("%d\n", totalScore);
}

