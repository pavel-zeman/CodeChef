// Use segment tree to track the maximum and update the tree only if the maximum is greater than 1
// https://www.codechef.com/SEPT16/problems/DIVMAC
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

#define MAX_N 100010
#define MAX_P 1001
vector<int> divs[MAX_N];

bool prime[MAX_P];
int primes[MAX_P];
int primeCount;
int tree[MAX_N * 2];

void calcPrimes() {
    FOR(i, MAX_P) prime[i] = true;
    FORE(i, 2, MAX_P) {
        if (prime[i]) {
            primes[primeCount++] = i;
            for(int j = i + i; j < MAX_P; j += i) prime[j] = false;
        }
    }
}

void calcDivs(int pos, int v) {
    divs[pos].clear();
    FOR(i, primeCount) {
        while (v % primes[i] == 0) {
            divs[pos].push_back(primes[i]);
            v /= primes[i];
        }
        if (primes[i] * primes[i] > v) break;
    }
    if (v > 1) divs[pos].push_back(v);
    reverse(divs[pos].begin(), divs[pos].end());
}

int getLeast(int pos) {
    return divs[pos].empty() ? 1 : divs[pos].back();
}

int buildTree(int node, int l, int r) {
    int result;
    if (l == r) result = getLeast(l);
    else {
        int child = node * 2 + 1;
        int middle = (l + r) >> 1;
        result = max(buildTree(child, l, middle), buildTree(child + 1, middle + 1, r));
    }
    return tree[node] = result;
}

int getMax(int node, int l, int r, int start, int end) {
    if (start > r || end < l) return 0;
    if (l >= start && r <= end) return tree[node];
    int child = node * 2 + 1;
    int middle = (l + r) >> 1;
    return max(getMax(child, l, middle, start, end), getMax(child + 1, middle + 1, r, start, end));
}


int update(int node, int l, int r, int start, int end) {
    if (start > r || end < l) return 0;
    if (tree[node] == 1) return 1;
    int result;
    if (l == r) {
        divs[l].pop_back();
        result = tree[node] = getLeast(l);
    } else {
        int child = node * 2 + 1;
        int middle = (l + r) >> 1;
        result = max(update(child, l, middle, start, end), update(child + 1, middle + 1, r, start, end));
        tree[node] = max(tree[child], tree[child + 1]);
    }
    return result;
}


int main(void) {
    calcPrimes();
    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        FOR(i, n) calcDivs(i, getInt());
        buildTree(0, 0, n - 1);
        FOR(i, m) {
            int type = getInt();
            int l = getInt() - 1;
            int r = getInt() - 1;
            if (type == 0) {
                // update
                update(0, 0, n - 1, l, r);
            } else {
                // get
                print(getMax(0, 0, n - 1, l, r));
            }
        }
    }
}

