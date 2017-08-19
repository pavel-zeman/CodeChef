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

#define MAX_C 500010
#define MAX_Q 100010

struct Cpu {
    int x, y, p;
    int s, c;
} cpus[MAX_C];
int totalCpus;
vector<int> add[MAX_Q];


struct SetItem {
    int cpu;

    SetItem(int cpu) {
        this->cpu = cpu;
    }

    bool operator<(const SetItem & other) const {
        return cpus[this->cpu].p < cpus[other.cpu].p ||
            (cpus[this->cpu].p == cpus[other.cpu].p && (
                cpus[this->cpu].s < cpus[other.cpu].s ||
                (cpus[this->cpu].s == cpus[other.cpu].s && cpus[this->cpu].c < cpus[other.cpu].c)
            ));
    }
};

//set<pair<int, pair<int, int>>
set<SetItem> items;

double sqr(int x) {
    return (double)x * x;
}

int main(void) {
    int tries = 400;
    int n = getInt();
    int q = getInt();
    FOR(i, n) {
        int x = getInt();
        int y = getInt();
        int k = getInt();
        FOR(j, k) {
            cpus[totalCpus].x = x;
            cpus[totalCpus].y = y;
            cpus[totalCpus].p = getInt();
            cpus[totalCpus].s = i + 1;
            cpus[totalCpus].c = j + 1;
            items.insert(SetItem(totalCpus));
            totalCpus++;
        }
    }
    FOR(i, q) {
        for(auto it = add[i].begin(); it != add[i].end(); it++) items.insert(SetItem(*it));
        printf("?\n");
        fflush(stdout);
        int x = getInt();
        int y = getInt();
        set<SetItem>::iterator bestCc;
        double minDist = 10000000;
        int cc;
        int j = 0;
        for(auto top = items.begin(); top != items.end() && j < tries; top++, j++) {
            int cc = top->cpu;
            double dist = sqrt(sqr(x - cpus[cc].x) + sqrt(sqr(y - cpus[cc].y))) + cpus[cc].p;
            if (dist < minDist) {
                minDist = dist;
                bestCc = top;
            }
        }
        cc = bestCc->cpu;
        items.erase(bestCc);
        printf("! %d %d\n", cpus[cc].s, cpus[cc].c);
        int nextPos = i + cpus[cc].p;
        if (nextPos < q) add[nextPos].push_back(cc);

    }
    printf("end\n");
    fflush(stdout);
}

