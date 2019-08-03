#include "common.h"
#include <cassert>

class SegTree { // RMQ
    public:
        SegTree(int _n, int init = 1000000007) {
            big = init;
            n = 1;
            while (n < _n) n *= 2;

            for (int i = 0; i < 2 * n - 1; i++) {
                dat[i] = init;
            }
        }

        void update(int k, int x) {
            // インデックスを葉にもってくる
            k += n - 1;
            dat[k] = x;

            // 根へ向かう
            while (k > 0) {
                k = (k - 1) / 2;
                dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
            }
        }

        int query(int a, int b) {
            return query(a, b, 0, 0, n);
        }
        // 範囲[a, b)
        // kは節点を表す
        // l, rはkが葉の[l, r)に対応している
        int query(int a, int b, int k, int l, int r) {
            if (r <= a || b <= l) return big;

            if (a <= l && r <= b) {
                return dat[k];
            } else {
                return min(
                    query(a, b, k * 2 + 1, l, (l + r) / 2),
                    query(a, b, k * 2 + 2, (l + r) / 2, r)
                );
            }
        }
    private:
        int n;
        int dat[2 * (1 << 17) - 1];
        int big;
};

int main() {
    SegTree st(8);
    st.update(0, 5); st.update(1, 3); st.update(2, 7); st.update(3, 9);
    st.update(4, 6); st.update(5, 4); st.update(6, 1); st.update(7, 2);

    assert(st.query(0, 7) == 1);
    st.update(6, 100);
    assert(st.query(0, 6) == 3);
    assert(st.query(3, 8) == 2);
    assert(st.query(3, 4) == 9);
    cout << "Segment Tree: PASS" << endl;
    return 0;
}
