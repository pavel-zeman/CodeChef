#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MOD 1000000007
#define MAXITEMS 1000



long long power(long long a, long long count, long long mod) {
    long long result = 1;
    long long power = a % mod;
    while (count > 0) {
        if (count & 1) result = (result * power) % mod;
        count >>= 1;
        power = (power * power) % mod;
    }
    return result;
}

char c = 0;
int getInt() {
    int r = 0;
    while (c < '0' || c > '9') c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

long long getLong() {
    long long r = 0;
    while (c < '0' || c > '9') c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

int n;
int k;
bool used[100000];
int total;

int edges[100000][2];
int istatus[10000];

int totalRemaining;
int neighbors[1000];

/*void generate(int vertex, int remain, int minNeighbour) {
    //istatus[n * k - 1 - remain - 1] = vertex;
    if (remain == 0) {
        FOR(i, n * k - 1) printf("%d %d; ", edges[i][0], edges[i][1]);
        printf("\n");
        total++;
    } else {
        FORE(i, minNeighbour, n * k) {
            if (!used[i] && i / k != vertex / k) {
                used[i] = true;
                edges[k * n - 1 - remain][0] = vertex;
                edges[k * n - 1 - remain][1] = i;
                //printf("At %d %d and calling %d\n", vertex, remain, i);
                generate(i, remain - 1, 0);
                //printf("At %d %d and calling %d\n", vertex, remain, vertex);
                if (remain != 1) generate(vertex, remain - 1, i + 1);
                used[i] = false;
            }
        }
    }
}*/

int generateTree(int *neighbors, int totalNeighbors, int *remainingIndexes, int level) {
    if (level < totalNeighbors - 1) {
        int newRemainingIndexes[100];
        int pos = 0;
        while (pos < (1 << totalNeighbors)) {

        }
    } else {

    }
}

int generateNeighbors(int vertex, int minVertex, int level, int totalNeighbors) {
    if (level < totalNeighbors) {
        int total = 0;
        FORE(i, minVertex, n * k) {
            if (!used[i]) {
                used[i] = true;
                neighbors[level] = i;
                totalRemaining--;
                total += generateNeighbors(vertex, i + 1, level + 1, totalNeighbors);
                totalRemaining++;
                used[i] = false;
            }
        }
        return total;
    } else {
        int localNeighbors[1000];
        FOR(i, totalNeighbors) localNeighbors[i] = neighbors[i];
        int remainingIndexes[1000];
        int pos = 0;
        FOR(i, n * k) {
            if (!used[i]) remainingIndexes[pos++] = i;
        }
        return generateTree(localNeighbors, totalNeighbors, remainingIndexes, 0);
    }
}

int main(void) {
    n = getInt();
    k = getInt();
    total = 0;
    FOR(i, ((int)sizeof(used))) used[i] = false;
    used[0] = true;
    totalRemaining = n * k - 1;

    FORE(i, 1, totalRemaining) {
        total += generateNeighbors(0, 1, 0, i);
    }
    //generate(0, n * k - 1, 0);
    printf("%d\n", total);


/*    long long res = 0;
    if (n == 1) {
        res = k == 1 ? 1 : 0;
    } else {
        if (k == 1) {
            res = power(n, n - 2, MOD);
        } else {
            long long m = power(n, n - 2, MOD - 1);
            res = power(k * k, m, MOD);
        }
    }
    printf("%lld", res);*/
}
