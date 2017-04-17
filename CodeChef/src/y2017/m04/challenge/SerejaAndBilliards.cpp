// Try to pocket balls with positive values and avoid balls with negative values. Many optimizations to minimize number of moves.
// https://www.codechef.com/APRIL17/problems/SEABIL
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

#define EMPTY 1000000000
#define MAX_N 128
int cost[MAX_N][MAX_N];
int cost2[MAX_N][MAX_N];
struct Move {
    pair<int, int> pos;
    pair<int, int> v;
    int e;
};
vector<Move> moves;
int n;


void makeMove(Move & m) {
    m.pos.first += m.v.first;
    m.pos.second += m.v.second;
    if ((m.pos.first == -1 && (m.pos.second == -1 || m.pos.second == n + 1)) ||
        (m.pos.first == n + 1 && (m.pos.second == -1 || m.pos.second == n + 1))) return;

    if (m.pos.first == -1) { m.pos.first = 1; m.v.first = -m.v.first; }
    if (m.pos.first == n + 1) { m.pos.first = n - 1; m.v.first = -m.v.first; }
    if (m.pos.second == -1) { m.pos.second = 1; m.v.second = -m.v.second; }
    if (m.pos.second == n + 1) { m.pos.second = n - 1; m.v.second = -m.v.second; }
}

void solvePositives() {
    FOR(i, n + 1) {
        Move m;
        bool found = false;
        int total = 0;
        FOR(j, n + 1) {
            if (cost[i][j] != EMPTY && !found && (i < n || (i == n && j != n))) {
                found = true;
                m.pos = make_pair(i, j);
                m.v = make_pair(0, 1);
                m.e = n - j + n - i;
            }
            if (cost[i][j] != EMPTY) total += cost[i][j];
        }
        if (found) {
            FOR(j, n + 1) cost[i][j] = EMPTY;
            cost[i][i] = total;
            moves.push_back(m);
        }
    }
    FOR(i, n + 1) if (cost[i][i] != EMPTY) {
        Move m;
        m.pos = make_pair(i, i);
        m.v = make_pair(1, 1);
        m.e = n + 1;
        moves.push_back(m);
        break;
    }
}

bool hasPositiveValue(int row) {
    FOR(i, n + 1) if (cost[row][i] != EMPTY && cost[row][i] > 0) return true;
    return false;
}

int firstPositive(int row) {
    FOR(i, n + 1) if (cost[row][i] != EMPTY && cost[row][i] > 0) {
        //printf("First positive at %d is %d with %d\n", row, i, cost[row][i]);
        return i;
    }
}

bool hasNegatives(int row, int from, int to) {
    FORE(i, from, to + 1) if (cost[row][i] < 0) return true;
    return false;
}

int lastPositive(int row) {
    for(int i = n; i >= 0; i--) if (cost[row][i] != EMPTY && cost[row][i] > 0) return i;
}


void printMove(Move m) {
    printf("Move: %d %d, v = %d %d, e = %d\n", m.pos.first, m.pos.second, m.v.first, m.v.second, m.e);
}

void removeNegative(int a, int b) {
    int dirs[] = {-1, 0, 1};
    int maxf = 0;
    Move best;
    FOR(i, 3) {
        Move m;
        m.pos.first = a;
        m.pos.second = b;
        m.v.first = 1;
        m.v.second = dirs[i];
        m.e = 0;
        Move localBest;
        int f = 0;

        while (m.pos.first <= n &&
               ((dirs[i] == 0 && m.e <= n - a) || (dirs[i] != 0 && (m.e == 0 || m.pos.first > a))) &&
               (cost[m.pos.first][m.pos.second] == EMPTY || cost[m.pos.first][m.pos.second] < 0)) {
            m.e++;
            if (cost[m.pos.first][m.pos.second] < 0) {
                f++;
                localBest = m;
            }
            makeMove(m);
        }
        if (f > maxf && b - dirs[i] >= 0 && b - dirs[i] <= n && b - dirs[i] != a - 1) {
            maxf = f;
            best = localBest;
        }
    }
    Move m = best;
    m.v.first = -m.v.first;
    m.v.second = -m.v.second;
    //printf("Pushing move: ");
    //printMove(m);
    moves.push_back(m);

    int total = 0;
    FOR(i, m.e) {
        if (cost[m.pos.first][m.pos.second] < 0) {
            total += cost[m.pos.first][m.pos.second];
            cost[m.pos.first][m.pos.second] = EMPTY;
        }
        makeMove(m);
    }
    cost[m.pos.first][m.pos.second] = cost[m.pos.first][m.pos.second] == EMPTY ?
        total : cost[m.pos.first][m.pos.second] + total;
}

void solveNegatives() {
    int row = -1;
    int dir = -1;
    FOR(i, n + 1) {
        if (i < n) {
            bool found = true;
            FOR(j, n + 1) if (cost[i][j] < -1 && cost[i + 1][j] != EMPTY && cost[i + 1][j] > 0) {
                found = false;
                break;
            }
            if (found) {
                row = i;
                dir = 1;
                break;
            }
        }
    }
    FOR(i, n + 1)
        if (cost[row][i] < -1) {
            Move m;
            m.pos = make_pair(row, i);
            m.v = make_pair(dir, 0);
            m.e = 1;
            cost[row + dir][i] = cost[row + dir][i] == EMPTY ? cost[row][i] : cost[row + dir][i] + cost[row][i];
            cost[row][i] = EMPTY;
            moves.push_back(m);
        }

    Move m;
    bool found = false;
    int total = 0;
    FOR(j, n + 1) {
        if (cost[row][j] != EMPTY && !found && (row < n || (row == n && j != n))) {
            found = true;
            m.pos = make_pair(row, j);
            m.v = make_pair(0, 1);
            m.e = n - j + n - row;
        }
        if (cost[row][j] != EMPTY) total += cost[row][j];
    }
    if (found) {
        FOR(j, n + 1) cost[row][j] = EMPTY;
        cost[row][row] = total;
        moves.push_back(m);
    }

    FOR(i, n + 1) {
        if (i != row && (hasPositiveValue(i) || cost[i][i] != EMPTY)) {

            if (i > row) {
                if (hasPositiveValue(i)) {
                    int fp = firstPositive(i);
                    int lp = lastPositive(i);
                    if (!(fp == lp && cost[i][fp] == 1)) {
                        int p1, p2;
                        if (fp >= i) { p1 = i; p2 = lp + 1;}
                        else if (lp <= i) {p1 = fp; p2 = i + 1; }
                        else if (!hasNegatives(i, 0, fp)) { p1 = 0; p2 = lp; }
                        else { p1 = fp; p2 = n + 1; }

                        FORE(j, p1, p2) if (cost[i][j] < 0) removeNegative(i, j);
                        total = 0;
                        FOR(j, n + 1) if (cost[i][j] != EMPTY && cost[i][j] > 0) total += cost[i][j];

                        FOR(j, n + 1) cost[i][j] = EMPTY;
                        cost[i][i] = total;
                        if (!(fp == lp && fp == i)) {
                            Move m;
                            m.pos = make_pair(i, fp >= i ? lp : (lp <= i ? fp : (p1 == 0 ? lp : fp)));
                            m.v = make_pair(0, fp >= i || (lp > i && p1 == 0) ? -1 : 1);
                            m.e = fp >= i ? lp - i : (lp <= i ? i - fp : (p1 == 0 ? lp + i : n - fp + n - i));
                            moves.push_back(m);
                        }
                    }
                } else {
                    removeNegative(i, i);
                }
            } else {
                Move m;
                found = false;
                total = 0;
                FOR(j, n + 1) {
                    if (cost[i][j] < -1) {
                        Move m2;
                        m2.pos = make_pair(i, j);
                        m2.v = make_pair(i < row ? 1 : -1, 0);
                        if (i + m2.v.first == j) m2.v.second = 1;
                        m2.e = 1;
                        moves.push_back(m2);
                        cost[i][j] = EMPTY;
                    } else if (cost[i][j] != EMPTY && !found && (i < n || (i == n && j != n))) {
                        found = true;
                        m.pos = make_pair(i, j);
                        m.v = make_pair(0, 1);
                        m.e = n - j + n - i;
                    }
                    if (cost[i][j] != EMPTY) total += cost[i][j];
                }
                if (found) {
                    FOR(j, n + 1) cost[i][j] = EMPTY;
                    cost[i][i] = total;
                    moves.push_back(m);
                }
            }
        }
    }

    FOR(i, n + 1) if (cost[i][i] != EMPTY) {
        Move m;
        m.pos = make_pair(i, i);
        m.v = make_pair(1, 1);
        m.e = n + 1;
        moves.push_back(m);
        break;
    }
}

int total = 0;
void simulate() {
    FOR(i, moves.size()) {
        Move m = moves[i];
        Move mb = m;
        int e = m.e;
        if (cost2[m.pos.first][m.pos.second] == EMPTY) {
            printf("Error at %d %d %d %d %d %d\n", i, m.pos.first, m.pos.second, m.v.first, m.v.second, m.e);
            exit(1);
        }
        if (m.v.first < -1 || m.v.first > 1 || m.v.second < -1 || m.v.second > 1 || (m.v.first == 0 && m.v.second == 0)) {
            printf("Velocity error: %d %d\n", m.v.first, m.v.second);
            exit(1);
        }

        FOR(j, e) {
            int origCost = cost2[m.pos.first][m.pos.second];
            cost2[m.pos.first][m.pos.second] = EMPTY;
            makeMove(m);
            if ((m.pos.first == -1 && (m.pos.second == -1 || m.pos.second == n + 1)) ||
                (m.pos.first == n + 1 && (m.pos.second == -1 || m.pos.second == n + 1))) {
                //printf("Adding %d\n", origCost);
                total += origCost;
                break;
            }
            if (origCost > 0 && cost2[m.pos.first][m.pos.second] < -1) {
                printf("Error?: %d %d\n", origCost, cost2[m.pos.first][m.pos.second]);
                printf("%d %d %d %d %d, curr: %d %d\n", mb.pos.first, mb.pos.second, mb.v.first, mb.v.second, mb.e, m.pos.first, m.pos.second);
            }
            cost2[m.pos.first][m.pos.second] = cost2[m.pos.first][m.pos.second] == EMPTY ? origCost : cost2[m.pos.first][m.pos.second] + origCost;
            //printf("Cost at %d %d set to %d\n", a, b, cost2[a][b]);
        }
    }
    total -= moves.size();
    printf("Total: %d\n", total);

}

void printGrid() {
    /*int x = 50;
    FOR(i, x) {
        FOR(j, x) if (cost2[i][j] == EMPTY) printf("    "); else printf("%4d", cost2[i][j]);
        printf("\n");
    }*/
    FOR(i, n) {
        printf("%d = ", i);
        FOR(j, n) if (cost2[i][j] != EMPTY) printf("%d = %d, ", j, cost2[i][j]);
        printf("\n");
    }

}


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        int m = getInt();
        FOR(i, n + 1) FOR(j, n + 1) cost2[i][j] = cost[i][j] = EMPTY;
        bool negatives = false;
        moves.clear();
        int totalPlus = 0;
        FOR(i, m) {
            int x = getInt();
            int y = getInt();
            int z = getSignedInt();
            cost2[x][y] = cost[x][y] = z;
            if (z > 0) totalPlus += z;
            if (z < 0) negatives = true;
        }
        //printf("Test: %d - %d\n", tt, m);
        //printGrid();
        int tp2 = 0;
        /*FOR(i, n + 1) {
            int ttt = 0;
            FOR(j, n + 1) if (cost2[i][j] > 0 && cost2[i][j] != EMPTY) ttt += cost2[i][j];
            printf("Cost at %d = %d\n", i, ttt);
            tp2 += ttt;
        }*/
        if (negatives) solveNegatives(); else solvePositives();
        //solvePositives();
        print(moves.size());
        FOR(i, moves.size()) printf("%d %d %d %d %d\n", moves[i].pos.first, moves[i].pos.second, moves[i].v.first, moves[i].v.second, moves[i].e);
        //simulate();
        //printf("Totalplus: %d %d\n", totalPlus, tp2);
    }

}

