#include "common.h"
#include <cassert>

template<int MOD> struct Modnum {
    lli val;
    constexpr Modnum(lli v = 0) noexcept : val(v % MOD) {
        if (val < 0) v += MOD;
    }

    constexpr Modnum operator - () const noexcept {
        return val ? MOD - val : 0;
    }
    constexpr Modnum operator + (const Modnum& x) const noexcept {
        return Modnum(*this) += x;
    }
    constexpr Modnum operator - (const Modnum& x) const noexcept {
        return Modnum(*this) -= x;
    }
    constexpr Modnum operator * (const Modnum& x) const noexcept {
        return Modnum(*this) *= x;
    }
    constexpr Modnum operator / (const Modnum& x) const noexcept {
        return Modnum(*this) /= x;
    }

    constexpr Modnum& operator += (const Modnum& x) noexcept {
        val += x.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    constexpr Modnum& operator -= (const Modnum& x) noexcept {
        val -= x.val;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr Modnum& operator *= (const Modnum& x) noexcept {
        val = val * x.val % MOD;
        return *this;
    }
    constexpr Modnum& operator /= (const Modnum& x) noexcept {
        val = val * modinv(x.val).val % MOD;
        return *this;
    }

    constexpr bool operator == (const Modnum& x) const noexcept {
        return val == x.val;
    }
    constexpr bool operator != (const Modnum& x) const noexcept {
        return val == x.val;
    }

    friend constexpr ostream& operator << (ostream &os, const Modnum<MOD>& x) noexcept {
        return os << x.val;
    }
    friend constexpr istream& operator >> (istream &is, const Modnum<MOD>& x) noexcept {
        return is >> x.val;
    }
    static constexpr Modnum<MOD> modpow(const Modnum &x, lli n) noexcept {
        if (n == 0) return 1;
        auto t = modpow(x, n / 2);
        t *= t;
        if (n & 1) t *= x;
        return t;
    }
    static constexpr Modnum<MOD> modinv(const Modnum &x) noexcept {
        return modpow(x, MOD - 2);
    }
};

using mi = Modnum<1000000007>;

#define MAX_FAC 10000
mi fac[MAX_FAC], finv[MAX_FAC];
void init_fac() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    for (int i = 2; i < MAX_FAC; i++) {
        fac[i] = fac[i - 1] * i;
        finv[i] = finv[i - 1] * mi::modinv(i);
    }
}
inline mi com(int n, int k) {
    if (n < k || n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k]);
}

int main() {
    assert(mi(1000000007LL) + mi(1LL) == mi(1LL));
    assert(mi(1000000007LL) * mi(1LL) == mi(0LL));
    assert(mi(3LL) - mi(1000000007LL) == mi(3LL));
    assert(mi::modpow(mi(4LL), 3LL) == mi(64LL));
    assert(mi(12LL) / mi(3LL) == mi(4LL));
    cout << "ModIntClass OK" << endl;

    init_fac();
    assert(com(5LL, 3LL) == mi(10LL));
    cout << "Binomial coeffcients OK" << endl;
    return 0;
}
