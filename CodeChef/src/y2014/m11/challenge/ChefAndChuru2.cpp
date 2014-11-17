//
// http://www.codechef.com/NOV14/problems/FNCS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

#define MAX_N 101000
#define MAX_SEGMENTS 320

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

long long int tree[MAX_N];
int l[MAX_N], r[MAX_N];
int a[MAX_N];
int n;
char c = 0;
int segmentSize;

vector<int> influencedSegments[MAX_N];


struct segment {
    long long int total;
    bool valid;
} segments[MAX_SEGMENTS];

int getInt() {
    int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

long long read(int idx) {
	long long int sum = 0;
	while (idx > 0){
		sum += tree[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void update(int idx, long long int val) {
	while (idx <= n){
		tree[idx] += val;
		idx += (idx & -idx);
	}
}

long long int calcInterval(int a, int b) {
    return read(b) - read(a - 1);
}

long long int calcSegment(int segment) {
    long long int result = 0;
    int start = segment * segmentSize;
    int end = start + segmentSize;
    FORE(i, start, end) result += calcInterval(l[i], r[i]);
    return result;
}

int main(void) {
    n = getInt();
    segmentSize = sqrt(n + 1) + 1;


    FOR(i, n + 1) tree[i] = 0;
    FOR(i, n) update(i + 1, a[i + 1] = getInt());
    FOR(i, n) l[i] = getInt(), r[i] = getInt();
    FORE(i, n, segmentSize * segmentSize) l[i] = r[i] = 0;

    FORE(i, 1, segmentSize) {
        segments[i].total = calcSegment(i);
        segments[i].valid = true;
    }
    FOR(i, segmentSize) {
        // add segment to the list of influenced segments
        int used[MAX_N];
        FOR(j, n + 3) used[j] = 0;
        int start = segmentSize * i;
        int end = start + segmentSize;
        FORE(j, start, end) {
            used[l[j]]++;
            used[r[j] + 1]--;
        }
        int counter = 0;
        FOR(j, n + 1) {
            counter += used[j];
            if (counter > 0) influencedSegments[j].push_back(i);
            if (counter < 0) *((char *)0) = 0;
        }
    }


    int q = getInt();
    FOR(i, q) {
        int operation = getInt();
        switch (operation) {
            case 1: {
                int x = getInt();
                int y = getInt();
                update(x, y - a[x]);
                a[x] = y;
                // invalidate sums
                for (vector<int>::iterator it = influencedSegments[x].begin(); it != influencedSegments[x].end(); it++) segments[*it].valid = false;
                }
                break;
            case 2:
                int m = getInt() - 1;
                int n = getInt() - 1;
                long long int result = 0;
                if (m % segmentSize != 0) {
                    int end = (m / segmentSize) * segmentSize + segmentSize - 1;
                    if (end > n) end = n;
                    while (m <= end) {
                        result += calcInterval(l[m], r[m]);
                        m++;
                    }
                }
                while (m + segmentSize - 1 <= n) {
                    int currentSegment = m / segmentSize;
                    if (!segments[currentSegment].valid) {
                        segments[currentSegment].valid = true;
                        segments[currentSegment].total = calcSegment(currentSegment);
                    }
                    result += segments[currentSegment].total;
                    m += segmentSize;
                }
                while (m <= n) {
                    result += calcInterval(l[m], r[m]);
                    m++;
                }
                printf("%lld\n", result);
                break;
        }
    }
}
