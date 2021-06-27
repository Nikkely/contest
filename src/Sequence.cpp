#include "common.h"
#include "testHelper.h"

/**
 * 条件を満たす最長部分列を求める
 * order: O(Nlog N)
 */
template <typename T>
vector<T> LongestSubSequence(const vector<T> seq,
                             function<bool(const T, const T)> comp, T inf) {
  int n = SIZE(seq);
  vector<T> dp(n, inf);
  rep(i, n) {
    auto it = upper_bound(ALL(dp), seq[i], comp);
    *it = seq[i];
  }
  auto it = lower_bound(ALL(dp), inf, comp);
  dp.erase(it, dp.end());
  return dp;
}
/** longest increasing subsequence */
inline vector<int> LIS(vector<int> seq) {
  return LongestSubSequence<int>(
      seq, [](const int x, const int y) { return x < y; }, 1000000007);
}

signed main() {
  vector<int> seq{1, 3, 5, 2, 4, 6};
  vector<int> exp{1, 2, 4, 6};
  auto ans = LIS(seq);
  assert(vector_check(exp, ans));
  cout << "LIS: PASS" << endl;
}
