#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Edge {
    int u, v, w, id;
};

// Kiểm tra cầu bằng DFS
bool is_bridge(int n, const vector<Edge>& edges, int exclude) {
    vector<vector<int>> adj(n);
    for (const Edge& e : edges) {
        if (e.id == exclude) continue;
        adj[e.u].push_back(e.v);
        adj[e.v].push_back(e.u);
    }

    int u = edges[exclude].u, v = edges[exclude].v;
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(u);
    visited[u] = true;

    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : adj[x]) {
            if (!visited[y]) {
                visited[y] = true;
                q.push(y);
            }
        }
    }
    return !visited[v];
}

// Kiểm tra có đường đi toàn cạnh < w hay không
bool exists_path_with_max_less_than(int n, const vector<Edge>& edges, int u, int v, int w, int exclude) {
    vector<vector<int>> adj(n);
    for (const Edge& e : edges) {
        if (e.id == exclude) continue;
        if (e.w < w) { // Chỉ giữ cạnh có trọng số < w
            adj[e.u].push_back(e.v);
            adj[e.v].push_back(e.u);
        }
    }

    vector<bool> visited(n, false);
    queue<int> q;
    q.push(u);
    visited[u] = true;

    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (x == v) return true;
        for (int y : adj[x]) {
            if (!visited[y]) {
                visited[y] = true;
                q.push(y);
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<Edge> edges(M);
        for (int i = 0; i < M; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
            edges[i].u--; edges[i].v--; // Chuyển về 0-based
            edges[i].id = i;
        }

        while (Q--) {
            int k, s;
            cin >> k >> s;
            k--;

            vector<Edge> modified_edges = edges;
            for (int i = 0; i < s; i++) {
                int t, c;
                cin >> t >> c;
                t--;
                modified_edges[t].w = c;
            }

            Edge e = modified_edges[k];

            // Kiểm tra cầu
            if (is_bridge(N, modified_edges, k)) {
                cout << "NO\n";
                continue;
            }

            // Kiểm tra có đường đi toàn cạnh < w(e) hay không
            if (exists_path_with_max_less_than(N, modified_edges, e.u, e.v, e.w, k)) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}