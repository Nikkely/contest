#include <map>
#include <vector>

using namespace std;

template <typename T>
bool inline vector_check(const vector<T> &v1, const vector<T> &v2) {
  return v1.size() == v2.size() && equal(v1.cbegin(), v1.cend(), v2.cbegin());
}

template <typename T>
bool inline map_check(const map<T, T> &m1, const map<T, T> &m2) {
  return m1.size() == m2.size() && equal(m1.cbegin(), m1.cend(), m2.cbegin());
}
