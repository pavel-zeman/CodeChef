// The problem can be transformed to max-flow and solved using standard Ford-Fulkerson algorithm (taken from https://web.stanford.edu/~liszt90/acm/notebook.html#file3)
// https://www.codechef.com/FEB16/problems/CALLSCHE
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

void fail() {
    *((char *)0) = 0;
}

#define MAX 100
int p, d, h, n;
int lt1, lt2;
int l[MAX];
int r[MAX][MAX];
int meeting[MAX][MAX][MAX];

int remainDay[MAX][MAX];
int remainForLunch[MAX][MAX];


typedef int LL;

struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow(flow), index(index) {}
  LL rcap() { return cap - flow; }
};


struct PushRelabel {
  int N;
  vector<vector<Edge> > G;
  vector<LL> excess;
  vector<int> dist, active, count;
  queue<int> Q;

  PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}

  void AddEdge(int from, int to, int cap) {
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
    //printf("Adding edge %d %d %d\n", from, to, cap);
  }

  void Enqueue(int v) {
    if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
  }

  void Push(Edge &e) {
    int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;
    excess[e.from] -= amt;
    Enqueue(e.to);
  }

  void Gap(int k) {
    for (int v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }

  void Relabel(int v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    for (int i = 0; i < (int)G[v].size(); i++)
      if (G[v][i].cap - G[v][i].flow > 0)
	dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }

  void Discharge(int v) {
    for (int i = 0; excess[v] > 0 && i < (int)G[v].size(); i++) Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1)
	Gap(dist[v]);
      else
	Relabel(v);
    }
  }

  LL GetMaxFlow(int s, int t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (int i = 0; i < (int)G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }

    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }

    LL totflow = 0;
    for (int i = 0; i < (int)G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }

  void PrintFlow() {
    FOR(i, N) FOR(j, G[i].size()) {
        if (G[i][j].cap > 0 && G[i][j].flow > 0) {
            printf("%d %d %d %d\n", G[i][j].from, G[i][j].to, G[i][j].cap, G[i][j].flow);
        }
    }
  }

};

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        bool ok = true;
        int total = 0;
        p = getInt();
        d = getInt();
        h = getInt();
        n = getInt();
        FOR(i, p) l[i] = getInt();
        lt1 = getInt() - 1;
        lt2 = getInt() - 1;
        FOR(i, d) FOR(j, h) {
            r[i][j] = getInt();
            if (r[i][j] > p) ok = false;
            total += r[i][j];
        }
        FOR(i, p) FOR(j, d) FOR(k, h) meeting[i][j][k] = getInt() ^ 1;

        FOR(i, p) FOR(j, d) {
            remainDay[i][j] = n;
            remainForLunch[i][j] = lt2 - lt1 + 1;
        }
        FOR(i, p) FOR(j, d) FOR(k, h) {
            remainDay[i][j] -= meeting[i][j][k];
            if (k >= lt1 && k <= lt2) remainForLunch[i][j] -= meeting[i][j][k];
        }
        FOR(i, p) FOR(j, d) if (remainDay[i][j] < 0 || remainForLunch[i][j] < 1) ok = false;
        if (ok) {
            PushRelabel pr(1 + p + p * d + p * d + d * h + 1);
            int opStart = 1;
            int dStart = opStart + p;
            int lunchStart = dStart + p * d;
            int rStart = lunchStart + p * d;
            int stop = rStart + d * h;
            FOR(i, p) pr.AddEdge(0, opStart + i, l[i]);
            FOR(i, p)
                FOR(j, d)
                    if (remainDay[i][j] > 0)
                        pr.AddEdge(opStart + i, dStart + i * d + j, remainDay[i][j]);
            FOR(i, p)
                FOR(j, d)
                    if (remainDay[i][j] > 0 && remainForLunch[i][j] > 1)
                        pr.AddEdge(dStart + i * d + j, lunchStart + i * d + j, remainForLunch[i][j] - 1);

            FOR(i, p) FOR(j, d) FOR(k, h)
                if (remainDay[i][j] > 0 && r[j][k] > 0 && !meeting[i][j][k]) {
                    if (k >= lt1 && k <= lt2)
                        pr.AddEdge(lunchStart + i * d + j, rStart + j * h + k, 1);
                    else
                        pr.AddEdge(dStart + i * d + j, rStart + j * h + k, 1);
                }
            FOR(i, d) FOR(j, h)
                if (r[i][j] > 0)
                    pr.AddEdge(rStart + i * h + j, stop, r[i][j]);

            int result = pr.GetMaxFlow(0, stop);
            ok = result == total;
        }

        puts(ok ? "Yes" : "No");
    }
}

