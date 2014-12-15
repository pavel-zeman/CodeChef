// Brute force for size 32 or less. For bigger graphs, use heuristics based on the number of components, degree of all vertices and degrees of all vertices to "second level" (this seems to be sufficient).
// http://www.codechef.com/DEC14/problems/GOODGAL
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

#define MAX_NODES 2048
#define MAX_SMALL 32
#define MAX_DIST 10
#define INF (MAX_DIST - 1)

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

struct Graph {
    int nodes;
    bool data[MAX_NODES][MAX_NODES];
} referenceGraph, testedGraph, tempGraph;

bool visited[MAX_NODES];

int isoMapping[MAX_NODES];
bool isoUsed[MAX_NODES];


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

int degree(Graph *graph, int v) {
    int total = 0;
    FOR(i, graph->nodes) total += graph->data[v][i];
    return total;
}

int degree2(Graph *graph, int v) {
    bool used[MAX_NODES];
    FOR(i, graph->nodes) used[i] = false;
    int total = 0;
    FOR(i, graph->nodes) {
        if (graph->data[v][i]) {
            used[i] = true;
            FOR(j, graph->nodes) if (graph->data[i][j]) used[j] = true;
        }
    }
    FOR(i, graph->nodes) total += used[i];
    return total;
}


void visit(Graph *graph, int v) {
    visited[v] = true;
    FOR(i, graph->nodes) if (graph->data[v][i] && !visited[i]) visit(graph, i);
}

void doubleGraph(struct Graph *graph) {
    FOR(i, graph->nodes) FOR(j, graph->nodes) graph->data[i + graph->nodes][j + graph->nodes] = graph->data[i][j];
    FOR(i, graph->nodes) graph->data[i][i + graph->nodes] = graph->data[i + graph->nodes][i] = true;
    graph->nodes <<= 1;
}

void convertToGood(struct Graph *graph) {
    tempGraph.nodes = graph->nodes;
    FOR(i, tempGraph.nodes) FOR(j, tempGraph.nodes) tempGraph.data[i][j] = false;

    FOR(i, tempGraph.nodes)
        FORE(j, i + 1, tempGraph.nodes) if (graph->data[i][j])
            FOR(k, tempGraph.nodes) if (graph->data[j][k] && !graph->data[i][k] && i != k) tempGraph.data[i][k] = tempGraph.data[k][i] = true;
    FOR(i, tempGraph.nodes) FOR(j, tempGraph.nodes) graph->data[i][j] = tempGraph.data[i][j];
}

void reduce(struct Graph *graph) {
    FOR(i, graph->nodes) visited[i] = false;
    visit(graph, 0);
    int mapping[MAX_NODES];
    int target = 0;
    tempGraph.nodes = graph->nodes / 2;
    FOR(i, graph->nodes) mapping[i] = visited[i] ? target++ : -1;
    FOR(i, tempGraph.nodes) FOR(j, tempGraph.nodes) tempGraph.data[i][j] = false;
    FOR(i, graph->nodes) FOR(j, graph->nodes) if (graph->data[i][j] && mapping[i] >= 0 && mapping[j] >= 0) tempGraph.data[mapping[i]][mapping[j]] = true;

    FOR(i, tempGraph.nodes) FOR(j, tempGraph.nodes) graph->data[i][j] = tempGraph.data[i][j];
    graph->nodes = tempGraph.nodes;
}

int components(Graph *graph) {
    int components = 0;
    FOR(i, graph->nodes) visited[i] = false;
    FOR(i, graph->nodes) if (!visited[i]) { components++; visit(graph, i);}
    return components;
}

bool findMapping(Graph *referenceGraph, Graph *testedGraph, int level) {
    if (level == referenceGraph->nodes) return true;
    FOR(i, referenceGraph->nodes) if (!isoUsed[i]) {
        bool ok = true;
        FOR(j, level) if (referenceGraph->data[j][level] != testedGraph->data[isoMapping[j]][i]) {
            ok = false;
            break;
        }
        if (ok) {
            isoUsed[i] = true;
            isoMapping[level] = i;
            ok = findMapping(referenceGraph, testedGraph, level + 1);
            isoUsed[i] = false;
            if (ok) return true;
        }
    }
    return false;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        testedGraph.nodes = getInt();
        FOR(i, testedGraph.nodes) FOR(j, testedGraph.nodes) testedGraph.data[i][j] = false;
        int m = getInt();
        FOR(i, m) {
            int a = getInt() - 1;
            int b = getInt() - 1;
            testedGraph.data[a][b] = testedGraph.data[b][a] = true;
        }

        FOR(i, testedGraph.nodes * 2) FOR(j, testedGraph.nodes * 2) referenceGraph.data[i][j] = false;
        referenceGraph.nodes = 1;

        bool ok = false;
        while (referenceGraph.nodes < testedGraph.nodes) doubleGraph(&referenceGraph);

        if (referenceGraph.nodes == testedGraph.nodes) {
            doubleGraph(&referenceGraph);
            convertToGood(&referenceGraph);
            reduce(&referenceGraph);

            if (testedGraph.nodes <= MAX_SMALL) {
                ok = findMapping(&referenceGraph, &testedGraph, 0);
            } else {
                ok = true;
                int expectedDegree = degree(&referenceGraph, 0);
                FOR(i, testedGraph.nodes) if (degree(&testedGraph, i) != expectedDegree) {
                    ok = false;
                    break;
                }
                if (ok) {
                    int expectedDegree2 = degree2(&referenceGraph, 0);
                    FOR(i, testedGraph.nodes) if (degree2(&testedGraph, i) != expectedDegree2) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    int expectedComponents = components(&referenceGraph);
                    if (components(&testedGraph) != expectedComponents) {
                        ok = false;
                    }
                }
            }
        }
        printf(ok ? "YES\n" : "NO\n");
    }
}
