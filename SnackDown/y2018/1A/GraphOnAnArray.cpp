// Check connectivity. If not connected, change a single number to a prime number, which is not used.
// https://www.codechef.com/SNCK1A19/problems/ARRGRAPH
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

#define PC (sizeof(primes) / sizeof(primes[0]))
#define MAX_N 64
int primes[] = {2, 3, 5, 7, 11, 13 ,	17 ,	19 ,	23 ,	29, 	31 ,	37, 	41 ,	43 , 47};
int primeCount[PC];
int a[MAX_N];
bool visited[MAX_N];
int n;


void visit(int node) {
    visited[node] = true;
    FOR(i, n) if (!visited[i] && gcd(a[i], a[node]) == 1) visit(i);
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        FOR(i, n) a[i] = getInt();
        FOR(i, n) visited[i] = false;
        FOR(i, PC) primeCount[i] = 0;
        FOR(i, n) FOR(j, PC) if (a[i] % primes[j] == 0) primeCount[j]++;
        visit(0);
        int totalVisited = 0;
        FOR(i, n) totalVisited += visited[i];
        bool ok = true;
        if (totalVisited != n) {
            ok = false;
            FOR(i, PC) if (primeCount[i] == 0) {
                a[0] = primes[i]; break;
            }
        }
        print(ok ? 0 : 1);
        FOR(i, n) printf("%d ", a[i]);
        printString("");
    }
}

