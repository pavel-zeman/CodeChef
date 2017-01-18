// Standard segment tree. As for the squares, pre-calculate as many 1,2,3-tuples as possible and use them to efficiently calculate the 4-tuples.
// https://www.codechef.com/JAN17/problems/FOURSQ
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

LLI sqr(LLI x) {
    return x * x;
}

#define MAX_PRECOMP 100001
#define MAX_N 100010
char cc[MAX_PRECOMP];
int nums[MAX_PRECOMP][3];
int a, b, c, d;
int n, q;
LLI p;
int aa[MAX_N];
LLI tree[3 * MAX_N];

LLI sqrt2(LLI x) {
    LLI sq = sqrt(x);
    if (sqr(sq + 1) <= x) sq++;
    return sq;
}

bool isOk2(int x) {
    if (cc[x] > 0 && cc[x] < 3) {
        a = nums[x][0];
        b = nums[x][1];
        return true;
    } else return false;
}

bool isOk1(int orig, LLI x) {
    if (x < MAX_PRECOMP && cc[x] > 0) {
        a = nums[x][0];
        b = nums[x][1];
        c = nums[x][2];
        return true;
    }
    int ss = sqrt2(x);
    if (isOk2(x - sqr(ss))) {
        c = ss;
        return true;
    } else return false;
}

LLI mult(LLI a, LLI b) {
    LLI res1 = (a & ((1 << 20) - 1)) * b % p;
    LLI res2 = (((a >> 20) * b % p) << 20) % p;
    return (res1 + res2) % p;
}

LLI buildTree(int node, int l, int r) {
    if (l == r) {
        tree[node] = aa[l];
    } else {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        LLI res1 = buildTree(childNode, l, middle);
        LLI res2 = buildTree(childNode + 1, middle + 1, r);
        tree[node] = mult(res1, res2);
    }
    return tree[node];
}

LLI gatherResult(int node, int l, int r, int start, int end) {
    if (start > r || end < l) return 1;
    else {
        if (l >= start && r <= end) return tree[node];
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        LLI res1 = gatherResult(childNode, l, middle, start, end);
        LLI res2 = gatherResult(childNode + 1, middle + 1, r, start, end);
        return mult(res1, res2);
    }
}

LLI updateTree(int node, int l, int r, int pos) {
    if (pos < l || pos > r) return tree[node];
    if (l == r) {
        tree[node] = aa[pos];
    } else {
        int middle = (l + r) >> 1;
        int childNode = node * 2 + 1;
        LLI res1 = updateTree(childNode, l, middle, pos);
        LLI res2 = updateTree(childNode + 1, middle + 1, r, pos);
        tree[node] = mult(res1, res2);
    }
    return tree[node];
}

void getNumbers(LLI x) {
    if (x == 0) a = b = c = d = 0;
    else {
        LLI x2 = x;
        int shifts = 0;
        while ((x2 & 3) == 0) {
            x2 >>= 2;
            shifts++;
        }
        LLI sq = sqrt2(x2);
        LLI y = x2 - sqr(sq);
        while (!isOk1(x2, y)) {
            sq--;
            y = x2 - sqr(sq);
        }
        d = sq;
        if (shifts > 0) {
            a <<= shifts;
            b <<= shifts;
            c <<= shifts;
            d <<= shifts;
        }
    }
}

int main(void) {
    for(int i =0; i * i < MAX_PRECOMP; i++) {
        cc[i * i] = 1;
        nums[i * i][0] = i;
        nums[i * i][1] = 0;
        nums[i * i][2] = 0;
        for(int j = i; j * j + i * i < MAX_PRECOMP; j++) {
            int index = j *j + i *i;
            if (cc[index] == 0 || cc[index] > 2) {
                cc[index] = 2;
                nums[index][0] = i;
                nums[index][1] = j;
                nums[index][2] = 0;
            }
            for(int k = j; j * j + i * i + k * k< MAX_PRECOMP; k++) {
                index = k * k + j * j + i * i;
                if (cc[index] == 0) {
                    cc[index] = 3;
                    nums[index][0] = i;
                    nums[index][1] = j;
                    nums[index][2] = k;
                }
            }
        }
    }
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        q = getInt();
        p = getLongLongInt();
        FOR(i, n) aa[i] = getInt() % p;
        buildTree(0, 0, n - 1);
        FOR(i, q) {
            int op = getInt();
            int x = getInt();
            int y = getInt();
            switch (op) {
            case 1:
                x--;
                aa[x] = y % p;
                updateTree(0, 0, n - 1, x);
                break;
            case 2:
                x--;
                y--;
                LLI res = gatherResult(0, 0, n - 1, x, y);
                getNumbers(res);
                printf("%d %d %d %d\n", a, b, c, d);
                break;
            }
        }
    }
}

