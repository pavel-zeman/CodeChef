// Simple min-max search with branch pruning (the same algorithm is used for both MAX and RANDOM approaches, because it seems to work better).
// http://www.codechef.com/JULY15/problems/MAXDIFFW
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

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

void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}

#define MAX_N 50
int n;
bool visited[MAX_N][MAX_N];
int cost[MAX_N][MAX_N];
map<int, int> costMap[MAX_N];

struct Move {
    int index;
    int cost;

    Move(int index, int cost) {
        this->index = index;
        this->cost = cost;
    }
};

Move getMaxNext(int current) {
    for(map<int,int>::reverse_iterator it=costMap[current].rbegin(); it != costMap[current].rend(); it++) {
        if (!visited[current][it->second]) {
            return Move(it->second, it->first);
        }
    }
    return Move(-1, 0);
}

Move getMyNext(int current, int level) {
    if (level == 0) return Move(current, 0);

    int maxTotalCost = -MAX_N * MAX_N * 100;
    int maxIndex = -1;
    for (map<int, int>::reverse_iterator it = costMap[current].rbegin(); it != costMap[current].rend(); it++) {
        int i = it->second;
        if (!visited[current][i]) {
            Move opponentMove = getMaxNext(i);
            if (opponentMove.index >= 0) {
                int temp = cost[current][i] - opponentMove.cost;
                if (temp > maxTotalCost - (level - 1) * 400) {
                    visited[current][i] = true;
                    visited[i][opponentMove.index] = true;

                    temp += getMyNext(opponentMove.index, level - 1).cost;

                    visited[current][i] = false;
                    visited[i][opponentMove.index] = false;
                    if (temp > maxTotalCost) {
                        maxTotalCost = temp;
                        maxIndex = i;
                    }
                }
            } else {
                int temp = cost[current][i];
                if (temp > maxTotalCost) {
                    maxTotalCost = temp;
                    maxIndex = i;
                }
            }
        }
    }
    if (maxIndex < 0) maxTotalCost = 0;
    return Move(maxIndex, maxTotalCost);

}

int getMyNextRandom(int current) {
    int maxTotalCost = -MAX_N * MAX_N * 100;
    int maxIndex = -1;
    FOR(i, n) if (!visited[current][i]) {
        int temp = cost[current][i];
        int sum = 0;
        int count = 0;
        visited[current][i] = true;
        FOR(j, n) if (!visited[i][j]) {
            sum += -cost[i][j] + getMaxNext(j).cost;
            count++;
        }
        visited[current][i] = false;
        if (count > 0) sum /= count;
        temp += sum;
        if (temp > maxTotalCost) {
            maxTotalCost = temp;
            maxIndex = i;
        }
    }
    return maxIndex;
}


int main(void) {
    n = getInt();
    FOR(i, n) FOR(j, n) {
        cost[i][j] = getInt();
        if (cost[i][j] != 0) costMap[i][cost[i][j]] = j;
    }
    FOR(i, n) visited[i][i] = true;
    int node = 0;
    int total = 0;
    bool random = false;
    while (true) {
        int next = random ? getMyNextRandom(node) : getMyNext(node, 4).index;
        if (next < 0) break;
        total += cost[node][next];
        print(node + 1);
        print(next + 1);
        fflush(stdout);
        visited[node][next] = true;
        costMap[node].erase(cost[node][next]);
        node = next;
        if (getMaxNext(node).index < 0) break;
        getInt();
        next = getInt() - 1;
        //next = getMaxNext(node).index;
        //next = costMap[node].begin()->second;
        //if (next != getMaxNext(node).index) random = true;

        costMap[node].erase(cost[node][next]);
        total -= cost[node][next];
        visited[node][next] = true;
        node = next;
    }
    //print(total);
}

