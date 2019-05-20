#include "common.h"
#include <cassert>

#define INF 1000000007

struct Edge {
    int from, to, cost;
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
    return 0;
}
