// Use Floyd-Warshall to calculate the shortest distance between any 2 nodes and then always assign a job to the node with minimum power (while not exceeding the total network cost)
// https://www.codechef.com/JULY16/problems/CLUSSCHE
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

#define MAX_N 512
int cost[MAX_N][MAX_N];
int totalPower[MAX_N];

int main(void) {
    int n = getInt();
    int m = getInt();
    int b = getInt();
    int c = getInt();
    FOR(i, n) FOR(j, n) cost[i][j] = getInt();

    // Floyd - Warshall to get the lowest network cost
    FOR(k, n) FOR(i, n) FOR(j, n) if (cost[i][j] > cost[i][k] + cost[k][j]) cost[i][j] = cost[i][k] + cost[k][j];


    LLI score = 0;
    FOR(i, m) {
        pair<int, pair<int, int> > input[MAX_N];
        FOR(j, b) {
            int toRun = getInt();
            int power = getInt();
            input[j] = make_pair(-power, make_pair(toRun - 1, j));
        }
        sort(input, input + b);
        int resultNode[MAX_N];
        FOR(j, b) {
            int power = -input[j].first;
            int target = input[j].second.first;
            int order = input[j].second.second;
            int selected = -1;
            int mn = 1000000000;
            int minCost = 1000000000;
            FOR(k, n) {
                if (cost[target][k] <= c && (totalPower[k] < mn || (totalPower[k] == mn && cost[target][k] < minCost))) {
                    selected = k;
                    mn = totalPower[k];
                    minCost = cost[target][k];
                }
            }
            resultNode[order] = selected + 1;
            totalPower[selected] += power;
            c -= minCost;
        }
        FOR(j, b) print(resultNode[j]);

        int mn = totalPower[0];
        int mx = totalPower[0];
        FOR(j, n) {
            mn = min(totalPower[j], mn);
            mx = max(totalPower[j], mx);
        }
        //print(mx - mn);
        score += mx - mn;
        fflush(stdout);
    }
    print(score);
    print(c);
}

