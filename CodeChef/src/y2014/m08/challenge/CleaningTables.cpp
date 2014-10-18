// When there is no free table, fire the customer, whose will sit for the longest time without order (for each sitting customer, maintain the position of his next order in a sorted map)
// http://www.codechef.com/AUG14/problems/CLETAB
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

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 202
#define MAX_C 402
#define MAX_M 402

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
        int n = getInt();
        int m = getInt();
        bool sitting[MAX_C];
        int freeTables = n;
        int orders[MAX_M];
        vector<int> customerOrders[MAX_C];
        int customerOrderPosition[MAX_C];
        map<int, int> positionCustomer;

        FOR(i, MAX_C) sitting[i] = false, customerOrderPosition[i] = 0;

        FOR(i, m) {
            int temp = getInt() - 1;
            orders[i] = temp;
            customerOrders[temp].push_back(i);
        }
        FOR(i, MAX_C) customerOrders[i].push_back(m + i); // add virtual last order

        int total = 0;
        FOR(i, m) {
            int c = orders[i];
            if (!sitting[c]) {
                if (freeTables > 0) {
                    freeTables--;
                } else {
                    // find suitable customer to fire (the one with the latest order)
                    map<int, int>::iterator it = positionCustomer.end();
                    it--;
                    int toFire = it->second;
                    sitting[toFire] = false;
                    positionCustomer.erase(customerOrders[toFire][customerOrderPosition[toFire]]);
                }
                sitting[c] = true;
                total++;
            }
            int nextPos = ++customerOrderPosition[c];
            positionCustomer.insert(pair<int, int>(customerOrders[c][nextPos], c));
        }
        printf("%d\n", total);
    }
}
