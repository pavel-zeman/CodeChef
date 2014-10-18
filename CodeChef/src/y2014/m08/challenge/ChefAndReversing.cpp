// DFS all possible "forward" edges. Then check all possible "backward" egdes and repeat from beginning, until reaching the vertex N.
// http://www.codechef.com/AUG14/problems/REVERSE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 100010

int n, m;
bool visited[MAX_N];
vector<int> forward[MAX_N];
vector<int> back[MAX_N];

vector<int> queue1;
vector<int> queue2;

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

// forward visit
void visit1(int node) {
    queue2.push_back(node);
    visited[node] = true;

    FOR(i, (int)forward[node].size()) {
        int nextNode = forward[node][i];
        if (!visited[nextNode]) {
            visit1(nextNode);
        }
    }
}

// backward visit
void visit2(int node) {
    FOR(i, (int)back[node].size()) {
        int nextNode = back[node][i];
        if (!visited[nextNode]) {
            queue1.push_back(nextNode);
            visited[nextNode] = true;
        }
    }
}


int main(void) {
    n = getInt();
    m = getInt();
    FOR(i, m) {
        int a = getInt() - 1;
        int b = getInt() - 1;
        forward[a].push_back(b);
        back[b].push_back(a);
    }

    bool success = false;
    int steps = 0;
    queue1.push_back(0);
    visited[0] = true;

    while (true) {
        queue2.clear();
        FOR(i, (int)queue1.size()) visit1(queue1[i]);
        if (visited[n - 1]) {
            // found
            success = true;
            break;
        }

        queue1.clear();
        steps++;

        FOR(i, (int)queue2.size()) visit2(queue2[i]);
        if (visited[n - 1]) {
            // found
            success = true;
            break;
        }
        if (queue1.empty()) break; // no way
    }
    printf("%d\n", success ? steps : -1);

}
