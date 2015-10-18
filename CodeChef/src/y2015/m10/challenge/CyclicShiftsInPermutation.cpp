// If N = K, then there are just N possible permutations. Else if K is even, then any permutation is possible. If K is odd, then P and Q must have the same parity. To calculate order, Fenwick tree is used.
// https://www.codechef.com/OCT15/problems/PERSHFTS
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


#define MOD 1000000007
#define MAX_N 100002

#define MAX_SIZE MAX_N

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


int p[MAX_N], q[MAX_N];
int fact[MAX_N];
int factHalf[MAX_N];
bool used[MAX_N];

int getParity(int *data, int n) {
    FOR(i, n) used[i] = false;
    int total = 0;
    FOR(i, n) {
        if (!used[data[i]]) {
            int j = i;
            int length = 0;
            while (!used[data[j]]) {
                used[data[j]] = true;
                j = data[j];
                length++;
            }
            total += length - 1;
        }
    }
    return total & 1;
}

int main(void) {
    fact[0] = 1;
    FORE(i, 1, MAX_N) fact[i] = (fact[i - 1] * (long long int)i) % MOD;
    factHalf[0] = factHalf[1] = 0;
    factHalf[2] = 1;
    FORE(i, 3, MAX_N) factHalf[i] = (factHalf[i - 1] * (long long int)i) % MOD;

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int k = getInt();
        FOR(i, n) p[i] = getInt() - 1;
        FOR(i, n) q[i] = getInt() - 1;

        int order = -1;
        if (n == k) {
            int ip = 0;
            while (p[ip] != 0) ip++;
            int iq = 0;
            while (q[iq] != 0) iq++;

            bool ok = true;
            FOR(i, n) if (p[(ip + i) % n] != q[(iq + i) % n]) {
                ok = false;
                break;
            }
            if (ok) order = q[0] + 1;
        } else if ((k & 1) == 0) {
            fenwick.reset(n);
            order = 0;
            FOR(i, n - 1) {
                int localOrder = q[i] - fenwick.read(q[i]);
                fenwick.update(q[i] + 1, 1);
                order = ((localOrder * (long long int)fact[n - 1 - i]) % MOD + order) % MOD;
            }
            order = (order + 1) % MOD;
        } else {
            // must have the same parity
            if (getParity(p, n) == getParity(q, n)) {
                order = 0;
                fenwick.reset(n);
                FOR(i, n - 1) {
                    int localOrder = q[i] - fenwick.read(q[i]);
                    fenwick.update(q[i] + 1, 1);
                    order = ((localOrder * (long long int)factHalf[n - 1 - i]) % MOD + order) % MOD;
                }
                order = (order + 1) % MOD;
            }
        }

        print(order);
    }
}

