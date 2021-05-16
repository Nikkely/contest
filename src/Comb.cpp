#include "common.h"
#include "testHelper.h"

#include <atcoder/all>
using namespace atcoder;
class Comb {
  using mint = modint;
  int N;
  vector<mint> fac;
  vector<mint> iFac;

public:
  Comb(int n, int mod) : N(n) { mint::set_mod(mod); }
  // O(N)
  void init() {
    fac.assign(N + 1, mint(0));
    iFac.assign(N + 1, mint(0));
    fac[0] = mint(1);
    fac[1] = mint(1);
    iFac[0] = mint(1);
    iFac[1] = mint(1);
    repx(i, 1, N - 1, 1) {
      mint mi = i + 1;
      fac[i + 1] = fac[i] * mi;
      iFac[i + 1] = iFac[i] / mi;
    }
  }
  // O(1)
  mint calc(int n, int k) {
    if (n == 0 && k == 0) {
      return mint(1);
    }
    if (n < k || k < 0) {
      return mint(0);
    }
    return fac[n] * iFac[n - k] * iFac[k];
  }
};

int main() {
  Comb comb(10, 1000000007);
  comb.init();
  assert(comb.calc(4, 2).val() == 6);
  assert(comb.calc(6, 3).val() == 20);
  cout << "COMBINATION: PASS" << endl;
}