// Divide the functions into segments of size sqrt(N) and maintain sum for each of these segments. Due to constraints, we have to use unsigned long long (the maximum sum is 10^19).
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

#define MAX_N 102000
#define MAX_SEGMENTS 320

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

unsigned long long int tree[MAX_N];
int l[MAX_N], r[MAX_N];
int a[MAX_N];
int n;
char c = 0;
int segmentSize;

vector<pair<int, int> > influencedSegments[MAX_N];


unsigned long long segments[MAX_SEGMENTS];

int getInt() {
    int r = 0;
    while (!(c >= '0' && c <= '9')) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return r;
}

unsigned long long read(int idx) {
	unsigned long long int sum = 0;
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

unsigned long long int calcInterval(int a, int b) {
    return read(b) - read(a - 1);
}

unsigned long long int calcSegment(int segment) {
    unsigned long long int result = 0;
    int start = segment * segmentSize;
    int end = start + segmentSize;
    FORE(i, start, end) result += calcInterval(l[i], r[i]);
    return result;
}

int main(void) {
    n = getInt();
    segmentSize = sqrt(n + 1) + 1;
    FOR(i, n + 3) tree[i] = 0;
    FOR(i, n) update(i + 1, a[i + 1] = getInt());
    FOR(i, n) {
        l[i] = getInt();
        r[i] = getInt();
    }
    FORE(i, n, segmentSize * segmentSize) l[i] = r[i] = 0;

    FOR(i, segmentSize) segments[i] = calcSegment(i);

    // pre-alocate space
    FOR(j, n + 1) influencedSegments[j].reserve(segmentSize);

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
            if (counter > 0) influencedSegments[j].push_back(make_pair(i, counter));
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

                if (y > a[x]) {
                    unsigned long long int diff = y - a[x];
                    for (vector<pair<int, int> >::iterator it = influencedSegments[x].begin(); it != influencedSegments[x].end(); it++) segments[it->first] += diff * it->second;
                } else {
                    unsigned long long int diff = a[x] - y;
                    for (vector<pair<int, int> >::iterator it = influencedSegments[x].begin(); it != influencedSegments[x].end(); it++) segments[it->first] -= diff * it->second;
                }
                a[x] = y;
                }
                break;
            case 2:
                int m = getInt() - 1;
                int n = getInt() - 1;
                unsigned long long int result = 0;
                if (m % segmentSize != 0) {
                    int end = (m / segmentSize) * segmentSize + segmentSize - 1;
                    if (end > n) end = n;
                    while (m <= end) {
                        result += calcInterval(l[m], r[m]);
                        m++;
                    }
                }
                int currentSegment = m / segmentSize;
                while (m + segmentSize - 1 <= n) {
                    result += segments[currentSegment++];
                    m += segmentSize;
                }
                while (m <= n) {
                    result += calcInterval(l[m], r[m]);
                    m++;
                }
                printf("%llu\n", result);
                break;
        }
    }
}
