// Maintain the leader's distance as a series of line segments and update the segments with each speed change.
// https://www.codechef.com/JAN16/problems/CYCLRACE
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

#define MAX_N 50010
#define TYPE_SPEED 1
#define TYPE_QUERY 2
#define MAX_CHANGE 1000000010


struct Cyclist {
    int speed;
    LLI pos;
    int leaderEndTime; // last time, when he is a leader

    Cyclist() {}

    Cyclist(int speed, LLI pos, int leaderEndTime) {
        this->speed = speed;
        this->pos = pos;
        this->leaderEndTime = leaderEndTime;
    }
} cyclist[MAX_N];


LLI getPos(Cyclist c, int time) {
    return c.pos + (LLI)c.speed * time;
}


map<int, Cyclist> speedIndex;

int getLeaderChangeTime(Cyclist leader, Cyclist newLeader) {
    LLI result = (leader.pos - newLeader.pos) / (newLeader.speed - leader.speed);
    if (result < 0) return -1;
    if (result >= MAX_CHANGE) return MAX_CHANGE;
    if (getPos(newLeader, result) <= getPos(leader, result)) result++;
    if (result >= MAX_CHANGE) return MAX_CHANGE;
    return result;
}

int getBegin(map<int, Cyclist>::iterator it, int def) {
    return it == speedIndex.begin() ? def : (--it)->second.leaderEndTime + 1;
}

int main(void) {
    getInt();
    int q = getInt();

    speedIndex[0] = Cyclist(0, 0, MAX_CHANGE);

    FOR(i, q) {
        int type = getInt();
        int time = getInt();
        while (speedIndex.begin()->second.leaderEndTime < time)
            speedIndex.erase(speedIndex.begin());

        if (type == TYPE_SPEED) {
            int c = getInt() - 1;
            int speed = getInt();

            if (speed != cyclist[c].speed) {
                cyclist[c].pos = getPos(cyclist[c], time);
                cyclist[c].pos -= time * (LLI)speed;
                cyclist[c].speed = speed;
                LLI posCurrent = getPos(cyclist[c], time);
                LLI posLeader = getPos(speedIndex.begin()->second, time);

                if (posCurrent > posLeader || posCurrent == posLeader && speed >= speedIndex.begin()->second.speed) {
                    speedIndex.erase(speedIndex.begin());

                    for(map<int, Cyclist>::iterator it = speedIndex.begin(); it != speedIndex.end();) {
                        map<int, Cyclist>::iterator it2 = it;
                        it2++;
                        if (speed >= it->first) {
                            speedIndex.erase(it);
                        } else {
                            int changeTime = getLeaderChangeTime(cyclist[c], it->second);
                            if (changeTime != MAX_CHANGE && changeTime <= it->second.leaderEndTime) {
                                cyclist[c].leaderEndTime = changeTime - 1;
                                break;
                            } else
                                speedIndex.erase(it);
                        }
                        it = it2;
                    }
                    if (speedIndex.empty()) cyclist[c].leaderEndTime = MAX_CHANGE;
                    speedIndex[cyclist[c].speed] = cyclist[c];
               } else {
                    map<int, Cyclist>::iterator it = speedIndex.lower_bound(speed);
                    map<int, Cyclist>::iterator itBack = it;
                    map<int, Cyclist>::iterator itPrev = it;
                    itPrev--;
                    int tt = getBegin(it, time);
                    int tt2 = MAX_CHANGE - 3;
                    if (it != speedIndex.end() && getPos(cyclist[c], tt) <= getPos(it->second, tt) ||
                        it == speedIndex.end() && getPos(cyclist[c], tt2) <= getPos(itPrev->second, tt2)) {
                        // do nothing
                    } else {
                        it--;
                        while (true) {
                            int changeTime = getLeaderChangeTime(it->second, cyclist[c]);
                            if (changeTime > it->second.leaderEndTime) break;
                            else if (changeTime > getBegin(it, time)) {
                                it->second.leaderEndTime = changeTime - 1;
                                break;
                            } else {
                                map<int, Cyclist>::iterator it2 = it;
                                it2--;
                                speedIndex.erase(it);
                                it = it2;
                            }
                        }
                        it = itBack;
                        while (it != speedIndex.end()) {
                            if (it->second.speed == speed) {
                                map<int, Cyclist>::iterator it2 = it;
                                it2++;
                                speedIndex.erase(it);
                                it = it2;
                            } else {
                                int changeTime = getLeaderChangeTime(cyclist[c], it->second);
                                if (changeTime == MAX_CHANGE || changeTime > it->second.leaderEndTime) {
                                    map<int, Cyclist>::iterator it2 = it;
                                    it2++;
                                    speedIndex.erase(it);
                                    it = it2;
                                } else {
                                    cyclist[c].leaderEndTime = changeTime - 1;
                                    break;
                                }
                            }
                        }
                        itPrev = speedIndex.end();
                        itPrev--;
                        if (it == speedIndex.end()) {
                            cyclist[c].leaderEndTime = MAX_CHANGE;
                        }
                        speedIndex[speed] = cyclist[c];
                    }
               }
            }
        } else {
            printf("%lld\n", getPos(speedIndex.begin()->second, time));
        }
    }
}

