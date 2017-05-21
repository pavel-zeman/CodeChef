// The result is comb(ceil(n/k) * k - n + ceil(n/k) - 1, ceil(n/k) - 1) % m. To calculate the binomial coefficient, Graneville's theorem with CRT (Chinese remainder theorem) are used.
// https://www.codechef.com/MAY17/problems/SANDWICH
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(int)(t);c++)
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

#define MAX_P 1000010
bool isPrime[MAX_P];
int primes[100000];
int totalPrimes;

struct Power {
    int p;
    int q;
    int pq;
};


int fact[MAX_P];
int maxFact;

void initFact() {
    fact[0] = fact[1] = 1;
    maxFact = 1;
}

int getFact(int n, int p, int pq) {
    if (n > maxFact) {
        FORE(i, maxFact + 1, n + 1) {
            fact[i] = fact[i - 1];
            if (i % p != 0) fact[i] = (fact[i] * (LLI)i) % pq;
        }
        maxFact = n;
    }
    return fact[n];
}

vector<int> getSmall(LLI v, int p) {
    vector<int> res;
    while (v > 0) {
        res.push_back(v % p);
        v /= p;
    }
    return res;
}

vector<int> getBig(vector<int> & small, int p, int q, int pq) {
    vector<int> res;
    FOR(i, small.size()) {
        int t = 0;
        int pp = 1;
        for(int j = 0; j < q && j + i < (int)small.size(); j++) {
            t += small[i + j] * pp;
            pp *= p;
        }
        res.push_back(t);
    }
    return res;
}

pair<int, int> extendedGcd(int a, int b) {
    int s = 0, olds = 1;
    int t = 1, oldt = 0;
    int r = b, oldr = a;
    while (r != 0) {
        int q = oldr / r;
        int tt = r;
        r = oldr - q * r;
        oldr = tt;

        tt = s;
        s = olds - q * s;
        olds = tt;

        tt = t;
        t = oldt - q * t;
        oldt = tt;
    }
    return make_pair(olds, oldt);
}


int getCombMod(LLI n, LLI k, Power power) {
    vector<int> ns = getSmall(n, power.p);
    vector<int> nb = getBig(ns, power.p, power.q, power.pq);
    vector<int> ks = getSmall(k, power.p);
    while (ks.size() < ns.size()) ks.push_back(0);
    vector<int> kb = getBig(ks, power.p, power.q, power.pq);
    vector<int> rs = getSmall(n - k, power.p);
    while (rs.size() < ns.size()) rs.push_back(0);
    vector<int> rb = getBig(rs, power.p, power.q, power.pq);
    vector<int> e;
    FOR(i, ns.size()) {
        int r = 0;
        FORE(j, i, ns.size()) if (ks[j] + rs[j] > ns[j]) r++;
        e.push_back(r);
    }
    int r = 1;
    initFact();
    FOR(i, ns.size()) {
        r = (r * (LLI)getFact(nb[i], power.p, power.pq)) % power.pq;
        int kf = getFact(kb[i], power.p, power.pq);
        kf = (kf * (LLI)getFact(rb[i], power.p, power.pq)) % power.pq;
        int inv = (extendedGcd(kf, power.pq).first + power.pq) % power.pq;
        r = (r * (LLI)inv) % power.pq;
    }
    if (power.q - 1 < (int)e.size()) {
        int plusMinusOne = power.p == 2 && power.q >= 3 ? 1 : -1;
        if (plusMinusOne < 0 && (e[power.q - 1] & 1) == 1) r = (power.pq - r) % power.pq;
    }
    FOR(i, e[0]) r = (r * (LLI)power.p) % power.pq;
    return r;
}

// Implementation of Granville's theorem
int getComb(LLI n, LLI k, int m) {
    if (k == 0) return 1;
    int morig = m;
    vector<Power> powers;
    vector<int> a;
    FOR(i, totalPrimes) {
        int q = 0;
        while (m % primes[i] == 0) {
            q++;
            m /= primes[i];
        }
        if (q > 0) {
            Power pp;
            pp.p = primes[i];
            pp.q = q;
            pp.pq = 1;
            FOR(i, q) pp.pq *= pp.p;
            powers.push_back(pp);
            if (m == 1) break;
        }
    }
    FOR(i, powers.size()) a.push_back(getCombMod(n, k, powers[i]));
    vector<int> M;
    FOR(i, powers.size()) M.push_back(morig / powers[i].pq);
    int r = 0;
    FOR(i, powers.size())
        r = (r + a[i] * (LLI)(extendedGcd(powers[i].pq, M[i]).second + morig) % morig * (LLI)M[i]) % morig;
    return r;
}

int main(void) {
    FOR(i, MAX_P) isPrime[i] = true;
    FORE(i, 2, MAX_P) {
        if (isPrime[i]) {
            primes[totalPrimes++] = i;
            for(int j = i + i; j < MAX_P; j += i) isPrime[j] = false;
        }
    }

    int t = getInt();
    FOR(tt, t) {
        LLI n = getLongLongInt();
        LLI k = getLongLongInt();
        int m = getInt();
        LLI parts = (n + k - 1) / k;
        LLI remain = parts * k - n;
        int ways = getComb(remain + parts - 1, parts - 1, m);
        print(parts);
        print(ways);
    }
}

