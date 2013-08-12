// DFS getting counts of vertices for each distance from current vertex (root)
// http://www.codechef.com/AUG13/problems/PRIMEDST
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <list>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 50100
#define MAX_NEIGHBORS (2 * MAX_N)


using namespace std;

bool prime[MAX_N];
int numPrimes[MAX_N];
list<int> neighbors[MAX_N];
int neighborsCount[MAX_N];

int total = 0;


struct CustomList {
    int *data;
    int capacity;
    int used;

    CustomList() {
        data = new int[capacity = 8];
        data[0] = 0;
        used = 0;
    }

    ~CustomList() {
        delete [] data;
    }

    void allocate(int size) {
        if (size > capacity) {
            while (capacity < size) capacity <<= 1;

            int *newData = new int[capacity];
            memcpy(newData, data, sizeof(int) * used);
            delete [] data;
            data = newData;
            data[0] = 0;
        }
    }

    void shift(int increment) {
        allocate(used + increment);
        memmove(data + increment, data, sizeof(int) * used);
        used += increment;
    }
};


char c = 0;
int getInt() {
    int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}


void calc(int vertex, int previous, CustomList &result) {
    if (vertex != 0 && neighborsCount[vertex] == 1) {
        result.data[0] = 0;
        result.data[1] = 1;
        result.used = 2;
        return;
    }
    if (vertex != 0 && neighborsCount[vertex] == 2) {
        int vertices = 1;
        while (neighborsCount[vertex] == 2) {
            list<int>::iterator it = neighbors[vertex].begin();
            if (*it == previous) it++;
            previous = vertex;
            vertex = *it;
            vertices++;
        }

        if (neighborsCount[vertex] == 1) {
            total += numPrimes[vertices - 1];
            result.data[0] = 0;
            result.allocate(vertices + 1);
            FOR(i, vertices)
                result.data[i + 1] = 1;
            result.used = vertices + 1;
            return;
        } else {
            total += numPrimes[vertices - 2];

            calc(vertex, previous, result);
            FORE(j, 1, result.used) {
                FOR(i, vertices - 1) {
                    if (prime[j + i]) total += result.data[j];
                }
            }

            result.shift(vertices - 1);
            FOR(i, vertices - 1) result.data[i + 1] = 1;
            return;
        }
    }

    CustomList siblings;
    for(list<int>::iterator it = neighbors[vertex].begin(); it != neighbors[vertex].end(); it++) {
        if (*it != previous) {
            CustomList temp;
            calc(*it, vertex, temp);
            FORE(i, 1, siblings.used)
                FORE(j, 1, temp.used)
                    if (prime[i + j]) total += siblings.data[i] * temp.data[j];

            if (siblings.used >= temp.used) {
                FOR(i, temp.used) siblings.data[i] += temp.data[i];
            } else {
                siblings.allocate(temp.used);
                FOR(i, siblings.used) siblings.data[i] += temp.data[i];
                FORE(i, siblings.used, temp.used) siblings.data[i] = temp.data[i];
                siblings.used = temp.used;
            }
        }
    }

    result.allocate(siblings.used + 1);
    result.used = siblings.used + 1;
    memcpy(result.data + 1, siblings.data, sizeof(int) * siblings.used);
    FORE(i, 2, siblings.used) {
        if (prime[i]) total += siblings.data[i];
    }
    result.data[1] = 1;
}

int main(void) {
    int n = getInt();

    // sieve of Erastothenes
    FOR(i, n) prime[i] = true;
    prime[1] = false;
    FORE(i, 2, n) {
        if (prime[i]) {
            for(int j=i+i;j<n;j+=i) prime[j] = false;
        }
    }
    numPrimes[0] = numPrimes[1] = 0;
    FORE(i, 2, n) numPrimes[i] = numPrimes[i - 1] + (prime[i] ? 1 : 0);
    FORE(i, 1, n) numPrimes[i] += numPrimes[i - 1];

    FOR(i, n - 1) {
        int a = getInt() - 1;
        int b = getInt() - 1;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }

    FOR(i, n) neighborsCount[i] = neighbors[i].size();

    CustomList distances;
    calc(0, 0, distances);

    printf("%.10lf", (double)total / n / (n - 1) * 2);
}
