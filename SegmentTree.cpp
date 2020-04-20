#include "common.h"
#include <cassert>

/**
 * Segment Tree
 * モノイドたちに対して区間操作を行うデータ構造
 */
template<typename Monoid>
class SegTree {
public:
    using F = function<Monoid(Monoid, Monoid)>;

    int size;
    vector<Monoid> seg;

    const F f; // モノイドの二項演算子
    const Monoid M1; // モノイドの単位元

    /**
     * 初期化
     * @order O(N)
     */
    SegTree(int n, const F _f, const Monoid& _M1) : f(_f), M1(_M1)
    {
        size = 1;
        while (size < n) size <<= 1;
        seg.assign(2 * size, M1);
    }
    /**
     * セグ木構築 (セグメントを直接更新したとき用 基本使わない)
     * @order O(N)
     */
    void build() {
        for (int k = size - 1; k > 0; k--) {
            seg[k] = f(seg[2 * k], seg[2 * k + 1]);
        }
    }
    /**
     * セグメント更新
     * @order O(logN)
     */
    void update(int k, const Monoid& x) {
        k += size;
        seg[k] = x;
        while (k >>= 1) {
            seg[k] = f(seg[2 * k], seg[2 * k + 1]);
        }
    }
    /**
     * 区間クエリ
     * @order O(logN)
     */
    Monoid query(int a, int b) {
        Monoid L = M1, R = M1;
        for (a += size, b += size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) L = f(L, seg[a++]); // 0-indexなので、左が奇数になる
            if (b & 1) R = f(seg[--b], R);
        }
        return f(L, R);
    }
    /**
     * セグメントへの直接アクセス(値更新したとき適宜buildが必要)
     * @order O(1)
     */
    Monoid& operator[] (const int& k) {
        return seg[k + size];
    }
};

/**
 * Lazy Segment Tree
 * セグ木の遅延評価
 * 区間更新可能
 */
template<typename Monoid, typename OperatorMonoid = Monoid>
class LSegTree {
public:
    using F = function< Monoid(Monoid, Monoid) >;
    using G = function< Monoid(Monoid, OperatorMonoid) >;
    using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;
    using P = function< OperatorMonoid(OperatorMonoid, int) >;

    int size;
    vector<Monoid> seg; // セグメント(要素)
    vector<OperatorMonoid> lazy; //伝播を遅延させるため滞留させておく(作用素)
    const F f; // クエリに用いる演算
    const G g; // 要素と作用素のマージの演算
    const H h; // 作用素と作用素のマージの演算
    const P p; // 作用素を伝播するときにの演算
    const Monoid M1; // 要素の型
    const OperatorMonoid OM0; // 作用素の型

    /**
    * 初期化
    * @order O(N)
    */
    LSegTree(int n, const F f, const G g, const H h, const P p,
            const Monoid &M1, const OperatorMonoid OM0)
        : f(f), g(g), h(h), p(p), M1(M1), OM0(OM0)
    {
        init(n);
    }
    /**
     * 初期化 (簡易版)
     * @order O(N)
     */
    LSegTree(int n, const F f, const G g, const H h,
            const Monoid &M1, const OperatorMonoid OM0)
        : f(f), g(g), h(h),
        p([](OperatorMonoid o, int i){ return o; }),
      M1(M1), OM0(OM0)
    {
        init(n);
    }
    /**
     * 初期化 (超簡易版)
     * @order O(N)
     */
    LSegTree(int n, const F f, const Monoid &M1, const OperatorMonoid OM0)
        : f(f),
        g([](Monoid m, OperatorMonoid o){ return m + o; }),
        h([](OperatorMonoid o1, OperatorMonoid o2){ return o1 + o2; }),
        p([](OperatorMonoid o, int i){ return o; }),
      M1(M1), OM0(OM0)
    {
        init(n);
    }
    /**
     * セグ木初期化(初期化処理の共通化)
     * @order O(N)
     */
    void init(int n) {
        size = 1;
        while(size < n) size <<= 1;
        seg.assign(2 * size, M1);
        lazy.assign(2 * size, OM0);
    }
    /**
     * セグ木構築(セグメントを直接操作したとき用)
     * @order O(N)
     */
    void build()
    {
        for(int k = size - 1; k > 0; k--) {
            seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);
        }
    }
    /**
     * 1段伝播させる
     * @order O(1)
     */
    void propagate(int k, int len)
    {
        if(lazy[k] != OM0) {
            if(k < size) {
                lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
                lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
            }
        seg[k] = g(seg[k], p(lazy[k], len));
        lazy[k] = OM0;
        }
    }
    /**
     * 区間更新
     * @order O(logN)
     */
    Monoid update(int a, int b, const OperatorMonoid &x, int k, int l, int r)
    {
        propagate(k, r - l);
        if(r <= a || b <= l) { // 管理区間外への更新はしない
            return seg[k];
        } else if(a <= l && r <= b) { // 更新区間が管理区間を完全に含む
            lazy[k] = h(lazy[k], x);
            propagate(k, r - l);
            return seg[k];
        } else { // 区間が部分的に含まれるので、下に問い合わせ
            return seg[k] = f(update(a, b, x, 2 * k + 0, l, (l + r) >> 1),
                                update(a, b, x, 2 * k + 1, (l + r) >> 1, r));
        }
    }
    /**
     * 区間更新(はじめの一回)
     * @order O(logN)
     */
    Monoid update(int a, int b, const OperatorMonoid &x)
    {
        return update(a, b, x, 1, 0, size);
    }
    /**
     * 区間クエリ
     * @order O(logN)
     */
    Monoid query(int a, int b, int k, int l, int r)
    {
        propagate(k, r - l);
        if(r <= a || b <= l) {
          return M1;
        } else if(a <= l && r <= b) {
          return seg[k];
        } else {
          return f(query(a, b, 2 * k + 0, l, (l + r) >> 1),
                query(a, b, 2 * k + 1, (l + r) >> 1, r));
        }
    }
    /**
     * 区間クエリ(はじめの一回)
     * @order O(logN)
     */
    Monoid query(int a, int b)
    {
        return query(a, b, 1, 0, size);
    }
    /**
     * 要素へのランダムアクセス(初期化以外ほぼ使わないかも buildしてね)
     * @order O(1)
     */
    Monoid& operator[](const int &k)
    {
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
    {
        SegTree<int> st(8, [](int l, int r){ return min(l, r); }, 1e9);
        st[0] = 5; st[1] = 3; st[2] = 7; st[3] = 9;
        st[4] = 6; st[5] = 4; st[6] = 1; st[7] = 2;
        st.build();

        assert(st.query(0, 7) == 1);
        st.update(6, 100);
        assert(st.query(0, 6) == 3);
        assert(st.query(3, 8) == 2);
        assert(st.query(3, 4) == 9);
    }
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

    {
        LSegTree<int> lst(8, [](int l, int r){ return min(l, r); }, 1e9, 0);
        lst[0] = 5; lst[1] = 3; lst[2] = 7; lst[3] = 9;
        lst[4] = 6; lst[5] = 4; lst[6] = 1; lst[7] = 2;
        lst.build();

        assert(lst.query(0, 7) == 1);
        lst.update(6, 8, 100);
        assert(lst.query(0, 6) == 3);
        lst.update(0, 5, 100);
        assert(lst.query(3, 8) == 4);
        lst.update(0, 8, 1000);
        lst.update(4, 8, 200);
        lst.update(0, 3, 200);
        assert(lst.query(0, 8) == 1109);
    }
    cout << "Lazy Segment Tree: PASS" << endl;
    return 0;
}
