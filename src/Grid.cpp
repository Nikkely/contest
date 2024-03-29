#include "common.h"
#include "testHelper.h"

/** direction utils */
enum class Direction { RIGHT = 0, UP, LEFT, DOWN };
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
enum class ExDirection { RT = 0, RU, UP, LU, LT, LD, DW, RD };
int exdx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int exdy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

/** 2D-array class */
template <typename T> class Grid {
private:
  vector<vector<T>> v;
  bool guard;
  const char *GRID_OUTPUT_DELIMITER = " ";

public:
  Grid(int h, int w) : guard(false) { v.assign(h, vector<T>(w)); }
  Grid(int h, int w, T val) : guard(false) { v.assign(h, vector<T>(w, val)); }
  Grid(int h, int w, T val, T guardVal) {
    guard = true;
    v.assign(h + 2, vector<T>(w + 2, val));
    rep(i, h) { v[i][0] = v[i][w + 1] = guardVal; }
    rep(j, w) { v[0][j] = v[h + 1][j] = guardVal; }
  }

  /** overload ope */
  const vector<T> &operator[](int col) const { return v[col]; }
  vector<T> &operator[](int col) { return v[col]; }
  bool operator!=(const Grid<T> &grid) const {
    int h = SIZE(this->v);
    if (h != SIZE(grid.v)) {
      return true;
    }
    int w = SIZE(this->v[0]);
    if (w != SIZE(grid.v[0])) {
      return true;
    }
    rep(i, h) {
      rep(j, w) {
        if (this->v[i][j] != grid.v[i][j]) {
          return true;
        }
      }
    }
    return false;
  }
  bool operator==(const Grid<T> &grid) const { return !(*this != grid); }
  istream &stdIn(istream &is) {
    if (!guard) {
      for (vector<T> &vec : v) {
        for (T &x : vec) {
          is >> x;
        }
      }
    } else {
      int h = SIZE(v);
      int w = SIZE(v[0]);
      repx(i, 1, h + 2, 1) {
        repx(j, 1, w + 2, 1) { is >> v[h][w]; }
      }
    }
    return is;
  }
  ostream &stdOut(ostream &os) const {
    int h = SIZE(v);
    int w = SIZE(v[0]);
    rep(i, h) {
      rep(j, w) { os << v[i][j] << (j + 1 == w ? "" : GRID_OUTPUT_DELIMITER); }
      if (i + 1 != h) {
        os << endl;
      }
    }
    return os;
  }
  int h() const { return SIZE(v); }
  int w() const { return SIZE(v[0]); }
};
/** standard io */
template <typename T> istream &operator>>(istream &is, Grid<T> &grid) {
  return grid.stdIn(is);
}
template <typename T> ostream &operator<<(ostream &os, const Grid<T> &grid) {
  return grid.stdOut(os);
}

/** 2D Cumulative Sum Utils */
/**
 * make Cumulative Sum grid
 * order: O(H*W)
 */
template <typename T> Grid<T> makeCumulativeGrid(const Grid<T> &grid, T zero) {
  const int height = grid.h();
  const int width = grid.w();
  Grid<T> cusum(height + 1, width + 1, zero);
  rep(h, height) {
    rep(w, width) {
      cusum[h + 1][w + 1] =
          cusum[h + 1][w] + cusum[h][w + 1] - cusum[h][w] + grid[h][w];
    }
  }
  return cusum;
}
/**
 * calculates culmulative sum of [x, x + w) & [y, y + h)
 * order: O(1);
 */
template <typename T> T calcCusum(Grid<T> &cusum, int y, int x, int h, int w) {
  return cusum[y + h][w + x] - cusum[y + h][x] - cusum[y][x + w] + cusum[y][x];
}

int main() {
  int H = 10, W = 10;
  Grid<int> A(H, W);
  assert(A.h() == H);
  assert(A.w() == W);
  rep(i, H) {
    rep(j, W) { A[i][j] = 1; }
  }
  Grid<int> B(H, W, 1);
  assert(A == B);

  Grid<int> C(H, W, 1, -1);
  assert(C[0][0] == -1);
  cout << "Grid:PASS" << endl;

  Grid<int> D(3, 3, 0);
  D[0][0] = 1;
  D[1][1] = 1;
  D[1][2] = 1;
  D[2][2] = 1;
  auto E = makeCumulativeGrid(D, 0);
  assert(calcCusum(E, 0, 0, 1, 1) == 1);
  assert(calcCusum(E, 0, 0, 3, 3) == 4);
  assert(calcCusum(E, 1, 1, 2, 2) == 3);
  cout << "CUMULATIVE SUM: PASS" << endl;
  return 0;
}