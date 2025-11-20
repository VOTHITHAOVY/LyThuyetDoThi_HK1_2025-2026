#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<vector<int>> adj(n + 1);

    for (int i = 1; i <= n; i++) {
        int j;
        while (cin >> j && j != -1) {
            adj[i].push_back(j);
        }
    }

    vector<bool> visited(n + 1, false);
    vector<int> result;
    queue<int> q;

    visited[x] = true;
    q.push(x);
    result.push_back(x);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                result.push_back(v);
            }
        }
    }

    cout << result.size() << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }

    return 0;
}