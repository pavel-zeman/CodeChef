#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAXN 100010
#define MOD 3046201

int n;
int fact[MAXN * 30];
int inverse[MOD];
int bushes[MAXN];
int tree[MAXN];

void updateTree(int index, int value) {
	while (index <= n){
		tree[index] += value;
		index += (index & -index);
	}
}

int readSum(int index){
	int sum = 0;
	while (index > 0){
		sum += tree[index];
		index -= (index & -index);
	}
	return sum;
}

int power(int value, int power) {
    long long int temp = value;
    int result = 1;
    while (power > 0) {
        if ((power & 1) == 1) result = (result * temp) % MOD;
        power >>= 1;
        temp = (temp * temp) % MOD;
    }
    return (int)result;
}

int getInverse(int a) {
    if (inverse[a] != 0) return inverse[a];
    int b = power(a, MOD - 2);
    inverse[a] = b;
    inverse[b] = a;
    return b;
}

int comb(int n, int k) {
    long long nf = fact[n];
    long long nk = getInverse(fact[k]);
    long long nk2 = getInverse(fact[n - k]);
    return (int)((((nf * nk) % MOD) * nk2) % MOD);
}

int multiComb(int n, int v, int items1, int items2) {
    long long nf = fact[n];
    long long nv1 = getInverse(power(fact[v], items1));
    long long nv2 = getInverse(power(fact[v + 1], items2));
    return (int)((((nf * nv1) % MOD) * nv2) % MOD);
}


int main(void) {
    memset(tree, 0, sizeof(tree));
    memset(inverse, 0, sizeof(inverse));

    fact[0] = 1;
    FORE(i, 1, sizeof(fact) / sizeof(fact[0])) fact[i] = (((long long)fact[i - 1]) * i) % MOD;

    scanf("%d", &n);
    FOR(i, n) {
        scanf("%d", &bushes[i + 1]);
        updateTree(i + 1, bushes[i + 1]);
    }

    int q;
    scanf("%d", &q);

    FOR(tt, q) {
        char command[100];
        int a, b;
        scanf("%s%d%d", command, &a, &b);

        if (!strcmp(command, "change")) {
            updateTree(a, b - bushes[a]);
            bushes[a] = b;
        } else {
            int total = readSum(b) - readSum(a - 1);
            int items = b - a + 1;
            int avg = total / items;
            int itemsPlusOne = total - items * avg;

            long long int c = comb(items, itemsPlusOne);
            long long int c2 = multiComb(total, avg, items - itemsPlusOne, itemsPlusOne);

            printf("%d\n", (int)((c * c2) % MOD));
        }
    }
}
