// Solve a single line using pre-computed steps. Then apply to all lines followed by all columns.
// https://www.codechef.com/DEC16/problems/THREECOL
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

/*
int n;
char grid[20];
int minDepth = 1000000000;
set<LLI> used;
map<LLI, int> position;
map<LLI, LLI> prevState;


char get(LLI state, int pos) {
    return (state >> (pos * 2)) & 3;
}

LLI setv(LLI state, int pos, unsigned int value) {
    pos <<= 1;
    LLI mask = 3;
    mask <<= pos;
    mask = ~mask;
    state &= mask;
    state |= value << pos;
    return state;
}


LLI mm(LLI state, int pos) {
    char g1 = get(state, pos);
    char g2 = get(state, pos + 1);
    if (g1 != g2) {
        char r;
        FOR(i, 3) if (g1 != i && g2 != i) r = i;
        state = setv(state, pos, r);
        state = setv(state, pos + 1, r);
    }
    return state;
}


LLI convert() {
    LLI res = 0;
    FOR(i, n) res += ((LLI)grid[i]) << (i * 2);
    return res;
}

bool isFinal(LLI state) {
    char start = get(state, 0);
    FORE(i, 1, n) if (get(state, i) != start) return false;
    return true;
}


void pp(LLI state) {
    FOR(i, n) {
        printf("%c", (int)((state & 3) + 'A'));
        state >>= 2;
    }
    printf("\n");
}


int main(void) {
    n = 20;
    FOR(i, 10) grid[i] = 0;
    FOR(i, 10) grid[i + 10] = 1;
    LLI state = convert();
    queue<LLI> q;
    q.push(state);
    used.insert(state);
    while (true) {
        state = q.front();
        q.pop();

        if (isFinal(state)) {
            vector<int> r;
            do {
                printf("%d ", position[state]);
                r.push_back(position[state]);
                pp(state);
                state = prevState[state];
            } while (prevState.find(state) != prevState.end());
            for(int i = r.size() - 1; i >= 0; i--) printf("%d, ", r[i]);
            return 0;
        }

        FOR(i, n - 1) {
            LLI state2 = mm(state, i);
            if (used.find(state2) == used.end()) {
                used.insert(state2);
                q.push(state2);
                position[state2] = i;
                prevState[state2] = state;
            }
        }

    }
}
*/


vector<int> line;
int pos4[] = {1, 0, 1, 0, 2};
int pos5[] = {3, 2, 1, 0, 1, 0, 2};
int pos8[] = {3, 2, 1, 0, 1, 0, 2, 4, 5, 4, 5, 4, 6};
int pos10[] = {7, 6, 5, 4, 3, 2, 1, 0, 1, 0, 2, 4, 5, 4, 7, 6, 8};
int pos11[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 0, 2, 4, 5, 4, 7, 6, 8};
int pos13[] = {7, 6, 5, 4, 3, 2, 1, 0, 1, 0, 2, 6, 5, 8, 9, 8, 7, 10, 9, 11};
int pos16[] = {7, 6, 5, 4, 3, 2, 1, 0, 1, 0, 2, 6, 5, 8, 9, 8, 7, 10, 9, 11, 12, 13, 12, 13, 12, 14};

void solve(int n, int position) {
    switch (n) {
    case 2:
        line.push_back(position);
        break;
    case 4:
        solve(2, position);
        solve(2, position + 2);
        FOR(i, sizeof(pos4) / sizeof(pos4[0])) line.push_back(pos4[i] + position);
        break;
    case 5:
        solve(4, position);
        FOR(i, sizeof(pos5) / sizeof(pos5[0])) line.push_back(pos5[i] + position);
        break;

    case 8:
        solve(4, position);
        solve(4, position + 4);
        FOR(i, sizeof(pos8) / sizeof(pos8[0])) line.push_back(pos8[i] + position);
        break;

    case 10:
        solve(8, position);
        solve(2, position + 8);
        FOR(i, sizeof(pos10) / sizeof(pos10[0])) line.push_back(pos10[i] + position);
        break;

    case 11:
        solve(10, position);
        FOR(i, sizeof(pos11) / sizeof(pos11[0])) line.push_back(pos11[i] + position);
        break;

    case 13:
        solve(8, position);
        solve(5, position + 8);
        FOR(i, sizeof(pos13) / sizeof(pos13[0])) line.push_back(pos13[i] + position);
        break;
    case 16:
        solve(8, position);
        solve(8, position + 8);
        FOR(i, sizeof(pos16) / sizeof(pos16[0])) line.push_back(pos16[i] + position);
        break;
    case 20:
        solve(5, position);
        vector<int> pos2;
        FOR(i, line.size()) pos2.push_back(line[i]);
        line.clear();
        FOR(i, 5) solve(4, i * 4);
        FOR(i, pos2.size())
            FOR(j, sizeof(pos8) / sizeof(pos8[0])) line.push_back(pos8[j] + pos2[i] * 4);
        break;
    }
}

int main(void) {
    int n = getInt();
    solve(n, 0);
    FOR(i, line.size()) line[i]++;
    printf("%d\n", line.size() * 2 * n);
    FOR(i, n) FOR(j, line.size()) printf("%d %d %d %d\n", line[j], i + 1, line[j] + 1, i + 1);
    FOR(i, n) FOR(j, line.size()) printf("%d %d %d %d\n", i + 1, line[j], i + 1, line[j] + 1);

}
