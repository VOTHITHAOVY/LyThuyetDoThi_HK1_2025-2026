#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<pair<int, int>> dfs_spanning_tree(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n + 1, false);
    vector<pair<int, int>> spanning_tree;
    stack<int> st;

    st.push(1);
    visited[1] = true;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                spanning_tree.push_back({ u, v });
                st.push(v);
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

    vector<pair<int, int>> tree = dfs_spanning_tree(n, adj);

    cout << tree.size() << endl;
    for (auto edge : tree) {
        cout << edge.first << " " << edge.second << endl;
    }

    return 0;
}