// Exclusion and inclusion principle.
// https://www.codechef.com/JAN16/problems/SEAKAM
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

#define MAX_N 100010
#define MAX_M 10
int fact[MAX_N];
pair<int, int> pairs[MAX_M];
int perm[MAX_M];
bool used[MAX_M];

bool toAnalyze[MAX_M];

vector<int> analyzingNodes;
vector<int> analyzingPairs;


bool containsNode(int node) {
    FOR(i, analyzingNodes.size())
        if (analyzingNodes[i] == node)
            return true;
    return false;
}

void addAnalyzingNode(int node) {
    if (!containsNode(node)) analyzingNodes.push_back(node);
}

int countPermutations(int total, int level) {
    if (level < total) {
        int totalPerms = 0;
        FOR(i, total)
            if (!used[i]) {
                used[i] = true;
                perm[level] = analyzingNodes[i];
                totalPerms += countPermutations(total, level + 1);
                used[i] = false;
            }
        return totalPerms;
    } else {
        FOR(i, analyzingPairs.size()) {
            bool found = false;
            FOR(j, total - 1) {
                if ((perm[j] == pairs[analyzingPairs[i]].first && perm[j + 1] == pairs[analyzingPairs[i]].second) ||
                    (perm[j + 1] == pairs[analyzingPairs[i]].first && perm[j] == pairs[analyzingPairs[i]].second)) {
                    found = true;
                    break;
                }
            }
            if (!found) return 0;
        }
        return 1;
    }
}

int main(void) {
    fact[0] = 1;
    FORE(i, 1, MAX_N) fact[i] = i * (LLI)fact[i - 1] % MOD;

    int t = getInt();
    FOR(tt, t) {
        int n = getInt();
        int m = getInt();
        FOR(i, m) {
            pairs[i].first = getInt();
            pairs[i].second = getInt();
        }

        int bad = 0;
        FORE(i, 1, 1<<m) {
            int temp = i;
            int totalBits = 0;
            FOR(j, m) {
                toAnalyze[j] = temp & 1;
                totalBits += temp & 1;
                temp >>= 1;
            }
            int perms = 1;
            int decrease = 0;
            FOR(j, m)
                if (toAnalyze[j]) {
                    toAnalyze[j] = false;
                    analyzingNodes.clear();
                    analyzingPairs.clear();

                    addAnalyzingNode(pairs[j].first);
                    addAnalyzingNode(pairs[j].second);
                    analyzingPairs.push_back(j);

                    bool changed = true;
                    while (changed) {
                        changed = false;
                        FORE(k, j + 1, m) {
                            if (toAnalyze[k] && (containsNode(pairs[k].first) || containsNode(pairs[k].second))) {
                                addAnalyzingNode(pairs[k].first);
                                addAnalyzingNode(pairs[k].second);
                                analyzingPairs.push_back(k);
                                toAnalyze[k] = false;
                                changed = true;
                            }
                        }
                    }
                    FOR(k, analyzingNodes.size()) used[k] = false;
                    perms = perms * countPermutations(analyzingNodes.size(), 0);
                    decrease += analyzingNodes.size() - 1;
                }
            perms = perms * (LLI)fact[n - decrease] % MOD;
            if ((totalBits & 1) == 1) bad = (bad + perms) % MOD; else bad = (bad + MOD - perms) % MOD;
        }
        int result = (fact[n] + MOD - bad) % MOD;
        print(result);
    }
}

