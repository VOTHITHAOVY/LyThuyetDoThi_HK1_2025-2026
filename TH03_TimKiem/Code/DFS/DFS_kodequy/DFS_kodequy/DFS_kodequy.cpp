#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
private:
    int n;
    vector<vector<int>> adj;

public:
    Graph(int n) : n(n), adj(n + 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Đồ thị vô hướng
    }

    // DFS không đệ quy
    vector<int> dfs_non_recursive(int start) {
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

    // DFS không đệ quy với parent (dùng cho tìm đường đi)
    vector<int> dfs_path_non_recursive(int start, int end) {
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
};

int main() {
    int n = 8;
    Graph g(n);

    // Thêm các cạnh của đồ thị
    g.addEdge(1, 2);
    g.addEdge(2, 5);
    g.addEdge(2, 4);
    g.addEdge(3, 7);
    g.addEdge(4, 8);
    g.addEdge(7, 2);

    cout << "DFS khong de quy tu dinh  7: ";
    vector<int> dfs_result = g.dfs_non_recursive(7);
    for (int node : dfs_result) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Duong di tu 3 den 8: ";
    vector<int> path = g.dfs_path_non_recursive(3, 8);
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}