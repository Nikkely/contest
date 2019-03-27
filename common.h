#include <iostream>
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
lli LARGE_NUM = 1000000007;

inline void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

inline int euclid(int a, int b) {
    if (a > b) swap(a, b);
    int r = a % b;
    while (r > 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}
