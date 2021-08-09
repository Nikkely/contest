#include "common.h"
#include "testHelper.h"

#include <atcoder/all>
using namespace atcoder;

/*
  座標圧縮（1次元）
  圧縮後座標のvectorを返す
  order: O(NlogN)
*/
template <typename T> vector<T> compress(const vector<T> &v) {
  vector<T> tmp = v;
  sort(ALL(tmp));
  tmp.erase(unique(ALL(tmp)), tmp.end());

  vector<T> ret(v.size());
  rep(i, SIZE(v)) {
    ret[i] = lower_bound(tmp.begin(), tmp.end(), v[i]) - tmp.begin();
  }
  return ret;
}

int main() {
  {
    vector<int> seq{4, 2, 10};
    auto compV = compress(seq);
    assert(vector_check(compV, vector<int>{1, 0, 2}));
    cout << "1d-COMPRESS: PASS" << endl;
  }
}
