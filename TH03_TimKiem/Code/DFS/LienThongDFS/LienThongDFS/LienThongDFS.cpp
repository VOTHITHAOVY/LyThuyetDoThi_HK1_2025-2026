#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// DFS không đệ quy
vector<int> dfs_non_recursive(vector<vector<int>>& adj, int start, int n) {
    vector<bool> visited(n + 1, false);
    vector<int> result;
    stack<int> st;

    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        result.push_back(u);

        // Duyệt theo thứ tự ngược để giống DFS đệ quy
        for (int i = adj[u].size() - 1; i >= 0; i--) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
            }
        }
    }

    return result;
}

// DFS đệ quy
void dfs_recursive(vector<vector<int>>& adj, vector<bool>& visited, vector<int>& result, int u) {
    visited[u] = true;
    result.push_back(u);

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs_recursive(adj, visited, result, v);
        }
    }
}

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

    // Sử dụng DFS không đệ quy
    vector<int> result = dfs_non_recursive(adj, x, n);
    sort(result.begin(), result.end());

    cout << result.size() << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }

    return 0;
}