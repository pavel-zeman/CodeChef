// Process the queries in the order of descending K. Use Fenwick tree to store blocks of size at least K.
// https://www.codechef.com/APRIL17/problems/SMARKET
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


// Fenwick tree
#define MAX_SIZE 100010

template <class type> class Fenwick {
private:
    type tree[MAX_SIZE];
    int n;

public:
    type read(int idx){
        type sum = 0;
        while (idx > 0){
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    void update(int idx , type val){
        while (idx <= n){
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }

    void reset(int n) {
        this->n = n;
        FOR(i, n + 1) tree[i] = 0;
    }
};

Fenwick<int> fenwick;

#define MAX_N 100010
int a[MAX_N];
vector<int> block[MAX_N];
int start[MAX_N];
int length[MAX_N];
int rr[MAX_N];

#define MAX_Q 100010
struct Query {
    int l, r, k;
    int ord;
} query[MAX_Q];

bool kOrder(const Query &i, const Query &j) {
    return i.k > j.k;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int q = getInt();
        FOR(i, n) a[i] = getInt();
        int last = a[0];
        int c = 0;
        int s = 0;
        FOR(i, n + 1) block[i].clear();
        FOR(i, n) {
            if (a[i] != last) {
                block[i - s].push_back(s);
                length[s] = i - s;
                last = a[i];
                c = 0;
                s = i;
            }
            start[i] = s;
            c++;
        }
        block[n - s].push_back(s);
        length[s] = n - s;
        fenwick.reset(n + 1);
        FOR(i, q) {
            query[i].l = getInt() - 1;
            query[i].r = getInt() - 1;
            query[i].k = getInt();
            query[i].ord = i;
        }
        sort(query, query + q, kOrder);
        int lastK = n;
        FOR(i, q) {
            int k = query[i].k;
            int l = query[i].l;
            int r = query[i].r;
            while (lastK >= k) {
                FOR(j, block[lastK].size()) fenwick.update(block[lastK][j] + 1, 1);
                lastK--;
            }
            int result = 0;
            if (k <= r - l + 1) result += fenwick.read(r - k + 2) - fenwick.read(l);
            int s1 = start[l];
            if (s1 != l && length[s1] - (l - s1) >= k) result++;
            rr[query[i].ord] = result;
        }
        FOR(i, q) print(rr[i]);
    }
}

