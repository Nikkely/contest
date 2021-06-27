#include "common.h"
#include "testHelper.h"

/**
 * ソート済の列から値が最も近い要素のiteratorを返す
 * order: O(Nlog N)
 */
template <typename T>
auto searchNearestValue(const vector<T> &v, const T &value) {
  auto rit = lower_bound(ALL(v), value);
  if (rit == v.begin()) {
    return rit;
  }

  auto lit = rit - 1;
  if (abs(*lit - value) <= abs(*rit - value)) {
    return lit;
  }
  return rit;
}

/**
 * めぐる式二分探索
 * Tは単調で四則演算実装されてればなんでもよい
 * order: O(log N)
 */
template <typename T>
T meguruBinSearch(T okEdge, T ngEdge, function<bool(T)> isOk) {
  T ok = okEdge;
  T ng = ngEdge;
  while (abs(ok - ng) > 1) {
    T mid = (ok + ng) / 2; // 本当は中点だす演算子を用意したい
    if (isOk(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }
  return ok;
}

int meguruTest(int N, int L, int K, int *A);
signed main() {
  // https://atcoder.jp/contests/typical90/tasks/typical90_a
  int N = 20, L = 1000, K = 4;
  int A[] = {51,  69,  102, 127, 233, 295, 350, 388, 417, 466,
             469, 523, 553, 587, 720, 739, 801, 855, 926, 954};
  assert(meguruTest(N, L, K, A) == 170);
  cout << "MEGURU: PASS" << endl;

  vector<int> B{100, 200, 300, 400};
  assert(*searchNearestValue<int>(B, 100) == 100);
  assert(*searchNearestValue<int>(B, 249) == 200);
  assert(*searchNearestValue<int>(B, 999) == 400);
  cout << "SearchNearestValue: PASS" << endl;
}

int meguruTest(int N, int L, int K, int *A) {
  return meguruBinSearch<int>(0, L + 1, [&](int M) {
    int cnt = 0;
    int cutLength = 0;
    rep(i, N) {
      if (A[i] - cutLength >= M) {
        cutLength = A[i];
        cnt++;
        if (cnt == K) {
          break;
        }
      }
    }
    int remain = L - cutLength;
    return cnt == K && (remain == 0 || remain >= M);
  });
}