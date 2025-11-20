#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<int> dfs_path(vector<vector<int>>& adj, int start, int end, int n) {
    vector<bool> visited(n + 1, false);
    vector<int> parent(n + 1, -1);
    stack<int> st;

    st.push(start);
    visited[start] = true;
    parent[start] = -1;

    bool found = false;

    while (!st.empty() && !found) {
        int u = st.top();
        st.pop();

        if (u == end) {
            found = true;
            break;
        }

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                st.push(v);

                if (v == end) {
                    found = true;
                    break;
                }
            }
        }
    }

    vector<int> path;
    if (found) {
        for (int u = end; u != -1; u = parent[u]) {
            path.push_back(u);
        }
        reverse(path.begin(), path.end());
    }

    return path;
}

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

    vector<int> path = dfs_path(adj, x, y, n);

    if (!path.empty()) {
        cout << path.size() << endl;
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << " ";
        }
    }
    else {
        cout << "0" << endl;
    }

    return 0;
}