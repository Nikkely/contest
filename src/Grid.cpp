#include "common.h"
#include "testHelper.h"

/** direction utils */
enum Direction { RIGHT = 0, UP, LEFT, DOWN };
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
enum ExDirection { RT = 0, RU, UP, LU, LT, LD, DW, RD };
int exdx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int exdy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

/** 2D-array utils */
template <typename T> using Grid = vector<vector<T>>;
template <typename T> void makeGrid(Grid<T> grid, int h, int w) {
  grid.assign(h, vector<T>(w))
}
template <typename T> void makeGrid(Grid<T> grid, int h, int w, int val) {
  grid.assign(h, vector<T>(w, val))
}