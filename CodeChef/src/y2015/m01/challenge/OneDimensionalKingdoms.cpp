// Hungry algorithm - sort kingdoms by R and simply go through the sorted list
// http://www.codechef.com/JAN15/problems/ONEKING
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


struct Kingdom {
    int l, r;

    Kingdom(int l, int r) {
        this->l = l;
        this->r = r;
    }

    bool operator<(const Kingdom &other) const {
        return this->r < other.r || this->r == other.r && this->l < other.l;
    }
};


vector<Kingdom> kingdoms;

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


int main(void) {
    int t = getInt();
    FOR(tt, t) {
        kingdoms.clear();
        int n = getInt();
        FOR(i, n) {
            int a = getInt();
            int b = getInt();
            kingdoms.push_back(Kingdom(a, b));
        }
        sort(kingdoms.begin(), kingdoms.end());
        int lastBombPosition = -1;
        int totalBombs = 0;
        for(vector<Kingdom>::iterator it = kingdoms.begin(); it != kingdoms.end(); it++) {
            if (it->l > lastBombPosition) {
                lastBombPosition = it->r;
                totalBombs++;
            }
        }
        printf("%d\n", totalBombs);
    }
}
