// Just a simple algorithm, which deletes or inserts characters to make both strings the same length and then swaps or replaces all different characters.
// https://www.codechef.com/DEC16/problems/EDIT
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

#define MAX_L 100010
char s1[MAX_L], s2[MAX_L];
int r[26][26];
queue<int> pos[26 * 26];

struct {
    char op;
    int p;
    int p2;
    char c;
} operations[MAX_L];

int opCount;

int getIndex(char from, char to) {
    return (from - 'A') * 26 + (to - 'A');
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int s1l = getString(s1);
        int s2l = getString(s2);
        int ii = getInt();
        int d = getInt();
        int w = getInt();
        FOR(i, 26) FOR(j, 26) r[i][j] = getInt();
        opCount = 0;
        if (s1l < s2l) {
            FORE(i, s1l, s2l) {
                operations[opCount].op = 'I';
                operations[opCount].p = i;
                operations[opCount].c = s2[i];
                opCount++;
            }
        } else if (s1l > s2l) {
            for(int i = s1l; i > s2l; i--) {
                operations[opCount].op = 'D';
                operations[opCount].p = i;
                opCount++;
            }
        }
        FOR(i, min(s1l, s2l)) if (s1[i] != s2[i]) pos[getIndex(s1[i], s2[i])].push(i);
        FOR(i, min(s1l, s2l)) if (s1[i] != s2[i]) {
            int ind1 = getIndex(s1[i], s2[i]);
            int ind2 = getIndex(s2[i], s1[i]);
            if (pos[ind2].empty()) {
                operations[opCount].op = 'R';
                operations[opCount].p = i + 1;
                operations[opCount].c = s2[i];
                opCount++;
            } else {
                operations[opCount].op = 'S';
                operations[opCount].p = i + 1;
                operations[opCount].p2 = pos[ind2].front() + 1;
                swap(s1[i], s1[pos[ind2].front()]);
                pos[ind2].pop();
                opCount++;
            }
            pos[ind1].pop();
        }

        printf("%d\n", opCount);
        FOR(i, opCount) {
            switch (operations[i].op) {
                case 'I':
                case 'R':
                    printf("%c %d %c\n", operations[i].op, operations[i].p, operations[i].c);
                    break;
                case 'D':
                    printf("%c %d\n", operations[i].op, operations[i].p);
                    break;
                case 'S':
                    printf("%c %d %d\n", operations[i].op, operations[i].p, operations[i].p2);
                    break;

            }
        }
    }
}

