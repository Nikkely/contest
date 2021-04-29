#include "common.h"
#include "testHelper.h"
#include <cassert>

/**
 * めぐる式二分探索
 * Tは+演算と/2の演算ができればなんでもよい
 * order: O(log N)
 */
template <typename T>
T meguruBinSearch(T okEdge, T ngEdge, function<bool(T)> isOk) {
  T ok = okEdge;
  T ng = ngEdge;
  while (abs(ok - ng) > 1) {
    T mid = (ok + ng) / 2;
    if (isOk(mid)) {
      ok = mid;
    } else {
      ng = mid;
    }
  }
  return ok;
}

signed main() {
  // https://atcoder.jp/contests/typical90/tasks/typical90_a
  int N = 20, L = 1000, K = 4;
  int A[] = {51,  69,  102, 127, 233, 295, 350, 388, 417, 466,
             469, 523, 553, 587, 720, 739, 801, 855, 926, 954};

  auto ans = meguruBinSearch<int>(0, L + 1, [&](int M) {
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
  assert(ans == 170);
  cout << "OK" << endl;
}