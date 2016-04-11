// Dynamic programming for small input. If there are no carrots, the result is comb(M+N-3, M-1) * comb(M+N-3, M-2) / (M+N-3).
// https://www.codechef.com/APRIL16/problems/CHNBGMT
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

int power(int a, int b, int mod) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % mod;
        sq = sq * (LLI)sq % mod;
        b >>= 1;
    }
    return result;
}

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 61
#define MAX_N2 200010
// x, y of the first bunny, x of the second bunny, carrots
int ways[MAX_N][MAX_N][MAX_N][MAX_N];
int mod, n, m;
int carrot[MAX_N][MAX_N];
bool isPrime[MAX_N2];
vector<int> primes;
vector<pair<int, int> > factorization[MAX_N2];
int primeCount;
int primePos[MAX_N2];
int powers[100000];

int solve(int x, int y, int otherX, int c) {
    if (x < 0 || y < 0 || otherX < 0) return 0;
    int result = ways[x][y][otherX][c];
    if (result < 0) {
        result = 0;
        if (x < otherX || x == n - 1 && otherX == n - 1) {
            int otherY = x + y - otherX;
            int newC = c - carrot[x][y] - carrot[otherX][otherY];
            if (c >= 0) {
                result = (result + solve(x - 1, y, otherX - 1, newC)) % mod;
                result = (result + solve(x - 1, y, otherX, newC)) % mod;
                result = (result + solve(x, y - 1, otherX - 1, newC)) % mod;
                result = (result + solve(x, y - 1, otherX, newC)) % mod;
            }
        }
        ways[x][y][otherX][c] = result;
        //printf("Setting %d %d %d %d to %d\n", x, y, otherX, c, result);
    }
    return result;
}

void addFactor(int i, int mul) {
    FOR(j, factorization[i].size())
        powers[factorization[i][j].first] += factorization[i][j].second * mul;
}

int main(void) {
    FOR(i, MAX_N2) isPrime[i] = true;
    isPrime[0] = isPrime[1] = false;
    FORE(i, 2, MAX_N2) {
        if (isPrime[i]) for(int j = i + i; j < MAX_N2; j += i) isPrime[j] = false;
    }
    FOR(i, MAX_N2) if (isPrime[i]) {
        primePos[i] = primes.size();
        primes.push_back(i);
    }
    primeCount = primes.size();
    FORE(i, 2, MAX_N2) {
        int temp = i;
        FOR(j, primeCount) {
            if (primes[j] * primes[j] > temp) break;
            if (temp % primes[j] == 0) {
                int c = 0;
                while (temp % primes[j] == 0) {
                    temp /= primes[j];
                    c++;
                }
                factorization[i].push_back(make_pair(j, c));
            }
        }
        if (temp > 1) factorization[i].push_back(make_pair(primePos[temp], 1));
    }


    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();
        int c = getInt();
        int d = getInt();
        mod = getInt();
        int result = 0;
        if (c == 0) {
            if (m == 1 || n == 1) result = 0; else {
                FOR(i, primeCount) powers[i] = 0;
                FORE(i, m, m + n - 2) addFactor(i, 2);
                FORE(i, 2, n) addFactor(i, -2);
                addFactor(n - 1, 1);
                addFactor(m - 1, 1);
                addFactor(n + m - 3, -1);

                result = 1 % mod;
                FOR(i, primeCount)
                    result = result * (LLI)power(primes[i], powers[i], mod) % mod;
            }
        } else {
            if (n < MAX_N && m < MAX_N) {
                FOR(i, n) FOR(j, m) carrot[i][j] = 0;
                FOR(i, n) FOR(j, m) FOR(k, n) FOR(l, d + 1) ways[i][j][k][l] = -1;
                FOR(i, n) FOR(j, m) FOR(l, d + 1) ways[i][j][i][l] = 0;
                FOR(i, d + 1) ways[0][0][0][i] = 1;
                FOR(i, d + 1) ways[n - 1][m - 1][n - 1][i] = -1;
                FOR(i, c) {
                    int x = getInt() - 1;
                    int y = getInt() - 1;
                    carrot[x][y] = 1;
                }
                result = solve(n - 1, m - 1, n - 1, d);
            } else
                fail();
        }
        print(result);
    }
}
