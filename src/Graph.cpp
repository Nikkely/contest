#include "common.h"
#include "testHelper.h"

/**
 * 木の距離を計算
 * とあるノードから数えた木の各要素までの距離を求める
 * order: O(log N)
 */
void calcTreeDist(int N, int start, const vector<vector<il>> &graph,
                  vector<ll> &dist, const ll INF = 1 << 29) {
  assert(0 <= start && start < N);
  assert(N == SIZE(graph));
  assert(N == SIZE(dist));

  rep(i, N) { dist[i] = INF; }
  queue<int> q;
  q.push(start);
  dist[start] = 0;

  while (!q.empty()) {
    int pos = q.front();
    assert(0 <= pos && pos < N);

    q.pop();
    for (il next : graph[pos]) {
      assert(0 <= next.first && next.first < N);

      if (dist[next.first] == INF) {
        dist[next.first] = dist[pos] + next.second;
        q.push(next.first);
      }
    }
  }
  return;
}
/**
 * ベルマンフォード
 * order: O(VE)
 * 負の閉路が存在する場合falseを返す
 */
bool bellmanFord(int n, int start, const vector<vector<il>> &graph,
                 vector<ll> &dist, const ll INF = 1LL << 60) {
  assert(n == SIZE(graph));
  assert(n == SIZE(dist));

  rep(i, n) { dist[i] = INF; }
  dist[start] = 0;
  rep(i, n) {
    for (il tc : graph[i]) {
      int to = tc.first;
      assert(0 <= to && to < n);

      ll alt = dist[i] + tc.second;
      if (dist[to] > alt) {
        dist[to] = alt;
        if (i == n - 1) {
          // 頂点数回更新 すなわち 負の閉路が存在する
          return false;
        }
      }
    }
  }
  return true;
}

/**
 * ダイクストラ
 * order: O(E + VLogV)
 */
void dijkstra(int n, int start, const vector<vector<il>> &G, vector<ll> &dist,
              const ll INF = 1LL << 60) {
  assert(n == SIZE(G));
  assert(n == SIZE(dist));

  rep(i, n) { dist[i] = INF; }
  dist[start] = 0;
  heapq<li> Q; // (cost, pos)
  Q.push(li(0, start));
  while (!Q.empty()) {
    int from = Q.top().second;
    assert(0 <= from && from < n);

    Q.pop();
    for (il tc : G[from]) {
      int to = tc.first;
      assert(0 <= to && to < n);

      ll alt = dist[from] + tc.second;
      if (alt < dist[to]) {
        dist[to] = alt;
        Q.push(li(alt, to));
      }
    }
  }
}

void calcTreeDistTest();
void bellmanFordTest();
void dijkstraTest();

int main() {
  calcTreeDistTest();
  cout << "calcTreeDist: PASS" << endl;
  bellmanFordTest();
  cout << "bellmanFord: PASS" << endl;
  dijkstraTest();
  cout << "dijkstra: PASS" << endl;
}

void calcTreeDistTest() {
  // https://atcoder.jp/contests/typical90/tasks/typical90_c
  int N = 3;
  vector<vector<il>> G(N);
  G[0].push_back(il(1, 1));
  G[1].push_back(il(1, 1));
  G[1].push_back(il(2, 1));
  G[2].push_back(il(1, 1));
  vector<ll> dist(N);
  calcTreeDist(N, 0, G, dist);
  vector<ll> ans = {0, 1, 2};
  assert(vector_check<ll>(dist, ans));
}

void bellmanFordTest() {
  {
    int N = 3;
    vector<vector<il>> G(N);
    G[0].push_back(il(1, 1));
    G[1].push_back(il(1, 1));
    G[1].push_back(il(2, 2));
    G[2].push_back(il(1, 2));
    vector<ll> dist(N);
    bellmanFord(N, 0, G, dist);
    vector<ll> ans = {0, 1, 3};
    assert(vector_check(dist, ans));
  }
  {
    int N = 3;
    vector<vector<il>> G(N);
    G[0].push_back(il(1, 1));
    G[1].push_back(il(1, 1));
    G[1].push_back(il(2, 2));
    G[2].push_back(il(1, 2));
    G[2].push_back(il(0, -1));
    G[0].push_back(il(2, -1));
    vector<ll> dist(N);
    assert(!bellmanFord(N, 0, G, dist));
  }
}

void dijkstraTest() {
  int N = 3;
  vector<vector<il>> G(N);
  G[0].push_back(il(1, 1));
  G[1].push_back(il(1, 1));
  G[1].push_back(il(2, 2));
  G[2].push_back(il(1, 2));
  vector<ll> dist(N);
  dijkstra(N, 0, G, dist);
  vector<ll> ans = {0, 1, 3};
  assert(vector_check(dist, ans));
}