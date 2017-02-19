// The problem can be transformed to max-flow as described in https://www.topcoder.com/community/data-science/data-science-tutorials/maximum-flow-section-2/
// https://www.codechef.com/JAN17/problems/TOURISTS
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

namespace std {
    template<> struct hash<pair<int, int> > {
        size_t operator () (const pair<int,int> &p) const {
            return p.first * p.second;
        }
    };
}


#define MAX_N 100010
#define MAX_E 200010
map<pair<int, int>, int> edges;
vector<int> neighbor[MAX_N];

pair<int, int> result[MAX_E];
bool visited[MAX_N];
int degree[MAX_N];


void dfs(int node) {
    visited[node] = true;
    FOR(i, neighbor[node].size())
        if (!visited[neighbor[node][i]]) dfs(neighbor[node][i]);
}

int main(void) {
    int n = getInt();
    int e = getInt();
    FOR(i, e) {
        int u = getInt() - 1;
        int v = getInt() - 1;
        neighbor[u].push_back(v);
        neighbor[v].push_back(u);
        auto it = edges.find(make_pair(v, u));
        result[i] = make_pair(u, v);
        if (it == edges.end()) edges[make_pair(u, v)] = i;
        else {
            result[it->second] = it->first;
            edges.erase(it->first);
        }
    }
    bool ok = true;
    FOR(i, n) if (neighbor[i].size() == 0 || (neighbor[i].size() & 1) == 1) ok = false;
    if (!ok) {
        printString("NO");
        return 0;
    }
    dfs(0);
    FOR(i, n) if (!visited[i]) ok = false;
    if (!ok) {
        printString("NO");
        return 0;
    }

    PushRelabel pr(n * 2 + 2 + e * 2);
    for(auto it = edges.begin(); it != edges.end(); it++) {
        pair<int, int> p = it->first;
        pr.AddEdge(it->second + 2 * n + 2, it->second + 2 * n + 2 + e, 1);

        pr.AddEdge(p.first + 1, it->second + 2 * n + 2, 1);
        pr.AddEdge(it->second + 2 * n + 2 + e, p.second + 1 + n, 1);

        pr.AddEdge(p.second + 1, it->second + 2 * n + 2, 1);
        pr.AddEdge(it->second + 2 * n + 2 + e, p.first + 1 + n, 1);

        degree[p.first]++;
        degree[p.second]++;
    }
    FOR(i, n) if (degree[i] > 0) {
        pr.AddEdge(0, i + 1, degree[i] >> 1);
        pr.AddEdge(i + 1 + n, n + n + 1, degree[i] >> 1);
    }
    LLI resultFlow = pr.GetMaxFlow(0, n + n + 1);
    if (resultFlow != edges.size()) {
        printString("NO");
        return 0;
    }

    FORE(i, 1, n + 1) FOR(j, pr.G[i].size()) {
        if (pr.G[i][j].cap > 0 && pr.G[i][j].flow > 0) {
            int edge = pr.G[i][j].to - 2 * n - 2;
            if (result[edge].first != i - 1) swap(result[edge].first, result[edge].second);
        }
    }
    printString("YES");
    FOR(i, e) printf("%d %d\n", result[i].first + 1, result[i].second + 1);
}

