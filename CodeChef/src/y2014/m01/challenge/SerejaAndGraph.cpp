// Ignore duplicate edges, use edges from all vertices of degree 1 and the rest must be cycles of even size - unfortunately this does not work, because a cycle does not guarantee existence of the solution
// http://www.codechef.com/JAN14/problems/SEAGRP
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 110

int n, m;

int degree[MAX_N];
bool neighbor[MAX_N][MAX_N];
bool processed[MAX_N];

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

int getNeighbor(int a) {
    FOR(i, n) if (neighbor[a][i]) return i;
    return -1;
}

void removeEdge(int a, int b) {
    neighbor[a][b] = neighbor[b][a] = false;
    degree[a]--;
    degree[b]--;
}

void addEdge(int a, int b) {
    if (!neighbor[a][b]) {
        neighbor[a][b] = neighbor[b][a] = true;
        degree[a]++;
        degree[b]++;
    }
}


int check(int v) {
    int result = 1;
    processed[v] = true;
    FOR(i, n)
        if (neighbor[v][i] && !processed[i]) {
            result += check(i);
        }
    return result;
}

bool solve() {
    if ((n & 1) == 1) return false;
    // use edges from vertices of degree 1
    bool found = true;
    while (found) {
        found = false;
        FOR(i, n) {
            if (degree[i] == 1 && !processed[i]) {
                found = true;
                int v = i;
                int v2 = getNeighbor(v);
                processed[v] = processed[v2] = true;
                FOR(j, n) {
                    if (j != v && neighbor[v2][j]) {
                        removeEdge(v2, j);
                    }
                }
            }
        }
    }

    FOR(i, n) if (degree[i] == 0) return false;

    // check cycles
    FOR(i, n)
        if (!processed[i]) {
            int vertices = check(i);
            if ((vertices & 1) == 1) return false;
            if (vertices >= 12) *((char *)0) = 0;
        }
    return true;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        n = getInt();
        m = getInt();
        FOR(i, n) degree[i] = 0, processed[i] = false;
        FOR(i, n) FOR(j, n) neighbor[i][j] = false;
        FOR(i, m) {
            int a = getInt() - 1, b = getInt() - 1;
            addEdge(a, b);
        }

        printf("%s\n", solve() ? "YES" : "NO");
    }
}

