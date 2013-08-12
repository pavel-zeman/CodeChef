// Aho-Corasick text search algorithm
// http://www.codechef.com/AUG13/problems/LYRC
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_W 520
#define MAX_LENGTH 5100
#define MAX_STATES 2500000
#define MAX_NEXT (26 + 26 + 10 + 1)
#define MAX_LINE 50100

struct word {
    char *data;
    int length;
    int previous;
    int count;
} words[MAX_W];
int w;

struct state {
    int next[MAX_NEXT];
    int f;
    int word;
    int previousWord;
    int count;
} states[MAX_STATES];
int s;

char c = 0;
int getInt() {
    int r = 0;
    while (!(c == '-' || (c >= '0' && c <= '9'))) c = getc_unlocked(stdin);
    bool minus = c == '-';
    if (minus) c = getc_unlocked(stdin);
    while (c >= '0' && c <= '9') {
        r = r * 10 + (c - '0');
        c = getc_unlocked(stdin);
    }
    return minus ? -r : r;
}


void checkDuplicity(int a) {
    int l = words[a].length;
    FOR(i, a) {
        if (words[i].length == l && !strcmp(words[i].data, words[a].data)) {
            words[a].previous = i;
            return;
        }
    }
    return;
}

int getNextPosition(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 26 + 26;
    return 26 + 26 + 10;
}

void addWord(char *data, int word) {
    int pos = 0;
    while (*data) {
        int nextPos = getNextPosition(*data);
        if (states[pos].next[nextPos] != -1) pos = states[pos].next[nextPos]; else {
            FOR(i, MAX_NEXT) states[s].next[i] = -1;
            states[s].word = -1;
            states[s].count = 0;
            states[pos].next[nextPos] = s;
            pos = s;
            s++;
        }
        data++;
    }
    states[pos].word = word;
}


int queue[MAX_STATES];
int qStart = 0, qEnd = 0;

void addQueue(int a) {
    queue[qEnd++] = a;
    qEnd %= MAX_STATES;
}

bool queueEmpty() {
    return qStart == qEnd;
}

int getQueue() {
    int result = queue[qStart];
    qStart = (qStart + 1) % MAX_STATES;
    return result;
}

void calcF(void) {
    states[0].f = 0;
    FOR(i, MAX_NEXT) if (states[0].next[i] != 0) {
        int n = states[0].next[i];
        states[n].f = 0;
        addQueue(n);
    }
    while (!queueEmpty()) {
        int state = getQueue();
        FOR(i, MAX_NEXT) {
            int n = states[state].next[i];
            if (n != -1) {
                int f = states[state].f;
                while (states[f].next[i] == -1) f = states[f].f;
                states[n].f = states[f].next[i];
                states[n].previousWord = states[states[n].f].word == -1 ? states[states[n].f].previousWord : states[n].f;
                addQueue(n);
            }
        }
    }
}

int main(void) {
    w = getInt();
    FOR(i, w) {
        char word[MAX_LENGTH];
        scanf("%s", word);
        words[i].length = strlen(word);
        words[i].data = (char *)malloc(words[i].length + 2);
        words[i].previous = -1;
        words[i].count = 0;

        strcpy(words[i].data, word);
        checkDuplicity(i);
    }

    s = 1;
    FOR(i, MAX_NEXT) states[0].next[i] = -1;
    states[0].word = -1;
    states[0].previousWord = -1;
    states[0].count = 0;

    // create the search state machine
    FOR(i, w) {
        if (words[i].previous == -1) {
            addWord(words[i].data, i);
        }
    }
    FOR(i, MAX_NEXT) if (states[0].next[i] == -1) states[0].next[i] = 0;
    calcF();

    //FOR(i, s) printf("%d -> %d, word %d, previousWord: %d\n", i, states[i].f, states[i].word, states[i].previousWord);

    // search the input strings
    int n = getInt();
    FOR(i, n) {
        char line[MAX_LINE];
        char *c = line;
        scanf("%s", line);
        int pos = 0;
        while (*c) {
            int nextPos = getNextPosition(*c);
            while (states[pos].next[nextPos] == -1) {
                pos = states[pos].f;
            }
            pos = states[pos].next[nextPos];
            states[pos].count++;
            c++;
        }
    }

    // calculate word totals
    FOR(i, s) {
        if (states[i].word != -1) words[states[i].word].count += states[i].count;
        int pw = states[i].previousWord;
        while (pw > 0) {
            if (states[pw].word != -1) words[states[pw].word].count += states[i].count;
            pw = states[pw].previousWord;
        }
    }

    FOR(i, w) {
        printf("%d\n", words[i].previous == -1 ? words[i].count : words[words[i].previous].count);
    }



}
