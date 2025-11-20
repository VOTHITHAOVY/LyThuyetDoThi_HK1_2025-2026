#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct Edge {
    int v, w;
};

struct Node {
    int dist, u, parent;
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};

vector<pair<int, int>> prim(int n, vector<vector<Edge>>& adj) {
    vector<int> dist(n + 1, numeric_limits<int>::max());
    vector<int> parent(n + 1, -1);
    vector<bool> visited(n + 1, false);
    vector<pair<int, int>> mst;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[1] = 0;
    pq.push({ 0, 1, -1 });

    while (!pq.empty()) {
        int u = pq.top().u;
        int p = pq.top().parent;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        if (p != -1) {
            mst.push_back({ p, u });
        }

        for (Edge edge : adj[u]) {
            int v = edge.v;
            int w = edge.w;

            if (!visited[v] && w < dist[v]) {
                dist[v] = w;
                parent[v] = u;
                pq.push({ w, v, u });
            }
        }
    }

    return mst;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }

    vector<pair<int, int>> mst_edges = prim(n, adj);

    // Tính tổng trọng số
    int total_weight = 0;
    vector<vector<int>> adj_temp(n + 1);
    for (auto edge : mst_edges) {
        int u = edge.first, v = edge.second;
        for (Edge e : adj[u]) {
            if (e.v == v) {
                total_weight += e.w;
                break;
            }
        }
    }

    cout << mst_edges.size() << " " << total_weight << endl;
    for (auto edge : mst_edges) {
        int u = edge.first, v = edge.second;
        for (Edge e : adj[u]) {
            if (e.v == v) {
                cout << u << " " << v << " " << e.w << endl;
                break;
            }
        }
    }

    return 0;
}