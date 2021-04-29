/**
 * Includes
 */
#include <algorithm>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Macros
 */
// loops
#define rep(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define rep1(i, n) for (int i = 1, i##_len = (n); i <= i##_len; ++i)
#define repc(i, n) for (int i = 0, i##_len = (n); i <= i##_len; ++i)
#define repx(i, s, e, d)                                                       \
  for (int i = (s), i##_end = (e), i##_inc = (d); i < i##_end; i += i##_inc)
#define repr(i, n) for (int i = (n); i > 0; --i)
#define reprx(i, s, e, d)                                                      \
  for (int i = (s), i##_end = (e), i##_inc = (d); i > i##_end; i += i##_inc)
#define rept(n)                                                                \
  for (int ___i___ = 0, i##_len = (n); ___i___ < i##_len; ++___i___)
#define repi(itr, ds)                                                          \
  for (auto itr = (ds).begin(), itr##_end = (ds).end(); itr != itr##_end; itr++)
// other
#define SIZE(c) ((int)(c).size())
#define ALL(x) (x).begin(), (x).end()
#define ZERO(a) memset(a, 0, sizeof(a))
#define DIST2(x1, y1, x2, y2)                                                  \
  (((x1) - (x2)) * ((x1) - (x2)) + ((y1) - (y2)) * ((y1) - (y2)))
#define ISEVEN(x) (!((x) % 2))
#define CEIL(x, y) (((x) + ((x) > 0 ? (y)-1 : -((y)-1))) / (y))
#define YESNO(bool)                                                            \
  if (bool) {                                                                  \
    cout << "YES" << endl;                                                     \
  } else {                                                                     \
    cout << "NO" << endl;                                                      \
  }
#define yesno(bool)                                                            \
  if (bool) {                                                                  \
    cout << "yes" << endl;                                                     \
  } else {                                                                     \
    cout << "no" << endl;                                                      \
  }
#define YesNo(bool)                                                            \
  if (bool) {                                                                  \
    cout << "Yes" << endl;                                                     \
  } else {                                                                     \
    cout << "No" << endl;                                                      \
  }
/**
 * Standard input helpers
 */
// vector:input
template <typename T> istream &operator>>(istream &is, vector<T> &vec) {
  for (T &x : vec)
    is >> x;
  return is;
}
// pair:output
template <typename T, typename U>
ostream &operator<<(ostream &os, pair<T, U> &pair_var) {
  os << "(" << pair_var.first << ", " << pair_var.second << ")";
  return os;
}
// vector:output
template <typename T> ostream &operator<<(ostream &os, const vector<T> &vec) {
  os << "{";
  for (int i = 0; i < vec.size(); i++) {
    os << vec[i] << (i + 1 == vec.size() ? "" : ", ");
  }
  os << "}";
  return os;
}
// map:output
template <typename T, typename U>
ostream &operator<<(ostream &os, map<T, U> &map_var) {
  os << "{";
  repi(itr, map_var) {
    os << *itr;
    itr++;
    if (itr != map_var.end())
      os << ", ";
    itr--;
  }
  os << "}";
  return os;
}
// set:output
template <typename T> ostream &operator<<(ostream &os, set<T> &set_var) {
  os << "{";
  repi(itr, set_var) {
    os << *itr;
    itr++;
    if (itr != set_var.end())
      os << ", ";
    itr--;
  }
  os << "}";
  return os;
}
/**
 * Helpers
 */
// type alias
using ll = long long;
using ii = pair<int, int>;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template <typename T>
using heapq = priority_queue<T, vector<T>, greater<T>>; // implement <
// 2d counters
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int exdx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int exdy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
// output
struct PreEntryInitializer {
  static constexpr int IOS_PREC = 15;
  PreEntryInitializer() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(IOS_PREC);
  };
} preEntryInitializer;
/**
 * If necessary
 */
// #define int long long int
// #define INF (INT32_MAX / 2)
// using namespace atcoder; // for atcoder
/**
 * Solver
 */
// signed main() {
//   return 0;
// }
