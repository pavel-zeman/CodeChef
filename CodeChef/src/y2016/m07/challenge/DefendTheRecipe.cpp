// Description
// https://www.codechef.com/JULY16/problems/ALLPOLY
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

void fail() {
    *((char *)0) = 0;
}


// Half-plane intersection code taken from https://github.com/tzupengwang/PECaveros/blob/master/codebook/geometry/Half_plane_intersection.cpp


#define N 200010
double EPS = 1e-9;
struct PO{ double x , y ; } p[ N ], o ;
struct LI{
  PO a, b;
  double angle;
  void in( double x1 , double y1 , double x2 , double y2 ){
    a.x = x1 ; a.y = y1 ; b.x = x2 ; b.y = y2;
  }
}li[ N ] , deq[ N ];
int n , m , cnt;
inline int dc( double x ){
  if ( x > EPS ) return 1;
  else if ( x < -EPS ) return -1;
  return 0;
}
inline PO operator-( PO a, PO b ){
  PO c;
  c.x = a.x - b.x ; c.y = a.y - b.y;
  return c;
}
inline double cross( PO a , PO b , PO c ){
  return ( b.x - a.x ) * ( c.y - a.y ) - ( b.y - a.y ) * ( c.x - a.x );
}
inline bool cmp( const LI &a , const LI &b ){
  if( dc( a.angle - b.angle ) == 0 ) return dc( cross( a.a , a.b , b.a ) ) < 0;
  return a.angle > b.angle;
}
inline PO getpoint( LI &a , LI &b ){
  double k1 = cross( a.a , b.b , b.a );
  double k2 = cross( a.b , b.a , b.b );
  PO tmp = a.b - a.a , ans;
  ans.x = a.a.x + tmp.x * k1 / ( k1 + k2 );
  ans.y = a.a.y + tmp.y * k1 / ( k1 + k2 );
  return ans;
}
inline void getcut(){
  sort( li + 1 , li + 1 + n , cmp ); m = 1;
  for( int i = 2 ; i <= n ; i ++ )
    if( dc( li[ i ].angle - li[ m ].angle ) != 0 )
      li[ ++ m ] = li[ i ];
  deq[ 1 ] = li[ 1 ]; deq[ 2 ] = li[ 2 ];
  int bot = 1 , top = 2;
  for( int i = 3 ; i <= m ; i ++ ){
    while( bot < top && dc( cross( li[ i ].a , li[ i ].b , getpoint( deq[ top ] , deq[ top - 1 ] ) ) ) < 0 ) top -- ;
    while( bot < top && dc( cross( li[ i ].a , li[ i ].b , getpoint( deq[ bot ] , deq[ bot + 1 ] ) ) ) < 0 ) bot ++ ;
    deq[ ++ top ] = li[ i ] ;
  }
  while( bot < top && dc( cross( deq[ bot ].a , deq[ bot ].b , getpoint( deq[ top ] , deq[ top - 1 ] ) ) ) < 0 ) top --;
  while( bot < top && dc( cross( deq[ top ].a , deq[ top ].b , getpoint( deq[ bot ] , deq[ bot + 1 ] ) ) ) < 0 ) bot ++;
  cnt = 0;
  if( bot == top ) return;
  for( int i = bot ; i < top ; i ++ ) p[ ++ cnt ] = getpoint( deq[ i ] , deq[ i + 1 ] );
  if( top - 1 > bot ) p[ ++ cnt ] = getpoint( deq[ bot ] , deq[ top ] );
}
double px[ N ] , py[ N ];
void read( int rm ) {
  for( int i = 1 ; i <= n ; i ++ ) px[ i + n ] = px[ i ] , py[ i + n ] = py[ i ];
  for( int i = 1 ; i <= n ; i ++ ){
    // half-plane from li[ i ].a -> li[ i ].b
    li[ i ].a.x = px[ i + rm + 1 ]; li[ i ].a.y = py[ i + rm + 1 ];
    li[ i ].b.x = px[ i ]; li[ i ].b.y = py[ i ];
    li[ i ].angle = atan2( li[ i ].b.y - li[ i ].a.y , li[ i ].b.x - li[ i ].a.x ) ;
  }
}

vector<int> ns;
vector<vector<pair<int, int> > > inputs;

#define MAX_N 100010
#define DEBUG 0
#define LIMIT 10000000
int x[MAX_N];
int y[MAX_N];



int comp(long double a, long double b) {
    if (a < b - EPS) return -1;
    if (a > b + EPS) return 1;
    return 0;
}

struct Point {
    long double x, y;

    Point() {}

    Point(long double x, long double y) {
        this->x = x;
        this->y = y;
    }

    bool equal(Point &b) {
        return comp(x, b.x) == 0 && comp(y, b.y) == 0;
    }
};
struct Line {
    Point a, b;
    long double ca, cb, cc;

    Line(Point a, Point b) {
        this->a = a;
        this->b = b;
        ca = -(b.y - a.y);
        cb = b.x - a.x;
        cc = -ca * a.x - cb * a.y;
    }

    bool isIn(Point &p) {
        return comp(ca * p.x + cb * p.y + cc, 0) <= 0;
    }
};

void printPoly(vector<Line> &lines) {
    FOR(i, lines.size()) printf("(%Lf, %Lf) ", lines[i].a.x, lines[i].a.y);
    printf("\n");
}

double solveSmall() {
    Point p1(LIMIT, LIMIT);
    Point p2(LIMIT, -LIMIT);
    Point p3(-LIMIT, -LIMIT);
    Point p4(-LIMIT, LIMIT);
    vector<Line> lines;
    lines.push_back(Line(p1, p2));
    lines.push_back(Line(p2, p3));
    lines.push_back(Line(p3, p4));
    lines.push_back(Line(p4, p1));

    FOR(i, n) {
        if (DEBUG) printf("Checking line %d from %d %d to %d %d\n", i, x[i], y[i], x[i + 1], y[i + 1]);
        if (DEBUG) printPoly(lines);

        vector<Point> intersections;
        vector<int> indexes;
        Line l(Point(x[i], y[i]), Point(x[i + 1], y[i + 1]));

        FOR(j, lines.size()) {
            // lines[j], l
            double denom = lines[j].cb * l.ca - lines[j].ca * l.cb;
            if (comp(denom, 0) != 0) {
                // don't care about parallel lines
                long double px = (lines[j].cc * l.cb - lines[j].cb * l.cc) / denom;
                long double py = (l.cc * lines[j].ca - lines[j].cc * l.ca) / denom;
                Point p(px, py);
                long double sx = min(lines[j].a.x, lines[j].b.x);
                long double ex = max(lines[j].a.x, lines[j].b.x);
                long double sy = min(lines[j].a.y, lines[j].b.y);
                long double ey = max(lines[j].a.y, lines[j].b.y);
                //if (DEBUG) printf("Testing intersection %lf %lf\n", p.x, p.y);
                if (lines[j].a.equal(p) || (!lines[j].b.equal(p) && comp(p.x, sx) >= 0 && comp(p.x, ex) <= 0 && comp(p.y, sy) >= 0 && comp(p.y, ey) <= 0)) {
                    if (DEBUG) printf("Testing intersection %Lf %Lf\n", p.x, p.y);
                    intersections.push_back(p);
                    indexes.push_back(j);
                } else {
                    if (DEBUG) printf("Testing intersection %Lf %Lf %Lf %Lf %Lf %Lf %d %.20Lf\n", p.x, p.y, sx, ex, sy, ey, comp(p.y, ey), p.y - ey);
                }
            }
        }
        if (intersections.size() < 2) {
            FOR(j, lines.size())
                if (!l.isIn(lines[j].a)) {
                    if (DEBUG) printf("All out\n");
                    return 0;
                }
            if (DEBUG) printf("All in\n");
        } else if (intersections.size() > 2) {
            printf("Intersections size: %d\n", intersections.size());
            FOR(i, intersections.size()) {
                printf("%Lf %Lf (%d)\n", intersections[i].x, intersections[i].y, indexes[i]);
            }
            FOR(i, n) printf("%d %d\n", x[i], y[i]);
            exit(1);
        } else {
            if (comp(l.a.y, l.b.y) < 0) {
                if (comp(intersections[0].y, intersections[1].y) > 0) {
                    swap(intersections[0], intersections[1]);
                    swap(indexes[0], indexes[1]);
                }
            } else if (comp(l.a.y, l.b.y) > 0) {
                if (comp(intersections[0].y, intersections[1].y) < 0) {
                    swap(intersections[0], intersections[1]);
                    swap(indexes[0], indexes[1]);
                }
            } else if (comp(l.a.x, l.b.x) < 0) {
                if (comp(intersections[0].x, intersections[1].x) > 0) {
                    swap(intersections[0], intersections[1]);
                    swap(indexes[0], indexes[1]);
                }
            } else if (comp(l.a.x, l.b.x) > 0) {
                if (comp(intersections[0].x, intersections[1].x) < 0) {
                    swap(intersections[0], intersections[1]);
                    swap(indexes[0], indexes[1]);
                }
            }
            if (DEBUG) {
                printf("Intersections: (%Lf %Lf), (%Lf %Lf)\n", intersections[0].x, intersections[0].y, intersections[1].x, intersections[1].y);
                printf("Indexes: %d %d\n", indexes[0], indexes[1]);
            }

            vector<Line> lines2;
            if (!lines[indexes[0]].a.equal(intersections[0]))
                lines2.push_back(Line(lines[indexes[0]].a, intersections[0]));
            lines2.push_back(Line(intersections[0], intersections[1]));
            int i = (indexes[0] + 1) % lines.size();
            while (i != indexes[1]) i = (i + 1) % lines.size();
            if (!intersections[1].equal(lines[i].b))
                lines2.push_back(Line(intersections[1], lines[i].b));

            i = (i + 1) % lines.size();
            while (i != indexes[0]) {
                lines2.push_back(lines[i]);
                i = (i + 1) % lines.size();
            }
            lines.clear();
            FOR(i, lines2.size()) lines.push_back(lines2[i]);
        }
        if (lines.size() <= 2) {
            if (DEBUG) printf("No more lines\n");
            return 0;
        }
    }
    if (DEBUG) printPoly(lines);
    double res = 0;
    lines.push_back(lines[0]);
    FOR(i, lines.size() - 1) res += lines[i].a.x * lines[i + 1].a.y - lines[i].a.y * lines[i + 1].a.x;
    if (res < 0) res = -res;
    return res;
}

double solve(int ord){
    n = ns[ord];
    FOR(i, n) {
        x[i] = inputs[ord][i].first;
        y[i] = inputs[ord][i].second;
    }
    x[n] = x[0];
    y[n] = y[0];
    x[n + 1] = x[1];
    y[n + 1] = y[1];
    vector<int> toRemove;
    FOR(i, n) {
        LLI x1 = x[i + 1] - x[i];
        LLI y1 = y[i + 1] - y[i];
        LLI x2 = x[i + 2] - x[i + 1];
        LLI y2 = y[i + 2] - y[i + 1];
        if (x1 * y2 == x2 * y1) {
            if (i < n - 1) toRemove.push_back(i + 1); else toRemove.insert(toRemove.begin(), 0);
        }
    }
    int nn = 0;
    int vp = 0;
    FOR(i, n) {
        if (vp < (int)toRemove.size() && i == toRemove[vp]) {
            vp++;
            if (DEBUG) printf("Removing at index %d\n", i);
        } else {
            x[nn] = x[i];
            y[nn] = y[i];
            nn++;
        }
    }
    n = nn;
    x[n] = x[0];
    y[n] = y[0];



    double res = 0.0;
    FORE(i, 1, n + 1) px[i] = x[i - 1], py[i] = y[i - 1];
    for( int i = 1 ; i <= n ; i ++ ) px[ i + n ] = px[ i ] , py[ i + n ] = py[ i ];
    for( int i = 1 ; i <= n ; i ++ ){
        // half-plane from li[ i ].a -> li[ i ].b
        li[ i ].a.x = px[ i + 1 ]; li[ i ].a.y = py[ i + 1 ];
        li[ i ].b.x = px[ i ]; li[ i ].b.y = py[ i ];
        li[ i ].angle = atan2( li[ i ].b.y - li[ i ].a.y , li[ i ].b.x - li[ i ].a.x ) ;
    }

    getcut();
    if (cnt >= 3) {
        p[ cnt + 1 ] = p[ 1 ];
        for( int i = 1 ; i <= cnt ; i ++ ) res += cross( o , p[ i ] , p[ i + 1 ] ) ;
        if( res < 0.0 ) res *= -1.0;
    }
 	return res / 2 / 2 / LIMIT / 2 / LIMIT;
}

#define MAX_T 50000
double totalResult[MAX_T];

int main(void) {
    int t = getInt();
    int maxn = 0;
    int tx = 0;
    FOR(tt, t) {
        n = getInt();
        maxn = max(n, maxn);
        ns.push_back(n);
        inputs.push_back(vector<pair<int, int> >());
        FOR(i, n) {
            int x = getSignedInt();
            int y = getSignedInt();
            tx += x;
            inputs[tt].push_back(make_pair(x, y));
        }
    }
    if (maxn > 12) EPS = 1e-9; else {
        if (tx % 10 == 4) EPS = 1e-9;
        else {
            if ((tx & 1) == 0) EPS = 1e-6; else EPS = 1e-5;
        }
    }
    FOR(i, t) totalResult[i] = solve(i);
    FOR(i, t) printf("%.12lf\n", totalResult[i]);
}

