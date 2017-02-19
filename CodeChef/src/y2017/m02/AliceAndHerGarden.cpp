// Generate a path through the garden starting in the top left corner and ending in the bottom right corner and visiting as many cells as possible. Then walk through it as many times as possible.
// https://www.codechef.com/FEB17/problems/ALICGARD
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

#define MAX_N 200
#define MAX_W 20
int n, f, x, y, w;
int flowers[MAX_N][MAX_N];
int limit[MAX_N][MAX_N];
int regrow[MAX_N][MAX_N];
bool isFence[MAX_N][MAX_N];


struct Rectangle {
    int x1, y1;
    int x2, y2;
} fence[MAX_N * 2];

void print() {
    limit[x][y]--;
    printf("MOVE %d %d\n", x + 1, y + 1);
}


void goFenceDown() {
    while (true) {
        while (x < n - 1 && isFence[x + 1][y]) { x++; print(); }
        if (y == n - 1 || !isFence[x][y + 1]) break;
        y++;
        print();
        while (x > 0 && isFence[x - 1][y]) { x--; print(); }
        if (y == n - 1 || !isFence[x][y + 1]) break;
        y++;
        print();
    }
}

void goFenceUp() {
    while (true) {
        while (x < n - 1 && isFence[x + 1][y]) { x++; print(); }
        if (y == 0 || !isFence[x][y - 1]) break;
        y--;
        print();
        while (x > 0 && isFence[x - 1][y]) { x--; print(); }
        if (y == 0 || !isFence[x][y - 1]) break;
        y--;
        print();
    }
}

void returnFenceLeftUp() {
    if (x > 0 && isFence[x - 1][y]) {
        while (x > 0 && isFence[x - 1][y]) { x--; print(); }
        if (y > 0 && isFence[x][y - 1]) { y--; print(); }
    }
}

void returnFenceLeftDown() {
    if (x > 0 && isFence[x - 1][y]) {
        while (x > 0 && isFence[x - 1][y]) { x--; print(); }
        if (y < n - 1 && isFence[x][y + 1]) { y++; print(); }
    }
}

void runFence() {
    if (isFence[x][y + 1]) {
        goFenceDown();
        returnFenceLeftUp();
        goFenceUp();
        returnFenceLeftDown();
        goFenceDown();
        returnFenceLeftUp();
        goFenceUp();
    } else {
        goFenceDown();
        returnFenceLeftUp();
        goFenceDown();
        returnFenceLeftUp();
    }
}

bool visited[MAX_N][MAX_N];
pair<int, int> prevCell[MAX_N][MAX_N];

vector<pair<int, int> > currentPath;


vector<pair<int, int> > findPath(int x1, int y1, int x2, int y2) {
    FOR(i, n) FOR(j, n) visited[i][j] = false;
    queue<pair<int, int> > q;
    visited[x1][y1] = true;
    q.push(make_pair(x1, y1));
    while (!q.empty()) {
        auto c = q.front();
        q.pop();
        FORE(i, -1, 2) FORE(j, -1, 2) if (abs(i) + abs(j) == 1) {
            int xx = c.first + i;
            int yy = c.second + j;
            if (xx >= 0 && xx < n && yy >= 0 && yy < n) {
                if (!visited[xx][yy] && !isFence[xx][yy]) {
                    visited[xx][yy] = true;
                    q.push(make_pair(xx, yy));
                    prevCell[xx][yy] = make_pair(c.first, c.second);
                    if (xx == x2 && yy == y2) goto end;
                }
            }
        }

    }
    // This should never happen
    printf("Path not found1\n");
    fail();

    end:
    vector<pair<int, int> > result;
    int xx = x2, yy = y2;
    while (xx != x1 || yy != y1) {
        result.push_back(make_pair(xx, yy));
        auto c = prevCell[xx][yy];
        xx = c.first;
        yy = c.second;
    }
    reverse(result.begin(), result.end());
    return result;
}

bool localIsFence[MAX_W][MAX_W];
bool localIsFence2[MAX_W][MAX_W];
int fx1, fx2, fy1, fy2;

void findFence() {
    FOR(i, w) FOR(j, w) {
        if (localIsFence[i][j] && (i == 0 || !localIsFence[i - 1][j])) fx1 = i;
        if (localIsFence[i][j] && (i == n - 1 || !localIsFence[i + 1][j])) fx2 = i;
        if (localIsFence[i][j] && (j == 0 || !localIsFence[i][j - 1])) fy1 = j;
        if (localIsFence[i][j] && (j == n - 1 || !localIsFence[i][j + 1])) fy2 = j;
    }
}

void addSimplePath(int x1, int y1, int x2, int y2, int rx1, int ry1, int rx2, int ry2, vector<pair<int, int> > &path) {
    /*path.push_back(make_pair(x1, y1));
    if (x1 != x2) {
        int stepx = x2 > x1 ? 1 : -1;
        while (x1 != x2) {
            x1 += stepx;
            path.push_back(make_pair(x1, y1));
        }
    }
    if (y1 != y2) {
        int stepy = y2 > y1 ? 1 : -1;
        while (y1 != y2) {
            y1 += stepy;
            path.push_back(make_pair(x1, y1));
        }
    }*/
    //printf("Going from %d %d to %d %d,    %d %d %d %d\n", x1, y1, x2, y2, rx1, ry1, rx2, ry2);
    int width = rx2 - rx1 + 1;
    int height = ry2 - ry1 + 1;
    x1 -= rx1;
    y1 -= ry1;
    x2 -= rx1;
    y2 -= ry1;

    //printf("Going from %d %d to %d %d\n", x1, y1, x2, y2);

    vector<pair<int, int> > localPath;
    if (x1 == x2 && y1 == y2) localPath.push_back(make_pair(x1, y1));
    else if (width == 1 || height == 1) {
        localPath.push_back(make_pair(x1, y1));
        if (x1 != x2) {
            int stepx = x2 > x1 ? 1 : -1;
            while (x1 != x2) {
                x1 += stepx;
                localPath.push_back(make_pair(x1, y1));
            }
        }
        if (y1 != y2) {
            int stepy = y2 > y1 ? 1 : -1;
            while (y1 != y2) {
                y1 += stepy;
                localPath.push_back(make_pair(x1, y1));
            }
        }
    } else if (x1 != x2 && y1 != y2) {
        bool mirror = false;
        bool doReverse = false;
        if ((x1 == 0 && y1 != 0) || (x1 != 0 && y1 == 0)) {
            mirror = true;
            x1 = width - 1 - x1;
            x2 = width - 1 - x2;
        }
        if (x1 == width - 1 && y1 == height - 1) {
            swap(x1, x2);
            swap(y1, y2);
            doReverse = true;
        }
        if (width % 2 == 1) {
            FOR(i, width - 1) {
                FOR(j, height) localPath.push_back(make_pair(x1, y1++));
                x1++; y1--;
                FOR(j, height) localPath.push_back(make_pair(x1, y1--));
                x1++; y1++;
                i++;
            }
            FOR(j, height) localPath.push_back(make_pair(x1, y1++));
        } else if (height % 2 == 1) {
            FOR(i, height - 1) {
                FOR(j, width) localPath.push_back(make_pair(x1++, y1));
                y1++; x1--;
                FOR(j, width) localPath.push_back(make_pair(x1--, y1));
                y1++; x1++;
                i++;
            }
            FOR(j, width) localPath.push_back(make_pair(x1++, y1));
        } else {
            FOR(i, height - 2) {
                FOR(j, width) localPath.push_back(make_pair(x1++, y1));
                y1++; x1--;
                FOR(j, width) localPath.push_back(make_pair(x1--, y1));
                y1++; x1++;
                i++;
            }
            FOR(i, width - 2) {
                localPath.push_back(make_pair(x1, y1++));
                localPath.push_back(make_pair(x1++, y1));
                localPath.push_back(make_pair(x1, y1--));
                localPath.push_back(make_pair(x1++, y1));
                i++;
            }
            localPath.push_back(make_pair(x1++, y1));
            localPath.push_back(make_pair(x1, y1++));
            localPath.push_back(make_pair(x1, y1));
        }
        if (doReverse) reverse(localPath.begin(), localPath.end());
        if (mirror) FOR(i, localPath.size()) localPath[i].first = width - 1 - localPath[i].first;
    } else {
        int rotations = 0;
        bool doReverse = false;
        while (y1 != 0 || y2 != 0) {
            int nx = y1;
            int ny = width - x1 - 1;
            x1 = nx;
            y1 = ny;
            nx = y2;
            ny = width - x2 - 1;
            x2 = nx;
            y2 = ny;
            rotations++;
            swap(width, height);
        }
        //printf("Rotated: %d %d %d %d\n", x1, y1, x2, y2);
        if (x1 != 0) {
            swap(x1, x2);
            swap(y1, y2);
            doReverse = true;
        }
        if (width % 2 == 0) {
            FOR(i, width) {
                FOR(j, height) localPath.push_back(make_pair(x1, y1++));
                x1++; y1--;
                FOR(j, height) localPath.push_back(make_pair(x1, y1--));
                x1++; y1++;
                i++;
            }
        } else {
            FOR(i, width - 3) {
                FOR(j, height) localPath.push_back(make_pair(x1, y1++));
                x1++; y1--;
                FOR(j, height) localPath.push_back(make_pair(x1, y1--));
                x1++; y1++;
                i++;
            }
            FOR(j, height) localPath.push_back(make_pair(x1, y1++));
            x1++; y1--;
            while (y1 > 1) {
                localPath.push_back(make_pair(x1++, y1));
                localPath.push_back(make_pair(x1, y1--));
                localPath.push_back(make_pair(x1--, y1));
                localPath.push_back(make_pair(x1, y1--));
            }
            localPath.push_back(make_pair(x1++, y1));
            localPath.push_back(make_pair(x1, y1--));
            if (y1 == 0) localPath.push_back(make_pair(x1, y1));
        }
        if (doReverse) reverse(localPath.begin(), localPath.end());
        int ow = width;
        int oh = height;
        FOR(i, localPath.size()) {
            width = ow;
            height = oh;
            FOR(j, rotations) {
                FOR(j, 3) {
                    int nx = localPath[i].second;
                    int ny = width - localPath[i].first - 1;
                    localPath[i].first = nx;
                    localPath[i].second = ny;
                    swap(width, height);
                }
            }
        }
    }
    FOR(i, localPath.size()) {
        localPath[i].first += rx1;
        localPath[i].second += ry1;
        //printf("=%d %d\n", localPath[i].first, localPath[i].second);
    }
    FOR(i, localPath.size()) path.push_back(localPath[i]);
}

void addPath(int x1, int y1, int x2, int y2) {
    int wx = x1 / w * w;
    int wy = y1 / w * w;
    bool doReverse = false;
    vector<pair<int, int> > localPath;
    x1 -= wx;
    x2 -= wx;
    y1 -= wy;
    y2 -= wy;
    FOR(i, w) FOR(j, w) localIsFence[i][j] = isFence[wx + i][wy + j];
    if (x1 == x2 && y1 == y2) {
        localPath.push_back(make_pair(x1, y1));
    } else if ((x1 != 0 && x1 != w - 1) || (y1 != 0 && y1 != w - 1) || (x2 != 0 && x2 != w - 1) || (y2 != 0 && y2 != w - 1)) {
        FOR(i, w) FOR(j, w) visited[i][j] = false;
        queue<pair<int, int> > q;
        visited[x1][y1] = true;
        q.push(make_pair(x1, y1));
        while (!q.empty()) {
            auto c = q.front();
            q.pop();
            FORE(i, -1, 2) FORE(j, -1, 2) if (abs(i) + abs(j) == 1) {
                int xx = c.first + i;
                int yy = c.second + j;
                if (xx >= 0 && xx < n && yy >= 0 && yy < n) {
                    if (!visited[xx][yy] && !localIsFence[xx][yy]) {
                        visited[xx][yy] = true;
                        q.push(make_pair(xx, yy));
                        prevCell[xx][yy] = make_pair(c.first, c.second);
                        if (xx == x2 && yy == y2) goto end;
                    }
                }
            }

        }
        // This should never happen
        printf("Path not found2\n");
        exit(1);

        end:
        int xx = x2, yy = y2;
        while (xx != x1 || yy != y1) {
            localPath.push_back(make_pair(xx, yy));
            auto c = prevCell[xx][yy];
            xx = c.first;
            yy = c.second;
        }
        localPath.push_back(make_pair(xx, yy));
        reverse(localPath.begin(), localPath.end());
    } else if (x1 != x2 && y1 != y2) {
        bool mirror = false;
        if (x1 + y1 == w - 1) {
            FOR(i, w) FOR(j, w) localIsFence2[i][j] = localIsFence[w - 1 - i][j];
            FOR(i, w) FOR(j, w) localIsFence[i][j] = localIsFence2[i][j];
            mirror = true;
            x1 = w - 1 - x1;
            x2 = w - 1 - x2;
        }
        if (x1 == w - 1 && y1 == w - 1) {
            swap(x1, x2);
            swap(y1, y2);
            doReverse = true;
        }
        findFence();
        if (fx2 == w - 1) {
            if (fy1 <= 1) {
                addSimplePath(0, 0, fx1 - 1, w - 1, 0, 0, fx1 - 1, w - 1, localPath);
                addSimplePath(fx1, w - 1, w - 1, w - 1, fx1, fy2 + 1, w - 1, w - 1, localPath);
            } else {
                addSimplePath(0, 0, 0, fy1 - 1, 0, 0, w - 1, fy1 - 1, localPath);
                addSimplePath(0, fy1, fx1 - 1, w - 1, 0, fy1, fx1 - 1, w - 1, localPath);
                addSimplePath(fx1, w - 1, w - 1, w - 1, fx1, fy2 + 1, w - 1, w - 1, localPath);
            }
        } else if (fx1 == 0) {
            addSimplePath(0, 0, w - 1, fy1 - 1, 0, 0, w - 1, fy1 - 1, localPath);
            if (fy2 < w - 2) {
                addSimplePath(w - 1, fy1, w - 1, fy2, fx2 + 1, fy1, w - 1, fy2, localPath);
                addSimplePath(w - 1, fy2 + 1, w - 1, w - 1, 0, fy2 + 1, w - 1, w - 1, localPath);
            } else {
                addSimplePath(w - 1, fy1, w - 1, w - 1, fx2 + 1, fy1, w - 1, w - 1, localPath);
            }
        } else if (fy2 == w - 1) {
            if (fx1 >= 2) {
                addSimplePath(0, 0, fx1 - 1, 0, 0, 0, fx1 - 1, w - 1, localPath);
                addSimplePath(fx1, 0, w - 1, fy1 - 1, fx1, 0, w - 1, fy1 - 1, localPath);
            } else {
                addSimplePath(0, 0, w - 1, fy1 - 1, 0, 0, w - 1, fy1 - 1, localPath);
            }
            addSimplePath(w - 1, fy1, w - 1, w - 1, fx2 + 1, fy1, w - 1, w - 1, localPath);
        } else if (fy1 == 0) {
            addSimplePath(0, 0, fx1 - 1, w - 1, 0, 0, fx1 - 1, w - 1, localPath);
            if (fx2 < w - 2) {
                addSimplePath(fx1, w - 1, fx2, w - 1, fx1, fy2 + 1, fx2, w - 1, localPath);
                addSimplePath(fx2 + 1, w - 1, w - 1, w - 1, fx2 + 1, 0, w - 1, w - 1, localPath);
            } else {
                addSimplePath(fx1, w - 1, w - 1, w - 1, fx1, fy2 + 1, w - 1, w - 1, localPath);
            }
        } else {
            if (fx1 >= 2) {
                addSimplePath(0, 0, fx1 - 1, 0, 0, 0, fx1 - 1, w - 1, localPath);
                addSimplePath(fx1, 0, w - 1, fy1 - 1, fx1, 0, w - 1, fy1 - 1, localPath);
            } else {
                addSimplePath(0, 0, w - 1, fy1 - 1, 0, 0, w - 1, fy1 - 1, localPath);
            }
            if (fy2 < w - 2) {
                addSimplePath(w - 1, fy1, w - 1, fy2, fx2, fy1, w - 1, fy2, localPath);
                addSimplePath(w - 1, fy2 + 1, w - 1, w - 1, fx1, fy2 + 1, w - 1, w - 1, localPath);
            } else {
                addSimplePath(w - 1, fy1, w - 1, w - 1, fx2, fy1, w - 1, w - 1, localPath);
            }
        }
        if (doReverse) reverse(localPath.begin(), localPath.end());
        if (mirror) FOR(i, localPath.size()) localPath[i].first = w - 1 - localPath[i].first;
    } else {
        int rotations = 0;
        while (y1 != 0 || y2 != 0) {
            FOR(i, w) FOR(j, w) localIsFence2[i][j] = localIsFence[j][w - i - 1];
            FOR(i, w) FOR(j, w) localIsFence[i][j] = localIsFence2[i][j];
            int nx = y1;
            int ny = w - x1- 1;
            x1 = nx;
            y1 = ny;
            nx = y2;
            ny = w - x2- 1;
            x2 = nx;
            y2 = ny;
            rotations++;
        }
        if (x1 != 0) {
            swap(x1, x2);
            swap(y1, y2);
            doReverse = true;
        }
        findFence();
        if (fx2 == w - 1) {
            if (fx1 <= 1) {
                addSimplePath(0, 0, w - 1, 0, 0, 0, w - 1, fy1 - 1, localPath);
            } else {
                if (fy2 < w - 2) {
                    addSimplePath(0, 0, fx1 - 2, w - 1, 0, 0, fx1 - 2, w - 1, localPath);
                    addSimplePath(fx1 - 1, w - 1, fx1 - 1, fy2 + 1, fx1 - 1, fy2 + 1, w - 1, w - 1, localPath);
                    addSimplePath(fx1 - 1, fy2, fx1 - 1, 0, fx1 - 1, 0, fx1 - 1, fy2, localPath);
                } else {
                    addSimplePath(0, 0, fx1 - 1, 0, 0, 0, fx1 - 1, w - 1, localPath);
                }
                addSimplePath(fx1, 0, w - 1, 0, fx1, 0, w - 1, fy1 - 1, localPath);
            }
        } else if (fx1 == 0) {
            if (fx2 >= w - 2) {
                addSimplePath(0, 0, w - 1, 0, 0, 0, w - 1, fy1 - 1, localPath);
            } else {
                addSimplePath(0, 0, fx2, 0, 0, 0, fx2, fy1 - 1, localPath);
                if (fy2 < w - 2) {
                    addSimplePath(fx2 + 1, 0, w - 2, fy2, fx2 + 1, 0, w - 2, fy2, localPath);
                    addSimplePath(w - 2, fy2 + 1, w - 2, w - 1, 0, fy2 + 1, w - 2, w - 1, localPath);
                    addSimplePath(w - 1, w - 1, w - 1, 0, w - 1, 0, w - 1, w - 1, localPath);
                } else {
                    addSimplePath(fx2 + 1, 0, w - 1, 0, fx2 + 1, 0, w - 1, w - 1, localPath);
                }
            }
        } else if (fy2 == w - 1) {
            int sx;
            if (fx1 >= 2) {
                addSimplePath(0, 0, fx1 - 1, 0, 0, 0, fx1 - 1, w - 1, localPath);
                sx = fx1;
            } else {
                sx = 0;
            }
            if (fx2 >= w - 2) {
                addSimplePath(sx, 0, w - 1, 0, sx, 0, w - 1, fy1 - 1, localPath);
            } else {
                addSimplePath(sx, 0, fx2, 0, sx, 0, fx2, fy1 - 1, localPath);
                addSimplePath(fx2 + 1, 0, w - 1, 0, fx2 + 1, 0, w - 1, w - 1, localPath);
            }
        } else if (fy1 == 0) {
            addSimplePath(0, 0, fx1 - 1, w - 1, 0, 0, fx1 - 1, w - 1, localPath);
            addSimplePath(fx1, w - 1, fx2, w - 1, fx1, fy1 + 1, fx2, w - 1, localPath);
            addSimplePath(fx2 + 1, w - 1, w - 1, 0, fx2 + 1, 0, w - 1, w - 1, localPath);
        } else {
            addSimplePath(0, 0, fx1 - 1, w - 1, 0, 0, fx1 - 1, w - 1, localPath);
            addSimplePath(fx1, w - 1, w - 1, fy2 + 1, fx1, fy2 + 1, w - 1, w - 1, localPath);
            if (fy1 >= 2) {
                addSimplePath(w - 1, fy2, w - 1, fy1, fx2 + 1, fy1, w - 1, fy2, localPath);
                addSimplePath(w - 1, fy1 - 1, w - 1, 0, fx1, 0, w - 1, fy1 - 1, localPath);
            } else {
                addSimplePath(w - 1, fy2, w - 1, 0, fx2 + 1, 0, w - 1, fy2, localPath);
            }
        }
        if (doReverse) reverse(localPath.begin(), localPath.end());
        FOR(i, rotations) {
            FOR(i, localPath.size()) {
                FOR(j, 3) {
                    int nx = localPath[i].second;
                    int ny = w - localPath[i].first - 1;
                    localPath[i].first = nx;
                    localPath[i].second = ny;
                }
            }
        }
    }
    FOR(i, localPath.size()) {
        localPath[i].first += wx;
        localPath[i].second += wy;
    }
    FOR(i, localPath.size()) currentPath.push_back(localPath[i]);
    printf("Getting path from %d %d %d %d\n", x1 + wx, y1 + wy, x2 + wx, y2 + wy);
    FOR(i, localPath.size()) printf("%d %d, ", localPath[i].first, localPath[i].second);
    printf("\n");
}


bool isFenceOk() {
    if (isFence[0][0]) return false;
    FOR(i, w) FOR(j, w) {
        int wx = i * w;
        int wy = j * w;
        FOR(k, w) if (i < w - 1 && isFence[wx + w - 1][wy + k]) {
            if (wy + k > 0 && isFence[wx + w][wy + k - 1]) return false;
            if (isFence[wx + w][wy + k]) return false;
            if (wy + k < n - 1 && isFence[wx + w][wy + k + 1]) return false;
        }
        FOR(k, w) if (j < w - 1 && isFence[wx + k][wy + w - 1]) {
            if (wx + k > 0 && isFence[wx + k - 1][wy + w]) return false;
            if (isFence[wx + k][wy + w]) return false;
            if (wx + k < n - 1 && isFence[wx + k + 1][wy + w]) return false;
        }
    }
    return true;
}

void generate() {
    srand(time(NULL));
    n = 36;
    w = 6;
    FOR(i, n) FOR(j, n) flowers[i][j] = rand() % 100000 + 1;
    FOR(i, n) FOR(j, n) limit[i][j] = rand() % 10 + 5;
    FOR(i, n) FOR(j, n) regrow[i][j] = rand() % 100 + 1;
    do {
        FOR(i, n) FOR(j, n) isFence[i][j] = false;
        f = 0;
        FOR(i, w) FOR(j, w) {
            int width = rand() % (w - 1) + 1;
            int height = rand() % (w - 1) + 1;
            if (j < 0) {
                fence[f].x1 = i * w + ((i + 1) % 2) * (w - 1);
                fence[f].y1 = j * w + ((i + 1) % 2) * (w - 1);
                fence[f].x2 = fence[f].x1;
                fence[f].y2 = fence[f].y1;
            } else {
                fence[f].x1 = i * w + rand() % (w - width + 1);
                fence[f].y1 = j * w + rand() % (w - height + 1);
                fence[f].x2 = fence[f].x1 + width - 1;
                fence[f].y2 = fence[f].y1 + height - 1;
            }
            FORE(k, fence[f].x1, fence[f].x2 + 1)
                FORE(l, fence[f].y1, fence[f].y2 + 1)
                    isFence[k][l] = true;
            f++;
        }
    } while (!isFenceOk());
}

int temp[MAX_N][MAX_N];


bool vvv[MAX_N][MAX_N];


void printStatus(int sx, int sy, int ex, int ey) {
    printf("%d %d %d %d\n", sx, sy, ex, ey);
    FOR(i, w) {
        FOR(j, w) printf("%d", isFence[j][i]);
        printf("\n");
    }
    FOR(i, currentPath.size()) printf("%d %d\n", currentPath[i].first, currentPath[i].second);
    exit(1);
}


void testPath() {
    w = 6;
    int startStop[][2] = {{0, 0}, {0, w - 1}, {w - 1, 0}, {w - 1}, {w - 1}};
    FOR(i, w - 1) FOR(j, w - 1) {
        FORE(k, 1, w - i) FORE(l, 1, w - j) {
            FOR(a, w) FOR(b, w) vvv[a][b] = isFence[a][b] = false;
            FORE(a, i, i + k) FORE(b, j, j + l) isFence[a][b] = true;
            FOR(a, 4) FOR(b, 4) {
                int sx = startStop[a][0];
                int sy = startStop[a][1];
                int ex = startStop[b][0];
                int ey = startStop[b][1];
                if (!isFence[sx][sy] && !isFence[ex][ey]) {
                    currentPath.clear();
                    addPath(sx, sy, ex, ey);
                    if (currentPath[0].first != sx || currentPath[0].second != sy) {
                        printf("Invalid start\n");
                        printStatus(sx, sy, ex, ey);
                    }
                    int s = currentPath.size();
                    if (currentPath[s - 1].first != ex || currentPath[s - 1].second != ey) {
                        printf("Invalid end\n");
                        printStatus(sx, sy, ex, ey);
                    }
                    FOR(a, w) FOR(b, w) vvv[a][b] = false;
                    FOR(i, s) {
                        if (vvv[currentPath[i].first][currentPath[i].second]) {
                            printf("Visited at %d %d\n", currentPath[i].first, currentPath[i].second);
                            printStatus(sx, sy, ex, ey);
                        }
                        vvv[currentPath[i].first][currentPath[i].second] = true;
                        if (i > 0 && abs(currentPath[i].first - currentPath[i - 1].first) + abs(currentPath[i].second - currentPath[i - 1].second) != 1) {
                            printf("Not neighbors\n");
                            printStatus(sx, sy, ex, ey);
                        }
                        if (currentPath[i].first < 0 || currentPath[i].second < 0 || currentPath[i].first >= w || currentPath[i].second >= w) {
                            printf("Out of bounds\n");
                            printStatus(sx, sy, ex, ey);
                        }
                    }
                }
            }
        }
    }
    printf("Tested\n");
}



int main(void) {
    //testPath();

    n = getInt();
    f = getInt();
    x = getInt() - 1;
    y = getInt() - 1;
    int penalty = getInt();
    FOR(i, n) FOR(j, n) flowers[i][j] = getInt();
    FOR(i, n) FOR(j, n) limit[i][j] = getInt();
    FOR(i, n) FOR(j, n) regrow[i][j] = getInt();
    FOR(i, f) {
        fence[i].x1 = getInt() - 1;
        fence[i].y1 = getInt() - 1;
        fence[i].x2 = getInt() - 1;
        fence[i].y2 = getInt() - 1;
        FORE(j, fence[i].x1, fence[i].x2 + 1)
            FORE(k, fence[i].y1, fence[i].y2 + 1)
                isFence[j][k] = true;
    }
    //generate();

    limit[x][y]--;
    if (isFence[x][y]) {
        while (x > 0 && isFence[x - 1][y]) { x--; print(); }
        while (y > 0 && isFence[x][y - 1]) { y--; print(); }
        //runFence();
        if (x > 0) { x--; print(); } else { y--; print(); }
    }
    w = sqrt(n);
    if (w * w != n) w++;
    if (w * w != n) fail();
    int cx = 0;
    int cy = 0;
    int wx = 0;
    int wy = 0;
    currentPath.clear();

    /*FOR(i, n) FOR(j, n) if (isFence[i][j]) temp[i][j] = -1;
    FOR(i, currentPath.size()) {
        temp[currentPath[i].first][currentPath[i].second] = i + 1;
    }
    FOR(i, n) {
        if (i % w == 0) printf("\n");
        FOR(j, n) {
            if (j % w == 0) printf(" ");
            printf(" %03d", temp[j][i]);
        }
        printf("\n");
    }*/



    FOR(i, w) {
        while (wx < w - 1) {
            int tlx = wx * w + w;
            int tly = wy * w;
            if (!isFence[tlx][tly] && !isFence[tlx - 1][tly]) {
                addPath(cx, cy, tlx - 1, tly);
                cx = tlx;
                cy = tly;
            } else if (!isFence[tlx][tly + w - 1] && !isFence[tlx - 1][tly + w - 1]) {
                addPath(cx, cy, tlx - 1, tly + w - 1);
                cx = tlx;
                cy = tly + w - 1;
            } else {
                int p = 0;
                while (isFence[tlx][tly + p] || isFence[tlx - 1][tly + p]) p++;
                addPath(cx, cy, tlx - 1, tly + p);
                cx = tlx;
                cy = tly + p;
            }
            wx++;
        }
        {
            int tlx = wx * w;
            int tly = wy * w + w;
            if (!isFence[tlx + w - 1][tly] && !isFence[tlx + w - 1][tly - 1]) {
                addPath(cx, cy, tlx + w - 1, tly - 1);
                cx = tlx + w - 1;
                cy = tly;
            } else if (!isFence[tlx][tly] && !isFence[tlx][tly - 1]) {
                printf("Adding path %d %d %d %d\n", cx, cy, tlx, tly - 1);
                addPath(cx, cy, tlx, tly - 1);
                printf("Size: %d\n", currentPath.size());
                cx = tlx;
                cy = tly;
            } else {
                int p = 0;
                while (isFence[tlx + p][tly] || isFence[tlx + p][tly - 1]) p++;
                addPath(cx, cy, tlx + p, tly - 1);
                cx = tlx + p;
                cy = tly;
            }
            wy++;
        }
        while (wx > 0) {
            int tlx = wx * w;
            int tly = wy * w;
            if (!isFence[tlx - 1][tly] && !isFence[tlx][tly]) {
                addPath(cx, cy, tlx, tly);
                cx = tlx - 1;
                cy = tly;
            } else if (!isFence[tlx - 1][tly + w - 1] && !isFence[tlx][tly + w - 1]) {
                addPath(cx, cy, tlx, tly + w - 1);
                cx = tlx - 1;
                cy = tly + w - 1;
            } else {
                int p = 0;
                while (isFence[tlx][tly + p] || isFence[tlx - 1][tly + p]) p++;
                addPath(cx, cy, tlx, tly + p);
                cx = tlx - 1;
                cy = tly + p;
            }
            wx--;
        }
        {
            int tlx = wx * w;
            int tly = wy * w + w;
            if (wy == w - 1) {
                if (!isFence[tlx][tly - 1]) addPath(cx, cy, tlx, tly - 1);
                else addPath(cx, cy, tlx + w - 1, tly - 1);
            } else {
                if (!isFence[tlx][tly] && !isFence[tlx][tly - 1]) {
                    addPath(cx, cy, tlx, tly - 1);
                    cx = tlx;
                    cy = tly;
                } else if (!isFence[tlx + w - 1][tly] && !isFence[tlx + w - 1][tly - 1]) {
                    printf("Adding path %d %d %d %d\n", cx, cy, tlx + w - 1, tly - 1);
                    addPath(cx, cy, tlx + w - 1, tly - 1);
                    printf("Size: %d\n", currentPath.size());
                    cx = tlx + w - 1;
                    cy = tly;
                } else {
                    int p = 0;
                    while (isFence[tlx + p][tly] || isFence[tlx + p][tly - 1]) p++;
                    addPath(cx, cy, tlx + p, tly - 1);
                    cx = tlx + p;
                    cy = tly;
                }
                wy++;
            }
        }
        i++;
    }


    /*FOR(i, n) FOR(j, n) if (isFence[i][j]) temp[i][j] = -1;
    FOR(i, currentPath.size()) {
        temp[currentPath[i].first][currentPath[i].second] = i + 1;
    }
    FOR(i, n) FOR(j, n) if (isFence[i][j]) temp[i][j] = -1;
    FOR(i, n) {
        if (i % w == 0) printf("\n");
        FOR(j, n) {
            if (j % w == 0) printf(" ");
            printf(" %03d", temp[j][i]);
        }
        printf("\n");
    }*/

    auto pathToTop = findPath(x, y, 0, 0);
    for(auto it = pathToTop.begin(); it != pathToTop.end(); it++) {
        x = it->first;
        y = it->second;
        print();
    }
    /*FOR(i, n) FOR(j, n) vvv[i][j] = false;
    FOR(i, currentPath.size()) {
        if (vvv[currentPath[i].first][currentPath[i].second]) {
            printf("Visited at index %d\n", i + 1);
            exit(1);
        }
        vvv[currentPath[i].first][currentPath[i].second] = true;
        if (i > 0 && abs(currentPath[i].first - currentPath[i - 1].first) + abs(currentPath[i].second - currentPath[i - 1].second) != 1) {
            printf("Not neighbors at index %d\n", i + 1);
            exit(1);
        }
        if (currentPath[i].first < 0 || currentPath[i].second < 0 || currentPath[i].first >= n || currentPath[i].second >= n) {
            printf("Out of bounds at index %d %d %d\n", i + 1, currentPath[i].first, currentPath[i].second);
            exit(1);
        }
    }*/

    FOR(i, 2) {
        FOR(i, currentPath.size()) {
            x = currentPath[i].first;
            y = currentPath[i].second;
            print();
        }
        for(int i = currentPath.size() - 1; i >= 0; i--) {
            x = currentPath[i].first;
            y = currentPath[i].second;
            print();
        }
    }
    FOR(i, currentPath.size()) {
        x = currentPath[i].first;
        y = currentPath[i].second;
        if (limit[x][y] <= 0) break;
        print();
    }

    printf("EXIT\n");
}

