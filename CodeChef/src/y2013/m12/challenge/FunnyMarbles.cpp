// Fenwick tree
// http://www.codechef.com/DEC13/problems/MARBLEGF
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_N 1000020

long long int tree[MAX_N];

int n;

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

char getChar() {
    while (!isalpha(c)) c = getc_unlocked(stdin);
    return c;
}

long long int read(int idx){
	long long int sum = 0;
	while (idx > 0){
		sum += tree[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void update(int idx , int val){
	while (idx <= n){
		tree[idx] += val;
		idx += (idx & -idx);
	}
}

int main(void) {
    n = getInt();
    int q = getInt();
    FOR(i, n + 1) tree[i] = 0;
    FOR(i, n) update(i + 1, getInt());
    FOR(i, q) {
        char action = getChar();
        int a = getInt();
        int b = getInt();
        switch (action) {
            case 'S': {
                long long int sum = read(b + 1);
                if (a > 0) sum -= read(a);
                printf("%lld\n", sum);
                break;
            }
            case 'G':
                update(a + 1, b);
                break;
            case 'T':
                update(a + 1, -b);
                break;
        }
    }
}
