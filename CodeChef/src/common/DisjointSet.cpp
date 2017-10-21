// Disjoint set

#define MAX_N 100000

class DisjointSet {
public:
    int prev[MAX_N];
    int depth[MAX_N];

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
