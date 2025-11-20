#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int n, x, y;
    cin >> n >> x >> y;

    vector<vector<int>> adj(n + 1);

    for (int i = 1; i <= n; i++) {
        int j;
        while (cin >> j && j != -1) {
            adj[i].push_back(j);
        }
    }

    vector<bool> visited(n + 1, false);
    vector<int> parent(n + 1, -1);
    queue<int> q;

    visited[x] = true;
    q.push(x);
    parent[x] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == y) break;

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    vector<int> path;
    for (int u = y; u != -1; u = parent[u]) {
        path.push_back(u);
    }
    reverse(path.begin(), path.end());

    cout << path.size() << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " ";
    }

    return 0;
}