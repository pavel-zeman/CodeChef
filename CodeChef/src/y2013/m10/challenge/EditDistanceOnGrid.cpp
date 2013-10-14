//
// http://www.codechef.com/OCT13/problems/EDSTGRID
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

#define MAX_SIZE 110
#define BLACK 'B'

int n, m, c2, c3;
char board[MAX_SIZE][MAX_SIZE];

using namespace std;

struct operation {
    int type;
    int r1, c1;
    int r2, c2;
};

vector<operation> operations;

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {

        scanf("%d%d%d%d", &n, &m, &c2, &c3);

        FOR(i, n) scanf("%s", board[i]);

        operations.clear();

        bool first = true;
        FOR(i, n) FOR(j, m) {
            if (board[i][j] == BLACK) {
                if (first) first = false; else {
                    struct operation operation;
                    operation.type = 3;
                    operation.r1 = i + 1;
                    operation.c1 = j + 1;
                    operations.push_back(operation);
                }
            }
        }

        printf("%d\n", operations.size());
        FOR(i, (int)operations.size()) {
            printf("%d %d %d", operations[i].type, operations[i].r1, operations[i].c1);
            if (operations[i].type == 1) printf(" %d %d", operations[i].r2, operations[i].c2);
            printf("\n");
        }
    }
}
