// Finally a working solution with complexity of O(Q * sqrt(N) * log(N)). Based on an idea described in https://discuss.codechef.com/questions/74081/distnum-editorial with 3-dimensional space (the third dimension is item value) and sqrt-decomposition.
// https://www.codechef.com/MAY16/problems/DISTNUM2
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

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 100010
#define MAX_BLOCKS 460

struct Item {
    int a;
    int prev;
    int converted;
} items[MAX_N];

int toA[MAX_N];
int toAIndex[MAX_N];
int blockSize, blocks;
pair<int, int> sa[MAX_N];
int nextIndex[MAX_N];

unordered_map<int, int> prevPosition;

// index, prev index, value
int cc3[MAX_BLOCKS][MAX_BLOCKS][MAX_BLOCKS];

// index, value
int cc2[MAX_BLOCKS][MAX_BLOCKS];

int getCount3(int a, int b, int c) {
    int ba = (a + 1) / blockSize;
    int bb = (b + 1) / blockSize;
    int bc = (c + 1) / blockSize;
    int result = 0;

    if (b >= 0) {
        if (ba > 0 && bb > 0 && bc > 0) {
            result = cc3[ba - 1][bb - 1][bc - 1];

            ba *= blockSize;
            bb *= blockSize;
            bc *= blockSize;
            FORE(i, ba, a + 1) {
                if (items[i].prev <= b && items[i].prev >= 0 && items[i].converted <= c) result++;
            }

            FORE(i, bb, b + 1) {
                int ind = nextIndex[i];
                if (ind >= 0 && ind < ba && items[ind].prev >= 0 && items[ind].converted <= c) result++;
            }

            FORE(i, bc, c + 1) {
                int ind = toAIndex[i];
                if (ind < ba && items[ind].prev < bb && items[ind].prev >= 0) result++;
            }
        } else {
            result = 0;
            if (a <= c && a <= b) {
                FORE(i, 0, a + 1) {
                    if (items[i].prev <= b && items[i].prev >= 0 && items[i].converted <= c) result++;
                }
            } else if (b <= c && b <= a) {
                FORE(i, 0, b + 1) {
                    int ind = nextIndex[i];
                    if (ind >= 0 && ind <= a && items[ind].prev >= 0 && items[ind].converted <= c) result++;
                }
            } else {
                FORE(i, 0, c + 1) {
                    int ind = toAIndex[i];
                    if (ind <= a && items[ind].prev <= b && items[ind].prev >= 0) result++;
                }
            }
        }
    }
    return result;
}

int getCount2(int a, int b) {
    int ba = (a + 1) / blockSize;
    int bb = (b + 1) / blockSize;
    int result = 0;

    if (ba > 0 && bb > 0) {
        result = cc2[ba - 1][bb - 1];

        ba *= blockSize;
        bb *= blockSize;
        FORE(i, ba, a + 1) {
            if (items[i].converted <= b && items[i].prev < 0) result++;
        }

        FORE(i, bb, b + 1) {
            int ind = toAIndex[i];
            if (ind < ba && items[ind].prev < 0) result++;
        }
    } else {
        result = 0;
        if (a <= b) {
            FORE(i, 0, a + 1) {
                if (items[i].converted <= b && items[i].prev < 0) result++;
            }
        } else {
            FORE(i, 0, b + 1) {
                int ind = toAIndex[i];
                if (ind <= a && items[ind].prev < 0) result++;
            }
        }
    }
    return result;
}

int getCount(int a1, int a2, int b, int c) {
    int res = getCount3(a2, b, c) - (a1 > 0 ? getCount3(a1 - 1, b, c) : 0);
    res += getCount2(a2, c) - (a1 > 0 ? getCount2(a1 - 1, c) : 0);
    return res;
}


int main(void) {
    int n = getInt();
    int q = getInt();
    FOR(i, n) nextIndex[i] = -1;

    FOR(i, n) {
        items[i].a = getInt();
        sa[i].first = items[i].a;
        sa[i].second = i;

        unordered_map<int, int>::iterator it = prevPosition.find(items[i].a);
        items[i].prev = it == prevPosition.end() ? -1 : it->second;
        if (items[i].prev >= 0) nextIndex[items[i].prev] = i;

        prevPosition[items[i].a] = i;
    }

    sort(sa, sa + n);
    FOR(i, n) {
        items[sa[i].second].converted = i;
        toA[i] = items[sa[i].second].a;
        toAIndex[i] = sa[i].second;
    }

    blockSize = sqrt(n) * 0.7;
    if (blockSize < 1) blockSize = 1;
    blocks = (n + blockSize - 1) / blockSize;

    FOR(i, n) {
        if (items[i].prev >= 0)
            cc3[i / blockSize][items[i].prev / blockSize][items[i].converted / blockSize]++;
        else
            cc2[i / blockSize][items[i].converted / blockSize]++;
    }

    FOR(i, blocks) FOR(j, blocks) FOR(k, blocks) {
        if (i > 0) cc3[i][j][k] += cc3[i - 1][j][k];
        if (j > 0) cc3[i][j][k] += cc3[i][j - 1][k];
        if (k > 0) cc3[i][j][k] += cc3[i][j][k - 1];
        if (i > 0 && j > 0) cc3[i][j][k] -= cc3[i - 1][j - 1][k];
        if (i > 0 && k > 0) cc3[i][j][k] -= cc3[i - 1][j][k - 1];
        if (j > 0 && k > 0) cc3[i][j][k] -= cc3[i][j - 1][k - 1];
        if (i > 0 && j > 0 && k > 0) cc3[i][j][k] += cc3[i - 1][j - 1][k - 1];
    }
    FOR(i, blocks) FOR(j, blocks) {
        if (i > 0) cc2[i][j] += cc2[i - 1][j];
        if (j > 0) cc2[i][j] += cc2[i][j - 1];
        if (i > 0 && j > 0) cc2[i][j] -= cc2[i - 1][j - 1];
    }

    int lastResult = 0;
    FOR(qq, q) {
        int a1 = getInt();
        int b1 = getInt();
        int c1 = getInt();
        int d1 = getInt();
        int k = getInt();
        int l = (a1 * (LLI)max(lastResult, 0) + b1) % n;
        int r = (c1 * (LLI)max(lastResult, 0) + d1) % n;
        if (l > r) swap(l, r);

        lastResult = -1;
        if (getCount(l, r, l - 1, n - 1) >= k) {
            int x = 0;
            int y = n - 1;
            while (y - x > blockSize * 4) {
                int m = (x + y) >> 1;
                int kk = getCount(l, r, l - 1, m);
                if (kk >= k) y = m; else x = m + 1;
            }
            int kk = getCount(l, r, l - 1, x);
            if  (kk == k) lastResult = toA[x];
            else {
                FORE(i, x + 1, y + 1) {
                    int ind = toAIndex[i];
                    if (ind >= l && ind <= r && items[ind].prev < l) kk++;
                    if (kk == k) {
                        lastResult = toA[i];
                        break;
                    }
                }
            }
        }
        print(lastResult);
    }
}

