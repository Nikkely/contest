#include "common.h"
#include <cassert>

class NetworkFlow {
protected:
    const static int MAX_V = 10000;
private:
    struct edge {
        int to, cap, rev;
    };
    vector<edge> G[MAX_V];
    bool used[MAX_V];
public:
    void add_edge(int from, int to, int cap) {
        G[from].push_back((edge){to, cap, (int)G[to].size()});
        G[to].push_back((edge){from, 0, (int)G[from].size() - 1});
    }

    // vからtへfだけ流し、流した量を返す
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        used[v] = true;
        for (int i = 0; i < G[v].size(); i++) {
            edge &e = G[v][i];
            if (!used[e.to] && e.cap > 0) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int max_flow(int s, int t) {
        int flow = 0;
        while (1) {
            memset(used, 0, sizeof(used));
            int f = dfs(s, t, 1000000007);
            if (f == 0) return flow;
            flow += f;
        }
    }
};

class BipartiteMaching : public NetworkFlow { // ?
private:
    vector<int> G[MAX_V];
    int match[MAX_V];
    bool used[MAX_V];
public:
    int V;
    void add_edge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void add_edge(int from, int to, int cap) {
        add_edge(from, to);
    }

    int dfs(int v) {
        used[v] = true;
        for(int i = 0; i < G[v].size(); i++) {
            int u = G[v][i], w = match[u];
            if (w < 0 || (!used[w] && dfs(w))) {
                match[v] = u;
                match[u] = v;
                return 1;
            }
        }
        return 0;
    }
    int dfs(int v, int t, int f) {
        return dfs(v);
    }

    int max_flow(int s, int t) {
        int ret = 0;
        memset(match, -1, sizeof(match));
        for (int v = 0; v < V; v++) {
            if (match[v] < 0) {
                memset(used, 0, sizeof(used));
                if (dfs(v)) {
                    ret++;
                }
            }
        }
        return ret;
    }
};
