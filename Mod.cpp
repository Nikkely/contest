#include "common.h"
#include <cassert>

const lli MOD = 1000000007LL;

inline lli mod_add(lli x, lli y) {
    return (x + y) % MOD;
}

inline lli mod_mul(lli x, lli y) {
    return (x * y) % MOD;
}

inline lli mod_sub(lli x, lli y) {
    return x - y >= 0 ? (x - y) % MOD : (x - y + MOD) % MOD;
}

inline lli mod_pow(lli x, lli y) {
    lli ret = 1;
    while (y > 0) {
        if (y & 1) ret = ret * x % MOD;
        x = x * x % MOD;
        y = y >> 1;
    }
    return ret;
}

// inline lli mod_inv(lli x, lli m) { // 拡張Euclid あんまよくわかってない
//     lli b = m, u = 1, v = 0;
//     while (b) {
//         lli t = x / b;
//         x -= t * b; swap(x, b);
//         u -= t * v; swap(u, v);
//     }
//     u %= MOD;
//     if (u < 0) u += m;
//     return u;
// }


inline lli mod_inv(lli x) {
    return mod_pow(x, MOD - 2);
}

inline lli mod_div(lli x, lli y) {
    return x * mod_inv(y) % MOD;
}

#define MAX_FAC 10000
lli fac[MAX_FAC], finv[MAX_FAC];
void init_fac() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    for (int i = 2; i < MAX_FAC; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        finv[i] = finv[i - 1] * mod_inv(i) % MOD;
    }
}
inline lli com(int n, int k) {
    if (n < k || n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

int main() {
    assert(mod_add(1000000007LL, 1LL) == 1LL);
    assert(mod_mul(1000000007LL, 1LL) == 0LL);
    assert(mod_sub(3LL, 1000000007LL) == 3LL);
    assert(mod_pow(4LL, 3LL) == 64LL);
    assert(mod_div(12LL, 3LL) == 4LL);

    init_fac();
    assert(com(5LL, 3LL) == 10LL);
    cout << "OK" << endl;
    return 0;
}
