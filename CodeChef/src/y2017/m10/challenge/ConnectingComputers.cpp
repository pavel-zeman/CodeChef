// Find MST and then try to improve it by adding edges
// https://www.codechef.com/OCT17/problems/POINTCN
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)
#define LLI long long int
#define MOD 1000000007


char ccc = 0;
int getInt() {
    int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}

int getString(char *start) {
    char *data = start;
    while (!(ccc > ' ' && ccc <= '~')) ccc = getc_unlocked(stdin);
    while (ccc > ' ' && ccc <= '~') {
        *data++ = ccc;
        ccc = getc_unlocked(stdin);
    }
    *data = 0;
    return data - start;
}


int getSignedInt() {
    int r = 0;
    while (!(ccc == '-' || (ccc >= '0' && ccc <= '9'))) ccc = getc_unlocked(stdin);
    bool minus = ccc == '-';
    if (minus) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}

long long int getLongLongInt() {
    long long int r = 0;
    while (!(ccc >= '0' && ccc <= '9')) ccc = getc_unlocked(stdin);
    while (ccc >= '0' && ccc <= '9') {
        r = r * 10 + (ccc - '0');
        ccc = getc_unlocked(stdin);
    }
    return r;
}


template <class type> void print(type a) {
    if (a < 0) {
        putc_unlocked('-', stdout);
        a = -a;
    }
    if (a == 0) {
        putc_unlocked('0', stdout);
    } else {
        char result[20];
        int resSize = 0;
        while (a > 0) {
            result[resSize++] = '0' + a % 10;
            a /= 10;
        }
        while (--resSize >= 0) putc_unlocked(result[resSize], stdout);
    }
    putc_unlocked('\n', stdout);
}

void printString(const char *str) {
    while (*str) putc_unlocked(*str++, stdout);
    putc_unlocked('\n', stdout);
}

int power(int a, int b) {
    int sq = a;
    int result = 1;
    while (b > 0) {
        if ((b & 1) == 1) result = result * (LLI)sq % MOD;
        sq = sq * (LLI)sq % MOD;
        b >>= 1;
    }
    return result;
}

int inv(int a) {
    return power(a, MOD - 2);
}

template <class type> type gcd(type a, type b) {
    return b == 0 ? a : gcd(b, a % b);
}

void fail() {
    *((char *)0) = 0;
}

double cpu() {
    return clock() / (double)CLOCKS_PER_SEC;
}


#define MAX_N 1024

unsigned long long s[2];
unsigned long long xorshift128plus() {
	unsigned long long x = s[0];
	const unsigned long long y = s[1];
	x ^= x << 23;
	s[1] = x ^ y ^ (x >> 17) ^ (y >> 26);
	return s[0] = y;
}

const int MX = 1000;

int C[MX][MX];
int H[MX][MX];

bool connected[MAX_N][MAX_N];
char result[MAX_N];
int neighbors[MAX_N];
struct Edge {
    int a, b;
    int w;

    bool operator<(const Edge & other) const {
        return this->w < other.w;
    }

} edges[MX * MX];


// Disjoint set

#define MAX_DS (MX * MX)

class DisjointSet {
public:
    int prev[MAX_DS];
    int depth[MAX_DS];

    int root(int a) {
        while (prev[a] != a) a = prev[a];
        return a;
    }

    void add(int x, int y) {
        x = root(x);
        y = root(y);
        if (x != y) {
            if (depth[x] > depth[y]) prev[y] = x;
            else if (depth[y] > depth[x]) prev[x] = y;
            else {
                prev[y] = x;
                depth[x]++;
            }
        }
    }

    void clear(int n) {
        FOR(i, n) {
            prev[i] = i;
            depth[i] = 0;
        }
    }
} ds;

int main(void) {
    int t = getInt();
    FOR(tt, t) {
		int n = getInt();
		int Cmax = getInt();
		int Hmax = getInt();
		FOR(i, n) {
			C[i][i] = 0;
			s[0] = getLongLongInt();
			s[1] = getLongLongInt();
			FORE(j, i + 1, n) C[i][j] = C[j][i] = xorshift128plus() % (Cmax + 1);
		}

		FOR(i, n) {
			s[0] = getLongLongInt();
			s[1] = getLongLongInt();
			FOR(j, n) H[i][j] = xorshift128plus() % (Hmax + 1);
		}

		int totalEdges = 0;
		FOR(i, n) FORE(j, i + 1, n) {
            edges[totalEdges].a = i;
            edges[totalEdges].b = j;
            edges[totalEdges].w = C[i][j];
            totalEdges++;
		}
		sort(edges, edges + totalEdges);
		FOR(i, n) FOR(j, n) connected[i][j] = false;
		ds.clear(totalEdges);
		FOR(i, totalEdges) {
            int r1 = ds.root(edges[i].a);
            int r2 = ds.root(edges[i].b);
            if (r1 != r2) {
                ds.add(r1, r2);
                connected[edges[i].a][edges[i].b] = true;
                connected[edges[i].b][edges[i].a] = true;
            }
		}

		FOR(i, n) {
            int total = 0;
            FOR(j, n) if (connected[i][j]) total++;
            neighbors[i] = total;
		}

		FOR(i, 800) {
		    int maxGain = 0;
		    int c1, c2;
            FOR(j, n)
                FORE(k, j + 1, n) if (!connected[j][k]) {
                    int gain = - (C[j][k] + (H[j][neighbors[j] + 1] - H[j][neighbors[j]]) + (H[k][neighbors[k] + 1] - H[k][neighbors[k]]));
                    if (gain > maxGain) {
                        maxGain = gain;
                        c1 = j;
                        c2 = k;
                    }
                }
            if (maxGain > 0) {
                connected[c1][c2] = true;
                connected[c2][c1] = true;
                neighbors[c1]++;
                neighbors[c2]++;
            } else break;
		}



		FOR(i, n) {
            FOR(j, n) result[j] = connected[i][j] ? '1' : '0';
            result[n] = 0;
            printString(result);

		}
		//print(minScore);


		/*FOR(i, n) {
            FOR(j, n) printf("%d ", C[i][j]);
            printf("\n");
		}

		FOR(i, n) {
            FOR(j, n) printf("%d ", H[i][j]);
            printf("\n");
		}*/


    }
}

