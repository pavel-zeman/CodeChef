#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <utility>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXN 100100
#define END -1

using namespace std;

int n, m;

int skill[MAXN];
int totalSkill[MAXN];
int superior[MAXN];
vector<int> children2[MAXN], children[MAXN];

bool correctTotal[MAXN];
bool hasParent[MAXN];


int calculateTotal(int node) {
    if (correctTotal[node]) return totalSkill[node];

    int total = skill[node];
    for(vector<int>::const_iterator ii = children[node].begin();ii != children[node].end();ii++) {
        total += calculateTotal(*ii);
    }
    correctTotal[node] = true;
    return totalSkill[node] = total;
}

void generateTree(int node) {
    for(vector<int>::const_iterator ii = children2[node].begin();ii != children2[node].end();ii++) {
        if (!hasParent[*ii]) {
            children[node].push_back(*ii);
            superior[*ii] = node;
            hasParent[*ii] = true;
            generateTree(*ii);
        }
    }
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

char getChar() {
    while (c < 'A' || c > 'Z') c = getc_unlocked(stdin);
    return c;
}

int main(void) {
    n = getInt();
    m = getInt();
    superior[0] = END;
    FOR(i, n) skill[i] = getInt();
    FOR(i, n) superior[i] = -1;

    vector<pair<int,int> > pairs;

    FOR(i, n - 1) {
        int sup = getInt(), inf = getInt();;

        /*superior[inf - 1] = sup - 1;*/
        children2[sup - 1].push_back(inf - 1);
        children2[inf - 1].push_back(sup - 1);
    }
    FOR(i, n) hasParent[i] = false;
    hasParent[0] = true;
    generateTree(0);



    FOR(i, n) correctTotal[i] = false;


    FOR(i, m) {
        char operation = getChar();
        int soldier = getInt();
        if (operation == 'Q') {
            printf("%d\n", calculateTotal(soldier - 1));
        } else {
            int value = getInt();

            int pos = soldier - 1;
            if (correctTotal[pos]) totalSkill[pos] += value - skill[pos];
            skill[pos] = value;

            if (correctTotal[pos]) pos = superior[pos];
            while (pos != END) {
                if (!correctTotal[pos]) break;
                correctTotal[pos] = false;
                pos = superior[pos];
            }
        }
    }
}

