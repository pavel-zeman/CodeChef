// Calculate rows with the maximum number of occurrences for each number. Then go column by column and find appropriate row.
// https://www.codechef.com/FEB16/problems/SEATL
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

void fail() {
    *((char *)0) = 0;
}

#define MAX_A 1000010
int a[MAX_A];
vector<int> row[MAX_A];
int rowMax[MAX_A];

bool localUsed[MAX_A];
int f[MAX_A];


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        FOR(i, n) FOR(j, m) a[i * m + j] = getInt();

        set<int> rowUsed;
        FOR(i, n) {
            vector<int> used;
            FOR(j, m) {
                int v = a[i * m + j];
                if (!localUsed[v]) {
                    localUsed[v] = true;
                    used.push_back(v);
                }
                f[v]++;
            }
            for(vector<int>::iterator it = used.begin(); it != used.end();it++) {
                int v = *it;
                if (f[v] >= rowMax[v]) {
                    if (f[v] > rowMax[v]) {
                        rowUsed.insert(v);
                        rowMax[v] = f[v];
                        row[v].clear();
                    }
                    row[v].push_back(i);
                }
                f[v] = 0;
                localUsed[v] = false;
            }
        }

        int result = 0;
        FOR(i, m) {
            vector<int> used;

            FOR(j, n) {
                int v = a[i + j * m];
                if (!localUsed[v]) {
                    localUsed[v] = true;
                    used.push_back(v);
                }
                f[v]++;
            }
            for(vector<int>::iterator it = used.begin(); it != used.end();it++) {
                int v = *it;
                int ct = rowMax[v] + f[v];
                if (ct > result) {
                    FOR(k, row[v].size()) {
                        int c = ct - (a[row[v][k] * m + i] == v);
                        if (c > result) result = c;
                    }
                }
                f[v] = 0;
                localUsed[v] = false;
            }
        }


        for(set<int>::iterator it = rowUsed.begin();it!=rowUsed.end();it++) {
            row[*it].clear();
            rowMax[*it] = 0;
        }

        print(result);
    }
}

