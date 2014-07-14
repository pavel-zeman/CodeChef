// Sort the frogs by their X position and then go through them one by one increasing "group number", if the distance of the neighbors is greater than K
// http://www.codechef.com/JULY14/problems/FROGV
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <algorithm>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010

struct Frog {
    int x;
    int position;

    bool operator<(const Frog &b) const {
        return x < b.x || (x == b.x && position < b.position);
    }
} frogs[MAX_N];

int group[MAX_N];

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
    int n = getInt();
    int k = getInt();
    int p = getInt();
    FOR(i, n) {
        frogs[i].x = getInt();
        frogs[i].position = i;
    }
    sort(frogs, frogs + n);
    int lastGroup = 0;
    int lastX = 0;
    FOR(i, n) {
        if (frogs[i].x - lastX > k) lastGroup++;
        lastX = frogs[i].x;
        group[frogs[i].position] = lastGroup;
    }
    FOR(i, p) {
        int a = getInt() - 1, b = getInt() - 1;
        printf("%s\n", group[a] == group[b] ? "Yes" : "No");
    }
}
