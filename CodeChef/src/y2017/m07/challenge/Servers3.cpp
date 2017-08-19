// Description
// https://www.codechef.com/JULY17/problems/SRVRS
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

#define MAX_S 100010
#define MAX_Q 100010
#define EMPTY 1000000000

struct Cpu {
    int s;
    int c;
    int p;

    Cpu(int s, int c, int p) {
        this->s = s;
        this->c = c;
        this->p = p;
    }
};

struct Server {
    int x, y;
    int minp;
    set<pair<int, int>> cpus;

    void addCpu(int c, int p) {
        if (p < minp) minp = p;
        cpus.insert(make_pair(p, c));
    }

    void removeCpu() {
        cpus.erase(cpus.begin());
        minp = cpus.empty() ? EMPTY : cpus.begin()->first;
    }
} servers[MAX_S];
vector<Cpu> add[MAX_Q];


struct SetItem {
    int server;

    SetItem(int server) {
        this->server = server;
    }

    bool operator<(const SetItem & other) const {
        return servers[this->server].minp < servers[other.server].minp ||
            (servers[this->server].minp == servers[other.server].minp && this->server < other.server);
    }
};

set<SetItem> items;

double sqr(int x) {
    return (double)x * x;
}

int main(void) {
    //int tries = 300;
    int n = getInt();
    int q = getInt();
    FOR(i, n) {
        servers[i].x = getInt();
        servers[i].y = getInt();
        servers[i].minp = EMPTY;
        int k = getInt();
        FOR(j, k) servers[i].addCpu(j, getInt());
        if (k > 0) items.insert(SetItem(i));
    }
    //int tries = 330 * 100000 / q;
    int tries = 1000;
    double total = 0;

    FOR(i, q) {
        for(auto it = add[i].begin(); it != add[i].end(); it++) {
            if (it->p < servers[it->s].minp) {
                items.erase(SetItem(it->s));
                servers[it->s].addCpu(it->c, it->p);
                items.insert(SetItem(it->s));
            } else servers[it->s].addCpu(it->c, it->p);
        }
        printf("?\n");
        fflush(stdout);
        int x = getInt();
        int y = getInt();
        int bestServer = -1;
        set<SetItem>::iterator bestIt;
        double minDist = 10000000;
        int j = 0;
        for(auto top = items.begin(); top != items.end() && j < tries; top++, j++) {
            int ss = top->server;
            if (servers[ss].minp >= minDist) break;
            double dist = sqrt(sqr(x - servers[ss].x) + sqrt(sqr(y - servers[ss].y))) + servers[ss].minp;
            if (dist < minDist) {
                minDist = dist;
                bestServer = ss;
                bestIt = top;
            }
        }
        items.erase(bestIt);
        auto bestCpu = servers[bestServer].cpus.begin();
        printf("! %d %d\n", bestServer + 1, bestCpu->second + 1);
        int nextPos = i + bestCpu->first;
        if (nextPos < q) add[nextPos].push_back(Cpu(bestServer, bestCpu->second, bestCpu->first));
        servers[bestServer].removeCpu();
        items.insert(SetItem(bestServer));
        total += minDist;

    }
    printf("end\n");
    fflush(stdout);
    printf("%lf\n", total);
}

