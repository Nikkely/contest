#include "common.h"
#include <cassert>

template<typename Monoid>
class SegTree {
public:
    using F = function<Monoid(Monoid, Monoid)>;

    int size;
    Monoid seg[(1 << 18) - 1];

    const F f;
    const Monoid M1;

    SegTree(int n, const F _f, const Monoid& _M1) : f(_f), M1(_M1)
    {
        size = 1;
        while (size < n) size <<= 1;
        for (int i = 0; i < 2 * size - 1; i++) {
            seg[i] = M1;
        }
    }

    void set(int k, const Monoid &x) {
        seg[k + size] = x;
    }

    void build() {
        for (int k = size - 1; k > 0; k--) {
            seg[k] = f(seg[2 * k], seg[2 * k + 1]);
        }
    }

    void update(int k, const Monoid& x) {
        k += size;
        seg[k] = x;
        while (k >>= 1) {
            seg[k] = f(seg[2 * k], seg[2 * k + 1]);
        }
    }

    Monoid query(int a, int b) {
        Monoid L = M1, R = M1;
        for (a += size, b += size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) L = f(L, seg[a++]); // 0-indexなので、左が奇数になる
            if (b & 1) R = f(seg[--b], R);
        }
        return f(L, R);
    }

    Monoid& operator[] (const int& k) {
        return seg[k + size];
    }
};

class BITree { // 1-index
    public:
        BITree(int _n) {
            n = _n;
            for (int i = 0; i <= n; i++) bit[i] = 0;
        }
        int sum(int i) {
            int s = 0;
            for (; i > 0; i -= i & -i) { // 最後の1ビット減算
                s += bit[i];
            }
            return s;
        }

        void add(int i, int x) {
            for (; i <= n; i += i & -i) {
                bit[i] += x;
            }
        }
    private:
        int bit[(1 << 17)  + 1], n;
};

int main() {
    SegTree<int> st(8, [](int l, int r){ return min(l, r); }, 1e9);
    st[0] = 5; st[1] = 3; st[2] = 7; st[3] = 9;
    st[4] = 6; st[5] = 4; st[6] = 1; st[7] = 2;
    st.build();

    assert(st.query(0, 7) == 1);
    st.update(6, 100);
    assert(st.query(0, 6) == 3);
    assert(st.query(3, 8) == 2);
    assert(st.query(3, 4) == 9);
    cout << "Segment Tree: PASS" << endl;

    // せっかくなので転倒数を求める
    {
        BITree bit(4);
        int a[] = {3, 1, 4, 2};
        int ans = 0;
        for (int j = 0; j < 4; j++) {
            bit.add(a[j], 1);
            ans += j + 1 - bit.sum(a[j]);
        }
        assert(ans == 3);
    }
    {
        BITree bit(7);
        int a[] = {3, 1, 4, 2, 5, 7, 6};
        int ans = 0;
        for (int j = 0; j < 7; j++) {
            bit.add(a[j], 1);
            ans += j + 1 - bit.sum(a[j]);
        }
        assert(ans == 4);
    }
    cout << "Binary Index Tree: PASS" << endl;

    return 0;
}
