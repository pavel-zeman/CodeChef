// Segment tree built on the array of chef healths (each node of the tree contains current minimum health, count of living chefs and amount of poison to distribute)
// http://www.codechef.com/SEPT13/problems/MLCHEF
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include <vector>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010

int n;
int chefHealthUsed = 0;

using namespace std;

struct chef {
    vector<int> inferiors;
    int from, to;
    int health;
    int superior;
} chefs[MAX_N];

int chefHealth[MAX_N];

struct segment {
    int from, to;
    int minHealth;
    int alive;
    int distribute;
} segments[MAX_N * 3];


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

int min(int a, int b) {
    return a < b ? a : b;
}

void buildChefTree(int chef) {
    chefHealth[chefHealthUsed++] = chefs[chef].health;
    int start = chefHealthUsed;
    for(vector<int>::iterator it = chefs[chef].inferiors.begin(); it != chefs[chef].inferiors.end(); it++) {
        buildChefTree(*it);
    }
    chefs[chef].from = start;
    chefs[chef].to = chefHealthUsed - 1;
}


void buildSegmentTree(int node, int a, int b) {
    segments[node].from = a;
    segments[node].to = b;
    segments[node].alive = b - a + 1;
    segments[node].distribute = 0;
    if (a == b) {
        segments[node].minHealth = chefHealth[a];
        segments[node].alive = 1;
    } else {
        int m = (a + b) >> 1;
        buildSegmentTree(node * 2 + 1, a, m);
        buildSegmentTree(node * 2 + 2, m + 1, b);
        segments[node].minHealth = min(segments[node * 2 + 1].minHealth, segments[node * 2 + 2].minHealth);
    }
}

int getAlive(int node, int a, int b) {
    if (a <= segments[node].from && b >= segments[node].to) {
        return segments[node].alive;
    } else if (a > segments[node].to || b < segments[node].from) {
        return 0;
    } else {
        return getAlive(node * 2 + 1, a, b) + getAlive(node * 2 + 2, a, b);
    }
}

void distribute(int node, int a, int b, int value) {
    // they are all dead
    if (segments[node].alive == 0) return;


    if (a <= segments[node].from && b >= segments[node].to) {
        // use the whole interval
        if (segments[node].minHealth > value) {
            segments[node].minHealth -= value;
            segments[node].distribute += value;
        } else {
            if (segments[node].from == segments[node].to) {
                segments[node].minHealth = INT_MAX;
                segments[node].alive = 0;
            } else {
                distribute(node * 2 + 1, a, b, segments[node].distribute + value);
                distribute(node * 2 + 2, a, b, segments[node].distribute + value);
                segments[node].minHealth = min(segments[node * 2 + 1].minHealth, segments[node * 2 + 2].minHealth);
                segments[node].alive = segments[node * 2 + 1].alive + segments[node * 2 + 2].alive;
                segments[node].distribute = 0;
            }
        }
    } else if (a > segments[node].to || b < segments[node].from) {
        return;
    } else {
        if (segments[node].distribute > 0) {
            distribute(node * 2 + 1, segments[node * 2 + 1].from, segments[node * 2 + 1].to, segments[node].distribute);
            distribute(node * 2 + 2, segments[node * 2 + 2].from, segments[node * 2 + 2].to, segments[node].distribute);
        }

        distribute(node * 2 + 1, a, b, value);
        distribute(node * 2 + 2, a, b, value);
        segments[node].minHealth = min(segments[node * 2 + 1].minHealth, segments[node * 2 + 2].minHealth);
        segments[node].alive = segments[node * 2 + 1].alive + segments[node * 2 + 2].alive;
        segments[node].distribute = 0;
    }
}


int main(void) {
    chefs[0].superior = -1;
    n = getInt();
    FOR(i, n) {
        chefs[i + 1].health = getInt();
        chefs[i + 1].superior = getInt();
        chefs[chefs[i + 1].superior].inferiors.push_back(i + 1);
    }
    buildChefTree(0);
    buildSegmentTree(0, 0, chefHealthUsed - 1);

    int q = getInt();
    FOR(i, q) {
        int type = getInt();
        int a = getInt();
        if (type == 1) {
            int x = getInt();
            distribute(0, chefs[a].from, chefs[a].to, x);
        } else {
            printf("%d\n", getAlive(0, chefs[a].from, chefs[a].to));
        }
    }
}
