//
// http://www.codechef.com/COOK39/problems/PPLUCKY
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_S 100010
#define EMPTY '0'


int freq[MAX_S];
int tree[MAX_S];
int n;

int read(int idx){
	int sum = 0;
	while (idx > 0){
		sum += tree[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void update(int idx ,int val){
	while (idx <= n){
		tree[idx] += val;
		idx += (idx & -idx);
	}
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(tt, t) {
        char s[MAX_S];
        int iteration[MAX_S];
        scanf("%d%s", &n, s);

        int numSevens = 0;
        int currentIteration = 0;
        FOR(i, n + 2) freq[i] = 0, tree[i] = 0;
        for(int i=n-1;i>=0;i--) {
            iteration[i] = -1;
            if (s[i] == '7') {
                numSevens++;
                currentIteration = 0;
            } else {
                if (numSevens > 0) {
                    currentIteration++;
                    iteration[i] = currentIteration;
                    numSevens--;
                }
            }
        }
        long long int result = 0;
        FOR(i, n) {
            if (iteration[i] != -1) {
                if (iteration[i] > 1) {
                    result += i - 2 * read(iteration[i] - 1) + 1;
                } else {
                    result += i + 1;
                }
                freq[iteration[i]]++;
                update(iteration[i], freq[iteration[i]]);
            }
        }

        printf("%lld\n", result);
    }
}
