// Assume, that the sum of each triple is the total sum / N. Then use O(N^2) algorithm to find as many such triples as time permits.
// https://www.codechef.com/JAN16/problems/CHMKTRPS
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

void fail() {
    *((char *)0) = 0;
}

#define MAX_N 300010
#define MAX_ITERATIONS 100000
struct Item {
    int pos;
    int value;

    bool operator<(const Item &other) const {
        return this->value < other.value;
    }

    bool operator<(int value) const {
        return this->value < value;
    }

};

Item a[MAX_N];
int b[MAX_N];
bool used[MAX_N];
int n;

map<long long int, set<pair<int, pair<int, int> > > > m;

vector<pair<int, pair<int, int> > > res;

int getNextRand() {
    return rand() % n;
}

int main(void) {
    clock_t startTime = clock();
    n = getInt() * 3;
    LLI sum = 0;
    FOR(i, n) {
        sum += a[i].value = getSignedInt();
        a[i].pos = i + 1;
    }
    sort(a, a + n);
    FOR(i, n) b[i] = a[i].value;
    sum /= n / 3;
    res.reserve(n / 3);
    //printf("Taget: %lld\n ", sum);
    FOR(i, n) {
        if (!used[i]) {
            used[i] = true;
            int remain = sum - b[i];
            int m = lower_bound(b + i + 1, b + n, remain >> 1) - b;
            int x = m - 1;
            if (x < i + 1) x = i + 1;
            int y = m;
            if (y >= n) y = n - 1;

            while (used[x] && x > i) x--;
            while (used[y] && y < n) y++;
            int iters = 0;
            while (x > i && y < n) {
                int s = b[x] + b[y];
                //printf("S: %d, remain: %d, a[i].pos = %d, x: %d, y: %d\n", s, remain, a[i].pos, x, y);
                if (s == remain) break;
                if (s < remain) {
                    y++;
                    while (used[y] && y < n) y++;
                } else {
                    x--;
                    while (used[x] && x > i) x--;
                }
                iters++;
            }
            //printf("%d\n", iters / 10000);
            if (x > i && y < n && b[x] + b[y] == remain && !used[x] && !used[y]) {
                if (used[x] || used[y]) fail();
                if (x <= i || x >= n || y <=i || y >= n) fail();
                used[x] = used[y] = true;
                res.push_back(make_pair(a[i].pos, make_pair(a[x].pos, a[y].pos)));
                if ((LLI)b[i] + b[x] + b[y] != sum) {
                    printf("Error, required: %lld, remain: %d, got %d\n", sum, remain, a[i].value + a[x].value + a[y].value);
                    //fail();
                }

            } else {
                used[i] = false;
                //printf("Fail\n");
            }
        }
        if (clock() - startTime > 4.9 * CLOCKS_PER_SEC) {
            //printf("%d\n", i);
            break;
        }
    }


    printf("%d\n", res.size());
    for(vector<pair<int, pair<int, int> > >::iterator it = res.begin(); it != res.end(); it++)
        printf("%d %d %d ", it->first, it->second.first, it->second.second);
}

