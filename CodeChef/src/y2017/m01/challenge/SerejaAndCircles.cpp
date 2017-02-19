// Pretty naive solution using fixed positions and selecting each circle to maximize the minimum distance
// https://www.codechef.com/JAN17/problems/SEACIR
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

#define MAX_N 410
int r[2 * MAX_N];

pair<int, int> positions[MAX_N];
bool used[MAX_N];
int rr[MAX_N];

int sqr(int a) {
    return a * a;
}


int main(void) {
    int n = getInt();
    int s = getInt();
    int skip = getInt();

    FOR(i, 2 * n) r[i] = getInt();

    sort(r, r + 2 * n);
    //int mxr = r[2 * n - skip - 1];
    int mxr = r[n];
    int toPlace = n - skip;
    int ss = sqrt(toPlace);
    if (ss * ss < toPlace) ss++;
    int smr = s - 2 * mxr;
    int stepX = smr / (ss - 1);
    int stepY = stepX * sqrt(3) / 2 + 1;
    while (true) {
        int total = 0;
        int y = 0;
        bool ok = true;
        FOR(i, toPlace) {
            total += smr / stepX;
            if ((i & 1) == 0) total++;
            if (total >= toPlace) break;
            y += stepY;
            if (y > smr) {
                ok = false;
                break;
            }
        }
        if (ok) {
            stepX++;
            stepY = stepX * sqrt(3) / 2 + 1;
        } else {
            stepX--;
            stepY = stepX * sqrt(3) / 2 + 1;
            break;
        }

    }

    int row = 0;
    int x = 0, y = 0;
    int generated = 0;
    while (true) {
        positions[generated++] = make_pair(x + mxr, y + mxr);
        x += stepX;
        if (x > smr) {
            x = (row & 1) == 0 ? stepX >> 1 : 0;
            y += stepY;
            row++;
        }
        if (y > smr) break;
    }

    int placed = 0;
    FOR(i, n) {
        int r1 = getInt();
        if (r1 <= r[2 * n - skip - 10] && placed < toPlace) {
            int p = -1;
            if (placed == 0) {
                p = 0;
                while (positions[p].first < r1 || positions[p].second < r1 || s - positions[p].first < r1 || s - positions[p].second < r1) p++;
            } else {
                double maxD = 0;
                FOR(i, generated) {
                    if (!used[i] && positions[i].first >= r1 && positions[i].second >= r1 && s - positions[i].first >= r1 && s - positions[i].second >= r1) {
                        double minD = s;
                        FOR(j, generated)
                            if (used[j]) {
                                double d = sqrt(sqr(positions[i].first - positions[j].first) + sqr(positions[i].second - positions[j].second)) - r1 - rr[j];
                                if (d < minD) minD = d;
                            }
                        if (minD > maxD) {
                            maxD = minD;
                            p = i;
                        }
                    }
                }
            }
            if (p >= 0) {
                printf("%d %d\n", positions[p].first, positions[p].second);
                used[p] = true;
                rr[p] = r1;
                placed++;
            } else printf("-1 -1\n");
        } else printf("-1 -1\n");
        fflush(stdout);
    }

    double minD = s;
    FOR(i, generated) {
        FOR(j, generated)
            if (i != j && used[i] && used[j]) {
                double d = sqrt(sqr(positions[i].first - positions[j].first) + sqr(positions[i].second - positions[j].second)) - rr[i] - rr[j];
                if (d < minD) minD = d;
            }
    }
    printf("%lf\n", minD);

}

