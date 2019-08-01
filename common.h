#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include<iomanip>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define rep(i,n) for(int i=0,i##_len=(n);i<i##_len;++i)
#define reps(i,n) for(int i=1,i##_len=(n);i<=i##_len;++i)
#define rrep(i,n) for(int i=((int)((n)-1));i>=0;--i)
#define rreps(i,n) for(int i=((int)(n));i>0;--i)
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define ZERO(a) memset(a,0,sizeof(a))
#define BIT(n) (1LL<<(n))
#define UNIQUE(v) v.erase(unique(v.begin(),v.end()),v.end());
#ifdef LOCAL
    #define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
    #define eprintf(...) 4545
#endif

typedef long long int lli;
using namespace std;
typedef pair<int, int> ii;
typedef priority_queue<int, vector<int>, greater<int> > heapq;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
// #define int long long int
struct aaa{
    aaa(){
        cin.tie(0); ios::sync_with_stdio(0); cout<<fixed<<setprecision(20);
    };
}aaaaaaa;

// signed main() {
//     return 0;
// }

inline void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// テスト用関数群
bool inline vector_check(vector<int> v1, vector<int> v2) {
    return v1.size() == v2.size() && equal(v1.cbegin(), v1.cend(), v2.cbegin());
}

bool inline map_check(map<int, int> m1, map<int, int> m2) {
    return m1.size() == m2.size() && equal(m1.cbegin(), m1.cend(), m2.cbegin());
}
