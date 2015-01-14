// Brute force approach trying to recursively find the solution for N=10000. Result is stored to a file and submitted as text.
// http://www.codechef.com/JAN15/problems/RANKA
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;

#define FOR(c, m) for(int c=0;c<(m);c++)
#define FORE(c, f, t) for(int c=(f);c<(t);c++)

#define MAX_M 1010
#define MOD 1000000007


const int N = 9;

bool valid(int x, int y)
{
   return (0 <= x && x < N && 0 <= y && y < N);
}

struct state
{
   int nextMove; // 1 or 2
   int board[N][N];
   bool visited[N][N];
   set <string> occured;
   string hash()
   {
      string ret;
      if(nextMove == 0) return "Invalid";
      ret += char('0' + nextMove);
      for(int i = 0; i < N; i++)
         for(int j = 0; j < N; j++)
            ret += char('0' + board[i][j]);
      return ret;
   }

   void init()
   {
      nextMove = 1;
      memset(board, 0, sizeof(board));
      occured.insert(hash());
   }

   map <int, bool> already;
   int cntResult;
   vector <int> xs, ys, delX, delY;

   void dfs(int x, int y, int color)
   {
      if(!valid(x, y)) return;
      if(board[x][y] != color)
      {
         if(board[x][y] == 0)
         {
            if(already.count(x * N + y)) return;
            already[x * N + y] = true;
            cntResult ++;
         }
         return;
      }
      if(visited[x][y]) return;
      visited[x][y] = true;
      xs.push_back(x);
      ys.push_back(y);
      dfs(x + 1, y, color);
      dfs(x - 1, y, color);
      dfs(x, y + 1, color);
      dfs(x, y - 1, color);
   }

   int dfsToCount(int x, int y)
   {
      already.clear();
      xs.clear();
      ys.clear();
      cntResult = 0;
      dfs(x, y, board[x][y]);
      already.clear();
      return cntResult;
   }

   state move(int x, int y)
   {
      state ret, invalid;
      invalid.nextMove = 0;
      if(x == 0 && y == 0)
      {
         state ret;
         ret.nextMove = 3 - nextMove;
         for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
               ret.board[i][j] = board[i][j];
         if(occured.count(ret.hash()))
         {
            return invalid;
         }
         ret.occured = occured;
         ret.occured.insert(ret.hash());
         return ret;
      }
      x --;
      y --;

      if(nextMove == 0) return invalid;
      if(valid(x, y) == false || board[x][y] != 0)
         return invalid;
      memset(visited, false, sizeof(visited));

      board[x][y] = nextMove;
      for(int i = 0; i < N; i++)
         for(int j = 0; j < N; j++)
            if(board[i][j] == 3 - nextMove && visited[i][j] == false)
            {
               int t = dfsToCount(i, j);
               if(t == 0)
               {
                  for(int k = 0; k < xs.size(); k ++)
                  {
                     delX.push_back(xs[k]);
                     delY.push_back(ys[k]);
                  }
               }
            }

      if(delX.size() == 0)
      {
         if(dfsToCount(x, y) == 0)
         {
            board[x][y] = 0;
            return invalid;
         }
      }

      ret.nextMove = 3 - nextMove;
      for(int i = 0; i < N; i++)
         for(int j = 0; j < N; j++)
            ret.board[i][j] = board[i][j];
      for(int i = 0; i < delX.size(); i++)
         ret.board[delX[i]][delY[i]] = 0;
      xs.clear();
      ys.clear();
      delX.clear();
      delY.clear();
      board[x][y] = 0;
      if(occured.count(ret.hash()))
         return invalid;
      ret.occured = occured;
      ret.occured.insert(ret.hash());
      return ret;
   }
};

state stateList[10000];
int x[10000];
int y[10000];

int maxLevel = 0;

bool move(int level) {
    if (level == 10000) {
        FOR(i, level) printf("%d %d\n", x[i], y[i]);
        return true;
    }
    if ((level & 1) <= 0) {
        FOR(j, 9) FOR(k, 9) {
            stateList[level + 1] = stateList[level].move(j + 1, k + 1);
            if (stateList[level + 1].nextMove != 0) {
                x[level] = j + 1;
                y[level] = k + 1;
                if (move(level + 1)) return true;
            }
        }
    } else {
        stateList[level + 1] = stateList[level].move(0, 0);
        if (stateList[level + 1].nextMove != 0) {
            if (move(level + 1)) return true;
        }
        FOR(j, 9) FOR(k, 9) {
            stateList[level + 1] = stateList[level].move(9 - j, 9 - k);
            if (stateList[level + 1].nextMove != 0) {
                x[level] = 9 - j;
                y[level] = 9 - k;
                if (move(level + 1)) return true;
            }
        }
    }
    return false;
}

int main(void) {
    state s;
    s.init();
    stateList[0] = s;
    move(0);
}
