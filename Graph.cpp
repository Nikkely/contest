#include "common.h"
#include "test_helper.h"
#include <cassert>

#define INF 1000000007

struct Edge {
    int from, to, cost;
    Edge(){}
    Edge(int f, int t, int c): from(f), to(t), cost(c) {};
    bool operator < (const Edge& e) const noexcept {
        return this->cost < e.cost;
    }
    bool operator <= (const Edge& e) const noexcept {
        return this->cost <= e.cost;
    }
    bool operator > (const Edge& e) const noexcept {
        return this->cost > e.cost;
    }
    bool operator >= (const Edge& e) const noexcept {
        return this->cost >= e.cost;
    }
};

/**
 * Bellman-Ford
 * @order O(|V| * |E|)
 * 頂点番号sからの最短距離を求める
 **/
vector<int> bellman_ford(vector<Edge> edges, int V, int s) {
    vector<int> dist(V);
    int E = edges.size();
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[s] = 0;
    while (true) {
        bool update = false;
        for (int i = 0; i < E; i++) {
            Edge e = edges[i];
            if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.cost) {
                dist[e.to] = dist[e.from] + e.cost;
                update = true;
            }
        }

        if (!update) break;
    }
    return dist;
}

/**
 * 負の閉路があるか調べる
 * @order O(|V| * |E|)
 * Bellman-Ford法を拡張して負の閉路の存在を調べる
 **/
bool has_negative_loop(vector<Edge> edges, int V) {
    vector<int> dist(V);
    int E = edges.size();
    for (int i = 0; i < V; i++) dist[i] = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < E; j++) {
            Edge e = edges[j];
            if (dist[e.to] > dist[e.from] + e.cost) {
                dist[e.to] = dist[e.from] + e.cost;
                if (i == V - 1) return true;
            }
        }
    }
    return false;
}

/**
 * Dijkstra
 * @param vector<vector<Edge> > edges は各頂点からの辺
 * @order O(|E| log |V|)
 * ヒープで実装
 */
vector<int> dijkstra(vector<vector<Edge> > G, int V, int s) {
    priority_queue<ii, vector<ii>, greater<ii> > que; // (min cost, index)
    vector<int> dist(V);
    for (int i = 0; i < V; ++i) {
        dist[i] = INF;
    }
    dist[s] = 0;
    que.push(ii(0, s));

    while(!que.empty()) {
        ii dv = que.top(); que.pop();
        int v = dv.second;
        if (dist[v] < dv.first) continue;

        for (int i = 0; i < G[v].size(); i++) {
            Edge e = G[v][i];
            if (dist[e.to] > dist[v] + e.cost) {
                dist[e.to] = dist[v] + e.cost;
                que.push(ii(dist[e.to], e.to));
            }
        }
    }

    return dist;
}

/**
 * warshall-floyd閉路チェック
 * @order O(|V|^3)
 * d[i][i] < 0 => 閉路
 */
void warshall_floyd(int *(*d), int V) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}


int main() {

    vector<Edge> edges = {
        Edge{0, 1, 4},
        Edge{0, 2, 15},
        Edge{1, 2, 6},
        Edge{1, 3, 11},
        Edge{2, 4, 13}
    };
    assert(vector_check(bellman_ford(edges, 5, 0), {0, 4, 10, 15, 23}));
    assert(vector_check(bellman_ford(edges, 5, 2), {INF,INF, 0, INF, 13}));
    cout << "Bellman-Ford: PASS" << endl;
    assert(!has_negative_loop(edges, 5));
    edges.push_back(Edge{4, 0, -1});
    assert(!has_negative_loop(edges, 5));
    edges.push_back(Edge{4, 0, -30});
    assert(has_negative_loop(edges, 5));
    cout << "negative-loop check:PASS" << endl;

    vector<Edge> edges_ = {
        Edge{0, 2, 2},
        Edge{0, 1, 5},
        Edge{1, 2, 4},
        Edge{1, 3, 2},
        Edge{2, 3, 6},
        Edge{2, 4, 10},
        Edge{3, 4, 1}
    };
    vector<vector<Edge> > G(5);
    for (int i = 0; i < edges_.size(); i++) {
        G[edges_[i].from].push_back(edges_[i]);
    }
    assert(vector_check(dijkstra(G, 5, 0), {0, 5, 2, 7, 8}));
    cout << "Dijkstra: PASS" << endl;
    return 0;
}
