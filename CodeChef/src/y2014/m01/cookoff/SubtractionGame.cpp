// Nim and Sprague-Grundy theorem
// http://www.codechef.com/COOK42/problems/GAMEAAM
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


using namespace std;

#define MAX_N 110

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
        int result = 0;
        FOR(i, n) {
            int a = getInt();
            int b = getInt();
            vector<int> v;

            if (a < b) {
                int temp = a;
                a = b;
                b = temp;
            }
            while (a > b) {
                int d = a % b == 0 ? a / b - 1 : a / b ;
                a -= d * b;
                int temp = a;
                a = b;
                b = temp;
                v.push_back(d);
            }

            int g = v.back();
            v.pop_back();
            while (!v.empty()) {
                int ng;
                if (g == 0) {
                    ng = v.back();
                } else {
                    ng = v.back() - 1;
                    if (ng >= g) ng++;
                }
                g = ng;
                v.pop_back();
            }
            result ^= g;
        }
        printf("%s\n", result == 0 ? "NO" : "YES");
    }
}

