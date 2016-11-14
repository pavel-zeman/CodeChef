// Use spiral as the path through the cube
// https://www.codechef.com/NOV16/problems/SEAWCU
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

#define MAX_N 62
int a[MAX_N][MAX_N][MAX_N];
bool used[MAX_N][MAX_N][MAX_N];
int n;

struct Point {
    int x, y, z;

    Point() {}
    Point(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

Point neighbors[] = {
    Point(-1, 0, 0), Point(1, 0, 0),
    Point(0, -1, 0), Point(0, 1, 0),
    Point(0, 0, -1), Point(0, 0, 1)
};

int dirs[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<pair<int, int> > sample;

bool isValid(int x, int y, int z) {
    return x >= 0 && x < n && y >= 0 && y < n && z >= 0 && z < n;
}

bool isNextValid(int x, int y, int z, Point &last) {
    if (!isValid(x, y, z)) return false;
    if (used[x][y][z]) return false;
    FOR(i, 6) {
        int nx = x + neighbors[i].x;
        int ny = y + neighbors[i].y;
        int nz = z + neighbors[i].z;
        if (isValid(nx, ny, nz) && used[nx][ny][nz] && (nx != last.x || ny != last.y || nz != last.z))
            return false;
    }
    return true;
}

void fillSample() {
    sample.clear();
    int dir = 0;
    int l = n - 1;
    int x = 0, y = 0;
    sample.push_back(make_pair(x, y));
    FOR(i, l) {
        x += dirs[dir][0];
        y += dirs[dir][1];
        sample.push_back(make_pair(x, y));
    }
    dir = (dir + 1) & 3;
    FOR(ii, 2) {
        FOR(i, l) {
            x += dirs[dir][0];
            y += dirs[dir][1];
            sample.push_back(make_pair(x, y));
        }
        dir = (dir + 1) & 3;
    }
    l -= 2;
    while (l > 1) {
        FOR(ii, 2) {
            FOR(i, l) {
                x += dirs[dir][0];
                y += dirs[dir][1];
                sample.push_back(make_pair(x, y));
            }
            dir = (dir + 1) & 3;
        }
        l -= 2;
    }

    //FOR(i, sample.size()) printf("%d %d\n", sample[i].first, sample[i].second);
}

int main(void) {
        int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) FOR(j, n) FOR(k, n) a[k][j][i] = getSignedInt();
        FOR(i, n) FOR(j, n) FOR(k, n) used[i][j][k] = 0;
        LLI totalmm = 0;
        vector<Point> totalResult;

        fillSample();

        /*FOR(ii, n) FOR(jj, n) {
            vector<Point> result;
            Point last(0, ii, jj);
            result.push_back(last);
            while (true) {
                used[last.x][last.y][last.z] = true;
                Point next;
                bool found = false;
                int mm = -1000000000;
                FOR(i, 6) {
                    int nx = last.x + neighbors[i].x;
                    int ny = last.y + neighbors[i].y;
                    int nz = last.z + neighbors[i].z;
                    if (a[nx][ny][nz] > mm && isNextValid(nx, ny, nz, last)) {
                        found = true;
                        next.x = nx;
                        next.y = ny;
                        next.z = nz;
                        mm = a[nx][ny][nz];
                    }
                }
                if (!found) break;
                result.push_back(next);
                last = next;
            }
            LLI sum = 0;
            LLI mm = 0;
            int c = 0;
            FOR(i, result.size()) {
                sum += a[result[i].x][result[i].y][result[i].z];
                if (sum > mm) {
                    mm = sum;
                    c = i + 1;
                }
            }
            //printf("%d\n", result.size());
            if (mm > totalmm) {
                totalResult.clear();
                totalmm = mm;
                FOR(i, c) totalResult.push_back(result[i]);
            }
            FOR(i, result.size()) used[result[i].x][result[i].y][result[i].z] = false;
        }*/
        // Try spiral
        {
            vector<Point> result;
            bool forw = true;
            for(int z = 0; z < n; z += 2) {
                if (forw) {
                    FOR(i, sample.size()) result.push_back(Point(sample[i].first, sample[i].second, z));
                    if (z < n - 1) result.push_back(Point(sample[sample.size() - 1].first, sample[sample.size() - 1].second, z + 1));
                } else {
                    for(int i=sample.size() - 1; i >= 0; i--) result.push_back(Point(sample[i].first, sample[i].second, z));
                    if (z < n - 1) result.push_back(Point(sample[0].first, sample[0].second, z + 1));
                }
                forw = !forw;
            }

            LLI sum = 0;
            LLI mm = 0;
            int c = 0;
            FOR(i, result.size()) {
                sum += a[result[i].x][result[i].y][result[i].z];
                if (sum > mm) {
                    mm = sum;
                    c = i + 1;
                }
            }
            //printf("%d\n", result.size());
            if (mm > totalmm) {
                totalResult.clear();
                totalmm = mm;
                FOR(i, c) totalResult.push_back(result[i]);
            }
        }


        print(totalResult.size());
        FOR(i, totalResult.size())
            printf("%d %d %d\n", totalResult[i].x + 1, totalResult[i].y + 1, totalResult[i].z + 1);
        //print(totalmm);
    }
}

