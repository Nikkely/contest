#include "common.h"
#include "testHelper.h"

/**
 * 1次元累積和
 * これは手書きしてもいいと思う
 * 定義：
 * s_0 = 0
 * s_i = a_i-1 + a_i-2 + ... + a_0 (i != 0)
 */
template <typename T> class Cusum {
  int n;
  vector<T> s;

public:
  // コンストラクタ
  // order: O(N)
  Cusum(int _n) : n(_n) { s.assign(n + 1); }

  // 累積和準備
  // order: O(N)
  void init(const vector<T> &v) {
    assert(SIZE(v) == n);
    s[0] = 0;
    rep(i, n) { s[i + 1] = v[i] + s[i]; }
  }

  // [l, r) で指定した区間の和を出す
  // order: O(1)
  T doQuery(int l, int r) {
    assert(0 <= l && l < n);
    assert(0 < r && r <= n);
    return s[r] - s[l];
  }
};

int main() {
  vector<int> a = {4, 9, 8, 5, 10};
  Cusum<int> cs(5);
  cs.init(a);
  assert(cs.doQuery(2, 4) == 13);
  assert(cs.doQuery(0, 5) == 36);
  cout << "CUSUM 1D:PASS" << endl;
}