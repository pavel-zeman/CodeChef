// Cache number of numbers modulo 5, 7, 8, 9 which are less than all possible powers of 10
// https://www.codechef.com/JULY16/problems/WORKCHEF
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

int getSpecial(LLI x) {
    int used = 1;
    int total = 0;
    LLI t = x;
    while (t > 0) {
        int d = t % 10;
        if ((used & (1 << d)) == 0) {
            used |= 1 << d;
            if (x % d == 0) total++;
        }
        t /= 10;
    }
    return total;
}

#define COMB (1 << 9)
#define MUL (9 * 8 * 7 * 5)
LLI p[18][COMB][MUL];
LLI temp[COMB][MUL];
int combIndex[MUL][MUL];

int getIndex(LLI value) {
    return (value % 9) + (value % 8) * 9 + (value % 7) * 9 * 8 + (value % 5) * 9 * 8 * 7;
}

void getMods(int *mods, int value) {
    mods[9] = value % 9;
    value /= 9;
    mods[8] = value % 8;
    value /= 8;
    mods[7] = value % 7;
    value /= 7;
    mods[5] = value;
}

void getMods2(int *mods, int value) {
    getMods(mods, value);
    mods[2] = mods[8] % 2;
    mods[3] = mods[9] % 3;
    mods[4] = mods[8] % 4;
    mods[6] = mods[3] + (mods[2] == mods[3] % 2 ? 0 : 3);
}


int getCombIndex3(int *mods, int *mods2) {
    return (mods2[9] + mods[9]) % 9 +
        (mods2[8] + mods[8]) % 8 * 9 +
        (mods2[7] + mods[7]) % 7 * 9 * 8 +
        (mods2[5] + mods[5]) % 5 * 9 * 8 * 7;
}


int getBits(LLI value) {
    int result = 0;
    while (value > 0) {
        int d = value % 10;
        if (d > 0) result |= 1 << (d - 1);
        value /= 10;
    }
    return result;
}


void getTotalInternal(LLI mx, int kk) {
    memset(temp, 0, sizeof(temp));
    LLI power = 1;
    int index = 0;
    while (power <= mx) {
        power *= 10;
        index++;
    }
    power /= 10;
    index--;
    index--;

    LLI v = 0;
    while (index >= 0) {
        int j = 0;
        while (v + power <= mx) {
            int pp = getIndex(v);
            int bb = getBits(v);
            FOR(k, COMB)
                FOR(l, MUL)
                    if (p[index][k][l] != 0)
                        temp[k | bb][combIndex[pp][l]] += p[index][k][l];
            j++;
            v += power;
        }
        index--;
        power /= 10;
    }
}


LLI getTotal(LLI mx, int k) {
    getTotalInternal(mx, k);

    LLI result = 0;
    FOR(i, COMB) {
        int totalBits = 0;
        bool bits[10];
        FORE(j, 1, 10) if ((i & (1 << (j - 1))) != 0) {
            totalBits++;
            bits[j] = true;
        } else bits[j] = false;
        if (totalBits >= k) {
            FOR(j, MUL) if (temp[i][j] > 0) {
                int mods[10];
                getMods2(mods, j);
                int n = 0;
                if (bits[1]) n++;
                FORE(kk, 2, 10) if (bits[kk] && mods[kk] == 0) n++;
                if (n >= k) result += temp[i][j];
            }
        }
    }

    for(LLI t = mx - mx % 10; t <= mx; t++)
        if (getSpecial(t) >= k) result++;
    return result;
}

int main(void) {
    FOR(i, MUL) FORE(j, i, MUL) {
        int mods1[10], mods2[10];
        getMods(mods1, i);
        getMods(mods2, j);
        combIndex[i][j] = combIndex[j][i] = getCombIndex3(mods1, mods2);
    }

    FOR(i, 10) p[0][i == 0 ? 0 : 1 << (i - 1)][getIndex(i)] = 1;

    LLI power = 1;
    FORE(i, 1, 18) {
        power *= 10;
        memcpy(p + i, p + i - 1, sizeof(p[0]));

        int pp[10];
        FORE(j, 1, 10) pp[j] = getIndex(power * j);

        FOR(k, COMB)
            FOR(l, MUL)
                if (p[i - 1][k][l] != 0)
                    FORE(j, 1, 10)
                        p[i][k | (1 << (j - 1))][combIndex[pp[j]][l]] += p[i - 1][k][l];
    }

    LLI mmm = 1000000000000000000LL;
    int t = getInt();
    FOR(tt, t) {
        LLI l = getLongLongInt();
        LLI r = getLongLongInt();
        int k = getInt();
        LLI result = 0;
        if (l == mmm && r == mmm) result = getSpecial(l) >= k ? 1 : 0;
        else if (r == mmm) result = getTotal(r - 1, k) - getTotal(l - 1, k) + (getSpecial(r) >= k ? 1 : 0);
        else result = getTotal(r, k) - getTotal(l - 1, k);
        print(result);
    }
}

