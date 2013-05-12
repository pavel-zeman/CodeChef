#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


#define MOD 747474747


int points[7000][5];
long long distances[7000];
int positions[7000];
int totalPos;
int d;

long long sqr(long long input) {
    return input * input;
}

void swap(int a, int b) {
    int temp1 = positions[a];
	positions[a] = positions[b];
	positions[b] = temp1;
	long long temp2 = distances[a];
    distances[a] = distances[b];
	distances[b] = temp2;
}

int parent(int a) {
    return (a - 1) >> 1;
}

int child(int a) {
    return (a << 1) + 1;
}

void up(int a) {
    while (a > 0 && distances[a] > distances[parent(a)]) {
        swap(a, parent(a));
		a = parent(a);
    }
}

void down() {
    int origPosition = positions[0];
	long long origDistance = distances[0];
    int temp = 0;
	int c = child(temp);
	while (c < totalPos && origDistance < distances[c] || c + 1 < totalPos && origDistance < distances[c + 1]) {
        if (c + 1 < totalPos && distances[c + 1] > distances[c]) c++;
		positions[temp] = positions[c];
		distances[temp] = distances[c];
		temp = c;
		c = child(temp);
    }
	positions[temp] = origPosition;
	distances[temp] = origDistance;
}

long long getDistance(int a, int b) {
	long long total = 0;
    for(int l=0;l<d;l++) {
        total += sqr(points[a][l] - points[b][l]);
    }
    //printf("Distance %d %d: %lld\n", a, b, total);
    return total;
}

int main(void) {
    int t;
    scanf("%d", &t);
    FOR(i, t) {
        int n;
        scanf("%d %d", &n, &d);

        FOR(j, n) FOR(k, d) scanf("%d", &points[j][k]);

        int p = 0;
        for(int j=1;j<n;j++) {
            distances[p] = getDistance(j, 0);
            positions[p++] = j;
        }
        totalPos = p;

        // build heap
        FOR(j, totalPos) {
            up(j);
        }

        long long result = 1;

        while (totalPos > 0) {
            if (distances[0] == 0) break;

            result *= (distances[0] % MOD);
            result %= MOD;

            int vertex = positions[0];
            swap(--totalPos, 0);
            down();


            for(int j=0;j<totalPos;j++) {
                long long d = getDistance(positions[j], vertex);
                if (d > distances[j]) {
                    distances[j] = d;
                    up(j);
                }
            }
        }
        printf("%lld\n", result);
    }
}
