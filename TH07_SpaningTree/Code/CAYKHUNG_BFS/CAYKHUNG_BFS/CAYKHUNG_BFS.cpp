#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<pair<int, int>> bfs_spanning_tree(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n + 1, false);
    vector<pair<int, int>> spanning_tree;
    queue<int> q;

    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                spanning_tree.push_back({ u, v });
                q.push(v);
            }
        }
    }

    return spanning_tree;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<pair<int, int>> tree = bfs_spanning_tree(n, adj);

    cout << tree.size() << endl;
    for (auto edge : tree) {
        cout << edge.first << " " << edge.second << endl;
    }

    return 0;
}