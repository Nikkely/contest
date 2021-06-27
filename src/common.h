/**
 * Includes
 */
#include <algorithm>
#include <assert.h>
#include <fstream>
#include <functional>
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
/* loops */
#define rep(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)
#define rep1(i, n) for (int i = 1, i##_len = (n); i <= i##_len; ++i)
#define repc(i, n) for (int i = 0, i##_len = (n); i <= i##_len; ++i)
#define repx(i, s, e, d)                                                       \
  for (int i = (s), i##_end = (e), i##_inc = (d); i < i##_end; i += i##_inc)
#define repr(i, n) for (int i = (n - 1); i >= 0; --i)
#define reprx(i, s, e, d)                                                      \
  for (int i = (s), i##_end = (e), i##_inc = (d); i > i##_end; i += i##_inc)
#define rept(n)                                                                \
  for (int __i__LINE__ = 0, __i__LINE__##_len = (n);                           \
       __i__LINE__ < __i__LINE__##_len; ++__i__LINE__)
#define repi(itr, ds)                                                          \
  for (auto itr = (ds).begin(), itr##_end = (ds).end(); itr != itr##_end; itr++)
#define repz(c) for (char c = 'a'; c <= 'z'; c++)
/** other utils */
#define SIZE(c) ((int)(c).size())
#define ALL(x) (x).begin(), (x).end()
#define ZERO(a) memset(a, 0, sizeof(a))
#define DIST2(x1, y1, x2, y2)                                                  \
  (((x1) - (x2)) * ((x1) - (x2)) + ((y1) - (y2)) * ((y1) - (y2)))
#define IS_EVEN(x) (!((x) % 2))
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
/** vector utils */
#define MAX_INDEX(v) ((int)distance(v.begin(), max_element(ALL(v))))
#define MIN_INDEX(v) ((int)distance(v.begin(), min_element(ALL(v))))
/**
 * Standard input Extends
 */
template <typename T> istream &operator>>(istream &is, vector<T> &vec) {
  for (T &x : vec)
    is >> x;
  return is;
}
template <typename T, typename U>
ostream &operator<<(ostream &os, pair<T, U> &pair_var) {
  os << "(" << pair_var.first << ", " << pair_var.second << ")";
  return os;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &vec) {
  os << "{";
  for (int i = 0; i < vec.size(); i++) {
    os << vec[i] << (i + 1 == vec.size() ? "" : ", ");
  }
  os << "}";
  return os;
}
/**
 * Standard output Extends
 */
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
/** type alias */
using ll = long long;
using ii = pair<int, int>;
using il = pair<int, ll>;
using li = pair<ll, int>;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template <typename T>
using heapq = priority_queue<T, vector<T>, greater<T>>; // implement <
/** output config */
struct PreEntryInitializer {
  static constexpr int IOS_PREC = 15;
  PreEntryInitializer() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(IOS_PREC);
  };
} preEntryInitializer;
/** string utils */
const int ALPHABET_TOTAL = 26;
/**
 * If necessary
 */
// #define int long long int
// #include <atcoder/all>
// using namespace atcoder;

/**
 * Solver
 */
// signed main() {
//   return 0;
// }
