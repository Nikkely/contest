#include "common.h"
#include "testHelper.h"

/** direction utils */
enum class Direction { RIGHT = 0, UP, LEFT, DOWN };
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
enum class ExDirection { RT = 0, RU, UP, LU, LT, LD, DW, RD };
int exdx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int exdy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

/** 2D-array utils */
template <typename T> using Grid = vector<vector<T>>;
template <typename T> void makeGrid(Grid<T> &grid, int h, int w) {
  grid.assign(h, vector<T>(w));
}
template <typename T> void makeGrid(Grid<T> &grid, int h, int w, T val) {
  grid.assign(h, vector<T>(w, val));
}
template <typename T>
void makeGridWithGuard(Grid<T> &grid, int h, int w, T guard) {
  makeGrid<T>(grid, h + 2, w + 2);
  rep(i, h) {
    grid[i][0] = guard;
    grid[i][w + 1] = guard;
  }
  rep(j, w) {
    grid[0][j] = guard;
    grid[h + 1][j] = guard;
  }
}
template <typename T>
void makeGridWithGuard(Grid<T> &grid, int h, int w, T val, T guard) {
  makeGrid<T>(grid, h + 2, w + 2, val);
  rep(i, h) {
    grid[i][0] = guard;
    grid[i][w + 1] = guard;
  }
  rep(j, w) {
    grid[0][j] = guard;
    grid[h + 1][j] = guard;
  }
}
/** overload ope */
template <typename T> istream &operator>>(istream &is, Grid<T> &grid) {
  for (vector<T> &vec : grid) {
    for (T &x : vec) {
      is >> x;
    }
  }
  return is;
}
template <typename T> bool operator!=(const Grid<T> &x, const Grid<T> &y) {
  int h = SIZE(x);
  if (h != SIZE(y)) {
    return true;
  }
  int w = SIZE(x[0]);
  if (w != SIZE(y[0])) {
    return true;
  }

  rep(i, h) {
    rep(j, w) {
      if (x[i][j] != y[i][j]) {
        return true;
      }
    }
  }
  return false;
}
template <typename T> bool operator==(const Grid<T> &x, const Grid<T> &y) {
  return !(x != y);
}
const char *G_GRID_OUTPUT_DELIMITER = " ";
template <typename T> ostream &operator<<(ostream &os, const Grid<T> &grid) {
  int h = SIZE(grid);
  int w = SIZE(grid[0]);
  rep(i, h) {
    rep(j, w) {
      os << grid[i][j] << (j + 1 == w ? "" : G_GRID_OUTPUT_DELIMITER);
    }
    if (i + 1 != h) {
      os << endl;
    }
  }
  return os;
}