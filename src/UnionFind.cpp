#include "common.h"
#include "test_helper.h"
#include <cassert>
class UnionFindWithSize {
    public:
        UnionFindWithSize(int N) : parent(N, -1) {}
        void unite(int x, int y) {
            x = find(x);
            y = find(y);
            if (x == y) return;
            if (parent[x] > parent[y]) swap(x, y);
            parent[x] += parent[y];
            parent[y] = x;
        }
        int find(int x) {
            if (parent[x] < 0) return x;
            return parent[x] = find(parent[x]);
        }
        int size(int x) {
            return -parent[find(x)];
        }
    private:
        vector<int> parent;
};

int main() {
    UnionFindWithSize ufws(5);
    assert(ufws.size(0) == 1);
    ufws.unite(0, 1);
    assert(ufws.find(0) == ufws.find(1));
    assert(ufws.size(0) == 2);
    assert(ufws.find(0) != ufws.find(2));
    ufws.unite(1, 2);
    assert(ufws.size(0) == 3);
    assert(ufws.find(0) == ufws.find(2));

    cout << "OK" << endl;
}
