#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int lli;
using namespace std;
typedef pair<int, int> ii;
// #define int long long int

inline void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// signed main() {
//     return 0;
// }

// テスト用関数郡
bool inline vector_check(vector<int> v1, vector<int> v2) {
    return v1.size() == v2.size() && equal(v1.cbegin(), v1.cend(), v2.cbegin());
}

bool inline map_check(map<int, int> m1, map<int, int> m2) {
    return m1.size() == m2.size() && equal(m1.cbegin(), m1.cend(), m2.cbegin());
}
