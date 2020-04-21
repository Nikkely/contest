#include <map>
#include <vector>

using namespace std;

bool inline vector_check(vector<int> v1, vector<int> v2) {
    return v1.size() == v2.size() && equal(v1.cbegin(), v1.cend(), v2.cbegin());
}

bool inline map_check(map<int, int> m1, map<int, int> m2) {
    return m1.size() == m2.size() && equal(m1.cbegin(), m1.cend(), m2.cbegin());
}
