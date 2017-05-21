// Use Monte Carlo to simulate positions of ships on the grid and then choose the square with highest probability
// https://www.codechef.com/MAY17/problems/CHEFBATL
#include <bits/stdc++.h>
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

template <class type> type gcd(type a, type b) {
    return b == 0 ? a : gcd(b, a % b);
}

void fail() {
    *((char *)0) = 0;
}

double cpu() {
    return clock() / (double)CLOCKS_PER_SEC;
}

#define SEARCH 0
#define HIT 1

#define EMPTY_CELL 1
#define SHIP_HIT 2
#define SHIP_SUNK 3
#define WIN 4
#define LOST 5

#define SIZE 10
bool myBoard[SIZE][SIZE];
int ships[] = {4, 3, 2, 1};
bool opponent[SIZE][SIZE];
bool used[SIZE][SIZE];
bool used2[SIZE][SIZE];
int state;
int neighbors[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int shipsRemain[4];
pair<int, int> possibleLocations[SIZE * SIZE];

bool isAvailable(int x, int y, int l) {
    FORE(i, x - 1, x + l + 1) FORE(j, y - 1, y + 2)
        if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && myBoard[j][i]) return false;
    if (x + l > SIZE) return false;
    return true;
}

void markUsed(int x, int y) {
    FORE(i, x - 1, x + 2) FORE(j, y - 1, y + 2) if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) used[i][j] = true;
}

void markUsed2(int x, int y) {
    FORE(i, x - 1, x + 2) FORE(j, y - 1, y + 2) if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) used2[i][j] = true;
}


void place(int x, int y, int l, bool horizontal) {
    if (horizontal) FORE(i, x, x + l) myBoard[i][y] = true;
    else FORE(i, y, y + l) myBoard[x][i] = true;
}

bool placeAndMarkIfPossible(int l, bool horizontal) {
    int possCount = 0;
    if (horizontal) {
        FOR(j, SIZE) {
            int i = 0;
            while (i <= SIZE - l) {
                while (i < SIZE && used2[i][j]) i++;
                if (i < SIZE) {
                    int start = i;
                    while (i < SIZE && !used2[i][j]) i++;
                    FORE(k, start, i - l + 1) possibleLocations[possCount++] = make_pair(k, j);
                }
            }
        }
        if (possCount == 0) return false;
        int randPos = rand() % possCount;
        int x = possibleLocations[randPos].first;
        int y = possibleLocations[randPos].second;
        FORE(i, x, x + l) {
            myBoard[i][y] = used2[i][y] = true;
            markUsed2(i, y);
        }
    } else {
        FOR(i, SIZE) {
            int j = 0;
            while (j <= SIZE - l) {
                while (j < SIZE && used2[i][j]) j++;
                if (j < SIZE) {
                    int start = j;
                    while (j < SIZE && !used2[i][j]) j++;
                    FORE(k, start, j - l + 1) possibleLocations[possCount++] = make_pair(i, k);
                }
            }
        }
        if (possCount == 0) return false;
        int randPos = rand() % possCount;
        int x = possibleLocations[randPos].first;
        int y = possibleLocations[randPos].second;
        FORE(i, y, y + l) {
            myBoard[x][i] = used2[x][i] = true;
            markUsed2(x, i);
        }
    }
    return true;
}


bool placeAndMarkIfPossible2(int l, int x1, int y1, int x2, int y2, bool horizontal) {
    int possCount = 0;
    if (horizontal) {
        FORE(j, y1, y2) {
            int i = x1;
            while (i <= x2 - l) {
                while (i < x2 && used2[i][j]) i++;
                if (i < x2) {
                    int start = i;
                    while (i < x2 && !used2[i][j]) i++;
                    FORE(k, start, i - l + 1) possibleLocations[possCount++] = make_pair(k, j);
                }
            }
        }
        if (possCount == 0) return false;
        int randPos = rand() % possCount;
        int x = possibleLocations[randPos].first;
        int y = possibleLocations[randPos].second;
        FORE(i, x, x + l) {
            myBoard[i][y] = used2[i][y] = true;
            markUsed2(i, y);
        }
    } else {
        FORE(i, x1, x2) {
            int j = y1;
            while (j <= y2 - l) {
                while (j < y2 && used2[i][j]) j++;
                if (j < y2) {
                    int start = j;
                    while (j < y2 && !used2[i][j]) j++;
                    FORE(k, start, j - l + 1) possibleLocations[possCount++] = make_pair(i, k);
                }
            }
        }
        if (possCount == 0) return false;
        int randPos = rand() % possCount;
        int x = possibleLocations[randPos].first;
        int y = possibleLocations[randPos].second;
        FORE(i, y, y + l) {
            myBoard[x][i] = used2[x][i] = true;
            markUsed2(x, i);
        }
    }
    return true;
}


pair<int, int> randPair() {
    return make_pair(rand() % SIZE, rand() % SIZE);
}

void printBoard() {
    char line[SIZE + 1];
    line[SIZE] = 0;
    FOR(i, SIZE) {
        FOR(j, SIZE) line[j] = myBoard[i][j] ? '#' : '.';
        printString(line);
    }
}

void generateBoard() {
    FOR(i, SIZE) FOR(j, SIZE) myBoard[i][j] = false;
    place(0, 0, 4, true);
    place(5, 0, 1, false);
    place(7, 0, 1, false);
    place(9, 0, 3, false);
    place(9, 4, 2, false);
    place(9, 7, 3, false);
    place(6, 9, 2, true);
    place(3, 9, 1, true);
    place(0, 9, 2, true);
    place(0, 7, 1, true);
}


void readCompMove() {
    int k = getInt();
    FOR(i, k) {
        getInt();
        getInt();
    }
}


void sinkShip(int x, int y) {

    int xx = x;
    int yy = y;
    while (yy < SIZE && opponent[xx][yy]) {
        markUsed(xx, yy);
        yy++;
    }
    xx = x;
    yy = y;
    while (yy >= 0 && opponent[xx][yy]) {
        markUsed(xx, yy);
        yy--;
    }
    xx = x;
    yy = y;
    while (xx < SIZE && opponent[xx][yy]) {
        markUsed(xx, yy);
        xx++;
    }
    xx = x;
    yy = y;
    while (xx >= 0 && opponent[xx][yy]) {
        markUsed(xx, yy);
        xx--;
    }
}

bool isMoveOk(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE && !used[x][y];
}

int makeMove(int x, int y) {
    print(x + 1);
    print(y + 1);
    fflush(stdout);
    used[x][y] = true;
    return getInt();
}

void printUsed() {
    char line[SIZE + 1];
    line[SIZE] = 0;
    FOR(i, SIZE) {
        FOR(j, SIZE) line[j] = used[i][j] ? '#' : '.';
        printString(line);
    }
}

bool isDiagonal(int x, int y) {
    return ((x + y) & 1) == 0;
}

bool isDiagonalWithEmptyBorder(int x, int y) {
    if (isDiagonal(x, y)) {
        FOR(i, 4) {
            int x1 = x + neighbors[i][0];
            int y1 = y + neighbors[i][1];
            if (x1 >= 0 && x1 < SIZE && y1 >= 0 && y1 < SIZE && used[x1][y1]) return false;
        }
        return true;
    } else return false;

}

bool diagonalWithEmptyBorderEmpty() {
    FOR(i, SIZE) FOR(j, SIZE) if (!used[i][j] && isDiagonalWithEmptyBorder(i, j)) return true;
    return false;
}

bool diagonalEmpty() {
    FOR(i, SIZE) FOR(j, SIZE) if (!used[i][j] && isDiagonal(i, j)) return true;
    return false;
}

int calcDist(int x, int y) {
    int minDist = 10;
    FOR(i, 4) {
        int x1 = x;
        int y1 = y;
        int d = 0;
        while (x1 >= 0 && x1 < SIZE && y1 >= 0 && y1 < SIZE && !used[x1][y1]) {
            d++;
            x1 += neighbors[i][0];
            y1 += neighbors[i][1];
        }
        minDist = min(minDist, d);
    }
    return minDist;
}

pair<int, int> randPair2() {
    /*if (diagonalWithEmptyBorderEmpty()) {
        auto p = make_pair(rand() % SIZE, rand() % SIZE);
        while (!isDiagonalWithEmptyBorder(p.first, p.second)) {
            p = make_pair(rand() % SIZE, rand() % SIZE);
        }
        return p;
    } else if (diagonalEmpty()) {
        auto p = make_pair(rand() % SIZE, rand() % SIZE);
        while (!isDiagonal(p.first, p.second)) {
            p = make_pair(rand() % SIZE, rand() % SIZE);
        }
        return p;*/
    if (diagonalEmpty()) {
        int maxDist = -1;
        pair<int, int> selected;
        FOR(i, SIZE) FOR(j, SIZE) if (isDiagonal(i, j) && !used[i][j]) {
            int x = calcDist(i, j);
            if (x > maxDist) {
                maxDist = x;
                selected = make_pair(i, j);
            }
        }
        return selected;
    } else return make_pair(rand() % SIZE, rand() % SIZE);
    /*{
        int maxDist = -1;
        pair<int, int> selected;
        FOR(i, SIZE) FOR(j, SIZE) if (!used[i][j]) {
            int x = calcDist(i, j);
            if (x > maxDist) {
                maxDist = x;
                selected = make_pair(i, j);
            }
        }
        return selected;

    }*/

}

int checkDist(int x, int y, int target) {
    int res = 0;
    FOR(i, 4) {
        int x1 = x + neighbors[i][0];
        int y1 = y + neighbors[i][1];
        int d = 0;
        while (!used[x1][y1] && x1 >= 0 && x1 < SIZE && y1 >= 0 && y1 < SIZE) {
            x1 += neighbors[i][0];
            y1 += neighbors[i][1];
            d++;
        }
        if (d == target) res++;
    }
    return res;
}

int maxDist(int x, int y) {
    int res = 0;
    FOR(i, 4) {
        int x1 = x + neighbors[i][0];
        int y1 = y + neighbors[i][1];
        int d = 0;
        while (!used[x1][y1] && x1 >= 0 && x1 < SIZE && y1 >= 0 && y1 < SIZE) {
            x1 += neighbors[i][0];
            y1 += neighbors[i][1];
            d++;
        }
        if (d > res) res = d;
    }
    return res;
}

int maxDistDirection(int x, int y) {
    int res = 0;
    int resDir = 0;
    FOR(i, 4) {
        int x1 = x + neighbors[i][0];
        int y1 = y + neighbors[i][1];
        int d = 0;
        while (!used[x1][y1] && x1 >= 0 && x1 < SIZE && y1 >= 0 && y1 < SIZE) {
            x1 += neighbors[i][0];
            y1 += neighbors[i][1];
            d++;
        }
        if (d > res) {
            res = d;
            resDir = i;
        }
    }
    return resDir;
}

int totalBoard[SIZE][SIZE];


pair<int, int> randPair3() {
    int maxRemain = 3;
    while (shipsRemain[maxRemain] == 0) maxRemain--;
    if (maxRemain == 0) return make_pair(rand() % SIZE, rand() % SIZE);
    /*else if (maxRemain == 3) {
        vector<pair<int, int> > result;
        FOR(i, SIZE) FOR(j, SIZE) if (!used[i][j] && (i + j) % 4 == 0 && maxDist(i, j) >= 3) {
            result.push_back(make_pair(i, j));
        }
        return result[rand() % result.size()];
    } */ else {
        vector<pair<int, int> > result;
        int mxDist = 0;
        int maxTotalBoard = 0;
        pair<int, int> res;
        FOR(i, SIZE) FOR(j, SIZE) if (!used[i][j]) {
            int t = checkDist(i, j, maxRemain);
            if (t > mxDist) {
                mxDist = t;
                result.clear();
                maxTotalBoard = 0;
            }
            if (t == mxDist) {
                if (totalBoard[i][j] > maxTotalBoard) {
                    maxTotalBoard = totalBoard[i][j];
                    res = make_pair(i, j);
                }
                result.push_back(make_pair(i, j));
            }
        }
        return mxDist == 0 ? make_pair(rand() % SIZE, rand() % SIZE) : res;
        /*int minDist = 0;
        pair<int, int> res;
        FOR(i, SIZE) FOR(j, SIZE) if (!used[i][j]) {
            int t = calcDist(i, j);
            if (t > minDist) {
                minDist = t;
                res = make_pair(i, j);
            }
        }
        return minDist == 0 ? make_pair(rand() % SIZE, rand() % SIZE) : res;*/
    }
}


bool randomBoard() {
    memset(myBoard, 0, sizeof(myBoard));
    memcpy(used2, used, sizeof(used));
    int shipsToTest[10];
    int shipsToTest2[10];
    int totalShips = 0;
    bool localUsed[10];
    for(int i = 3; i >= 0; i--) FOR(j, shipsRemain[i]) shipsToTest[totalShips++] = i + 1;
    FOR(i, totalShips) localUsed[i] = false;
    FOR(i, totalShips) {
        int pp = rand() % totalShips;
        while (localUsed[pp]) pp = rand() % totalShips;
        shipsToTest2[i] = shipsToTest[pp];
        localUsed[pp] = true;
    }

    FOR(i, totalShips)
        if (!placeAndMarkIfPossible(shipsToTest2[i], (rand() & 1) == 1)) return false;
    return true;
}

bool randomBoardLimited() {
    memset(myBoard, 0, sizeof(myBoard));
    memcpy(used2, used, sizeof(used));
    int shipsToTest[10];
    int shipsToTest2[10];
    int totalShips = 0;
    bool localUsed[10];
    for(int i = 3; i >= 1; i--) FOR(j, shipsRemain[i]) shipsToTest[totalShips++] = i + 1;
    FOR(i, totalShips) localUsed[i] = false;
    FOR(i, totalShips) {
        int pp = rand() % totalShips;
        while (localUsed[pp]) pp = rand() % totalShips;
        shipsToTest2[i] = shipsToTest[pp];
        localUsed[pp] = true;
    }
    int a = rand() % 5 + 6;
    int b = rand() % 5 + 6;
    int x1 = rand() % (SIZE - a + 1);
    int y1 = rand() % (SIZE - b + 1);
    FOR(i, totalShips)
        if (!placeAndMarkIfPossible2(shipsToTest2[i], x1, y1, x1 + a, y1 + b, (rand() & 1) == 1)) return false;
    FOR(i, shipsRemain[0])
        if (!placeAndMarkIfPossible(1, false)) return false;


    return true;
}


pair<int, int> monteCarlo() {
    memset(totalBoard, 0, sizeof(totalBoard));
    int cc = 100000;
    FOR(i, cc) {
        if (rand() % 2 == 0) {
            while (!randomBoard());
        } else {
            while (!randomBoardLimited());
        }

        FOR(k, SIZE) FOR(l, SIZE) totalBoard[k][l] += myBoard[k][l];
    }
    /*FOR(i, SIZE) {
        FOR(j, SIZE) printf("%3d ", totalBoard[i][j] * 1000 / cc);
        printf("\n");
    }*/

    int mx = 0;
    pair<int, int> res;
    FOR(i, SIZE) FOR(j, SIZE) if (totalBoard[i][j] > mx) {
        mx = totalBoard[i][j];
        res = make_pair(i, j);
    }
    if (mx == 0) {
        res = randPair3();
        while (!isMoveOk(res.first, res.second)) res = randPair3();
    }
    return res;
}

pair<int, int> monteCarlo2() {
    int mx = 0;
    pair<int, int> res;
    FOR(i, SIZE) FOR(j, SIZE) if (!used[i][j] && totalBoard[i][j] > mx) {
        mx = totalBoard[i][j];
        res = make_pair(i, j);
    }
    return res;
}

int main(void) {
    FOR(i, 4) shipsRemain[i] = ships[i];
    monteCarlo();
    //return 0;
    //srand(time(NULL));
    int t = 100;
    FOR(tt, t) {
        generateBoard();
        FOR(i, 4) shipsRemain[i] = ships[i];
        FOR(i, SIZE) FOR(j, SIZE) opponent[i][j] = used[i][j] = false;
        print(1);
        printBoard();
        fflush(stdout);

        int shipStartX = 0, shipStartY = 0, shipEndX = 0, shipEndY = 0;
        int totalSquares = 0;
        state = SEARCH;
        while (true) {
            int answer;
            pair<int, int> p;
            //printUsed();
            switch (state) {
            case SEARCH:
                p = randPair3();
                while (!isMoveOk(p.first, p.second)) p = randPair3();
                //p = monteCarlo2();
                answer = makeMove(p.first, p.second);
                //printf("Answer is %d\n", answer);
                switch (answer) {
                case EMPTY_CELL:
                    readCompMove();
                    break;
                case SHIP_HIT:
                    state = HIT;
                    shipEndX = shipStartX = p.first;
                    shipEndY = shipStartY = p.second;
                    opponent[p.first][p.second] = true;
                    totalSquares = 1;
                    break;
                case SHIP_SUNK:
                    state = SEARCH;
                    opponent[p.first][p.second] = true;
                    sinkShip(p.first, p.second);
                    shipsRemain[0]--;
                    break;
                case WIN:
                    goto end;
                case LOST:
                    readCompMove();
                    goto end;
                }
                break;

            case HIT:
                if (totalSquares == 1) {
                    int i = maxDistDirection(shipStartX, shipStartY);
                    p = make_pair(shipStartX + neighbors[i][0], shipStartY + neighbors[i][1]);
                } else {
                    if (shipStartX == shipEndX) {
                        p = make_pair(shipStartX, shipStartY - 1);
                        if (!isMoveOk(p.first, p.second)) p = make_pair(shipStartX, shipEndY + 1);
                    } else {
                        p = make_pair(shipStartX - 1, shipStartY);
                        if (!isMoveOk(p.first, p.second)) p = make_pair(shipEndX + 1, shipStartY);
                    }
                }
                answer = makeMove(p.first, p.second);
                switch (answer) {
                case EMPTY_CELL:
                    readCompMove();
                    break;
                case SHIP_HIT:
                    opponent[p.first][p.second] = true;
                    if (totalSquares == 1) {
                        if (p.first < shipStartX) shipStartX = p.first;
                        else if (p.first > shipStartX) shipEndX = p.first;
                        else if (p.second < shipStartY) shipStartY = p.second;
                        else if (p.second > shipStartY) shipEndY = p.second;
                    } else {
                        if (shipStartX == shipEndX) {
                            if (p.second < shipStartY) shipStartY = p.second; else shipEndY = p.second;
                        } else {
                            if (p.first < shipStartX) shipStartX = p.first; else shipEndX = p.first;
                        }
                    }
                    totalSquares++;
                    break;
                case SHIP_SUNK:
                    state = SEARCH;
                    opponent[p.first][p.second] = true;
                    sinkShip(p.first, p.second);
                    shipsRemain[totalSquares]--;
                    break;
                case WIN:
                    goto end;
                case LOST:
                    readCompMove();
                    goto end;
                }
            }
        }
        end:
        int x;
    }
    print(0);
}

