// Remove offers which are supersets of other offers (e.g. remove 1,2,3 when there is also 1,2), because offer with lower number of items is always better. Then start a recursive search starting with the offers with the lowest number of items.
// https://www.codechef.com/NOV15/problems/CHEFSHOP
#include <bits/stdc++.h>
using namespace std;

#define FOR(c, m) for(int c=0;c<(int)(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)


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


void fail() {
    *((char *)0) = 0;
}

template <class type> type mx(type a, type b) {
    return a > b ? a : b;
}

template <class type> type mn(type a, type b) {
    return a < b ? a : b;
}

#define MAX_N 16
#define MAX_OFFER 33000

int price[MAX_N];
struct Offer {;
    int value;
    int ingredientCount;

    bool operator<(const Offer &other) const {
        return this->ingredientCount < other.ingredientCount ||
        (this->ingredientCount == other.ingredientCount && this->value > other.value);
    }
} offer[MAX_OFFER];

int n, m;
bool used[MAX_OFFER];
int ingredientCount[MAX_OFFER];

int getMaxSave(int startOffer, int remainPos, int pricePos) {
    int result = 0;
    if (startOffer < m && pricePos >= offer[startOffer].ingredientCount) {
        FORE(i, startOffer, m) {
            if ((remainPos & offer[i].value) == offer[i].value) {
                result = mx(result,
                    getMaxSave(i + 1, remainPos & ~offer[i].value, pricePos - offer[i].ingredientCount) + price[pricePos - offer[i].ingredientCount]
                );
            }
        }
    }
    return result;
}

int main(void) {
    int t = getInt();
    FOR(tt, t) {
        // read input data
        n = getInt();
        FOR(i, n) price[i] = getInt();
        sort(price, price + n);
        int totalOffers = 1 << n;
        FOR(i, totalOffers) used[i] = false;
        m = getInt();
        FOR(i, m) {
            int items = getInt();
            int value = 0;
            FOR(j, items) value |= 1 << (getInt() - 1);
            used[value] = true;
            ingredientCount[value] = items;
        }

        // remove superset offers
        FORE(i, 2, n + 1)
            FOR(j, totalOffers)
                if (used[j] && ingredientCount[j] == i)
                    FOR(k, totalOffers)
                        if (used[k] && k != j && (j & k) == j) used[k] = false;

        m = 0;
        FOR(i, totalOffers)
            if (used[i]) {
                offer[m].value = i;
                offer[m].ingredientCount = ingredientCount[i];
                m++;
            }
        sort(offer, offer + m);

        int save = getMaxSave(0, (1 << n) - 1, n);
        int total = 0;
        FOR(i, n) total += price[i];
        print(total - save);
    }
}

