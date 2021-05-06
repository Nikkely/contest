#include "common.h"
#include "testHelper.h"

/**
 * 最大公約数の絶対値を求める
 * order: O(logN)
 **/
inline int gcd(int a, int b) {
  if (b == 0) {
    return abs(a);
  }
  return gcd(b, a % b);
}

/**
 * 最大公約数の絶対値を求める
 * 引数はサイズM(>=1)のvector
 * order: O(MlogN)
 **/
inline int gcd(vector<int> *v) {
  assert(SIZE(*v));
  int a = (*v)[0];
  repx(i, 1, SIZE(*v), 1) {
    int b = (*v)[i];
    a = gcd(a, b);
  }
  return a;
}

/**
 * ax + by = gcd(a, b)
 * を満たす整数(x, y)と、gcd(a, b)を求める
 * order: O(logN);
 **/
inline int extgcd(int a, int b, int &x, int &y) {
  int d = a;
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }

  d = extgcd(b, a % b, y, x);
  y = y - (a / b) * x;
  return d;
}

/**
 * 素数判定
 * order: O(N^1/2)
 **/
bool is_prime(int n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0)
      return false;
  }
  return n != 1;
}

/**
 * 約数列挙
 * order: O(N^1/2)
 **/
vector<int> divisor(int n) {
  vector<int> res;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      res.push_back(i);
      if (i != n / i)
        res.push_back(n / i);
    }
  }
  return res;
}

/**
 * 素因数分解
 * order: O(N^1/2)
 **/
map<int, int> prime_factor(int n) {
  map<int, int> res;
  for (int i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      ++res[i];
      n /= i;
    }
  }
  if (n != 1)
    res[n] = 1;
  return res;
}

/**
 * エラトステネスの篩
 * @param: n [2, n) の素数を返す
 * order: O(NloglogN)
 **/
vector<int> sieve(int n) {
  vector<int> ret;
  vector<int> is_prime_arr(n, 1);
  for (int i = 2; i < n; i++) {
    if (is_prime_arr[i]) {
      ret.push_back(i);
      for (int j = 2 * i; j < n; j += i)
        is_prime_arr[j] = 0;
    }
  }
  return ret;
}

/**
 * 拡張エラトステネスの篩
 * 要素を割り切る最小の整数を格納した配列を取得
 * @param: n [2, n) の配列を作成
 * order: O(NloglogN)
 **/
vector<int> ext_sieve(int n) {
  vector<int> min_prime(n, 1);
  for (int i = 2; i < n; i++) {
    if (min_prime[i] != 1)
      continue;

    min_prime[i] = i;
    for (int j = 2 * i; j < n; j += i)
      if (min_prime[j] == 1)
        min_prime[j] = i;
  }
  return min_prime;
}

/**
 * 高速素因数分解
 * order: O(logN)
 **/
map<int, int> prime_factor(int n, vector<int> &min_primes) {
  map<int, int> res;
  int p = min_primes[n];
  while (p > 1) {
    res[p]++;
    n /= p;
    p = min_primes[n];
  }
  return res;
}

int main() {
  assert(gcd(100, 10) == 10);
  assert(gcd(9, 12) == 3);
  assert(gcd(12, -8) == 4);
  assert(gcd(-12, -8) == 4);

  int x, y;
  assert(extgcd(100, 10, x, y) == 100 * x + 10 * y);
  assert(extgcd(9, 12, x, y) == 9 * x + 12 * y);
  assert(extgcd(12, -8, x, y) == 12 * x - 8 * y);
  assert(extgcd(-12, -8, x, y) == -12 * x - 8 * y);
  cout << "GCD: PASS" << endl;

  assert(!is_prime(10));
  assert(is_prime(7));
  assert(!is_prime(1));

  assert(vector_check<int>(divisor(10), {1, 10, 2, 5}));
  assert(vector_check<int>(divisor(9), {1, 9, 3}));

  assert(map_check<int>(prime_factor(12), {{2, 2}, {3, 1}}));
  assert(map_check<int>(prime_factor(9), {{3, 2}}));

  assert(vector_check<int>(sieve(10), {2, 3, 5, 7}));
  assert(vector_check<int>(sieve(13), {2, 3, 5, 7, 11}));

  auto min_primes = ext_sieve(12 + 1);
  assert(map_check<int>(prime_factor(12, min_primes), {{2, 2}, {3, 1}}));
  min_primes = ext_sieve(9 + 1);
  assert(map_check<int>(prime_factor(9, min_primes), {{3, 2}}));

  cout << "PRIME: PASS" << endl;
}
