// Description
// https://www.codechef.com/OCT15/problems/MGCHGYM
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


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

#define MAX_K 10
#define MAX_W 100010
#define MAX_N 100010
int wIndex[MAX_W];
char w[MAX_N];
int weight[MAX_K];
int k;

int total[MAX_K];
bool possible[MAX_K][MAX_W];

int main(void) {
    int n = getInt();
    int q = getInt();
    FOR(i, MAX_W) wIndex[i] = -1;
    FOR(i, n) {
        int x = getInt();
        if (wIndex[x] < 0) {
            weight[k] = x;
            wIndex[x] = k++;
        }
        w[i] = wIndex[x];
    }

    FOR(i, q) {
        int op = getInt();
        int l = getInt();
        int r = getInt();
        switch (op) {
            case 1: // set weight
                if (wIndex[r] < 0) {
                    weight[k] = r;
                    wIndex[r] = k++;
                }
                w[l - 1] = wIndex[r];
                break;
            case 2: // reverse
                l--; r--;
                while (l < r) swap(w[l++], w[r--]);
                break;
            case 3: // check
                int targetW = getInt();
                l--;
                //FORE(j, l, r) printf("%d ", weight[w[j]]);
                //printf("\n");
                FOR(j, k) total[j] = 0;
                FORE(j, l, r) total[w[j]]++;
                FOR(j, k) FOR(jj, targetW + 1) possible[j][jj] = false;
                for(int j=0;j<=total[0] && weight[0] * j <= targetW;j++) possible[0][j * weight[0]] = true;
                FORE(j, 1, k) {
                    FOR(x, targetW + 1)
                        if (possible[j - 1][x]) {
                            for(int jj=0;jj<=total[j] && x + weight[j] * jj <= targetW;jj++) possible[j][x + jj * weight[j]] = true;
                        }
                }
                /*FOR(j, k) {
                    printf("%d (%d): ", weight[j], total[j]);
                    FOR(jj, targetW + 1) printf("%d ", possible[j][jj]);
                    printf("\n");
                }*/
                printString(possible[k - 1][targetW] ? "Yes" : "No");
                break;
        }

    }
}

