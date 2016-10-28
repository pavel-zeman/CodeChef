// Remove the D smallest numbers, then create line between the minimum and maximum number and find pairs of numbers, which can be switched to minimize the total score
// https://www.codechef.com/OCT16/problems/SEAARI
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

double cpu() {
    return clock() / (double)CLOCKS_PER_SEC;
}

#define MAX_N 100010
int a[MAX_N];
int a2[MAX_N];
int origPosition[MAX_N];
bool removed[MAX_N];

int main(void) {
    int n = getInt();
    int k = getInt();
    int d = getInt();
    vector<pair<int, int> > vs;
    FOR(i, n) {
        a[i] = getSignedInt();
        vs.push_back(make_pair(a[i], i));
    }
    sort(vs.begin(), vs.end());
    vector<int> removedIndices;
    FOR(i, d / 2) {
        removed[vs[i].second] = true;
        removedIndices.push_back(vs[i].second + 1);
    }
    FOR(i, d / 2) {
        removed[vs[n - 1 - i].second] = true;
        removedIndices.push_back(vs[n - 1 - i].second + 1);
    }
    int ci = 0;
    vector<pair<int, int> > swaps;

    n -= d;
    ci = 0;
    LLI total = 0;
    FOR(i, n) {
        while (removed[ci]) ci++;
        origPosition[i] = ci;
        total += (a2[i] = a[ci]);
        ci++;
    }

    int mm = vs[d / 2].first;
    int mx = vs[n + d/2 - 1].first;
    double alfa = mm;
    double beta = (mx - mm) / (double)(n - 1);
    double lin[MAX_N];
    FOR(i, n) lin[i] = alfa + beta * i;


    if (k < 30000) {
        FOR(i, k) {
            double mx = 0;
            int mxp = 0;
            FOR(j, n) {
                double dd = abs(a2[j] - lin[j]);
                if (dd > mx) {
                    mxp = j;
                    mx = dd;
                }
            }

            double mxc = 0;
            int mx2p = -1;
            FOR(j, n) {
                if (j != mxp) {
                    double dd = abs(a2[j] - lin[j]);
                    double nn = abs(a2[j] - lin[mxp]) + abs(a2[mxp] - lin[j]);
                    double diff = mx + dd - nn;
                    if (diff > mxc) {
                        mxc = diff;
                        mx2p = j;
                    }
                }
            }
            swaps.push_back(make_pair(origPosition[mxp] + 1, origPosition[mx2p] + 1));
            swap(a2[mxp], a2[mx2p]);

            if (i % 100 == 0 && cpu() > 1.9) break;
        }
    } else {
        set<pair<int, int> > mins;
        FOR(i, n) mins.insert(make_pair(-abs(a2[i] - lin[i]), i));
        FOR(i, k) {
            double mx = -mins.begin()->first;
            int mxp = mins.begin()->second;

            int index = (a2[mxp] - alfa) / beta;
            int i1 = max(index - 500, 0);
            int i2 = min(index + 500, n);

            double mxc = 0;
            int mx2p = -1;
            FORE(j, i1, i2) {
                if (j != mxp) {
                    double dd = abs(a2[j] - lin[j]);
                    double nn = abs(a2[j] - lin[mxp]) + abs(a2[mxp] - lin[j]);
                    double diff = mx + dd - nn;
                    if (diff > mxc) {
                        mxc = diff;
                        mx2p = j;
                    }
                }
            }
            mins.erase(make_pair(-abs(a2[mxp] - lin[mxp]), mxp));
            mins.erase(make_pair(-abs(a2[mx2p] - lin[mx2p]), mx2p));

            swaps.push_back(make_pair(origPosition[mxp] + 1, origPosition[mx2p] + 1));
            swap(a2[mxp], a2[mx2p]);
        }
    }

    printf("%.lf %.lf\n", alfa, beta);

    FOR(i, swaps.size()) printf("1 %d %d\n", swaps[i].first, swaps[i].second);
    FOR(i, removedIndices.size()) printf("2 %d\n", removedIndices[i]);

    double result = 0;
    FOR(i, n) result += abs(a2[i] - alfa - beta * i);
    result /= n;

    printf("-1\n");

    //printf("%.lf\n", result);
    //printf("%u\n", swaps.size());
}

