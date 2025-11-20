#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> findEulerPath(vector<vector<int>>& adj, int n, int start) {
    vector<int> path;
    stack<int> st;

    vector<vector<int>> tempAdj = adj;

    st.push(start);

    while (!st.empty()) {
        int u = st.top();

        bool found = false;
        for (int v = 0; v < n; v++) {
            if (tempAdj[u][v] > 0) {
                st.push(v);
                tempAdj[u][v]--;
                tempAdj[v][u]--;
                found = true;
                break;
            }
        }

        if (!found) {
            path.push_back(u);
            st.pop();
        }
    }

    return path;
}

bool isConnected(vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false);
    int start = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] > 0) {
                start = i;
                break;
            }
        }
        if (start != -1) break;
    }

    if (start == -1) return true;

    stack<int> st;
    st.push(start);
    visited[start] = true;
    int count = 1;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        for (int v = 0; v < n; v++) {
            if (adj[u][v] > 0 && !visited[v]) {
                visited[v] = true;
                st.push(v);
                count++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        bool hasEdge = false;
        for (int j = 0; j < n; j++) {
            if (adj[i][j] > 0) {
                hasEdge = true;
                break;
            }
        }
        if (hasEdge && !visited[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n, vector<int>(n));
    vector<int> degree(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
            degree[i] += adj[i][j];
        }
    }

    if (!isConnected(adj, n)) {
        cout << 0 << endl;
        return 0;
    }

    // Đếm số đỉnh bậc lẻ
    vector<int> oddVertices;
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 != 0) {
            oddVertices.push_back(i);
        }
    }

    // Kiểm tra điều kiện nửa Euler
    if (oddVertices.size() != 0 && oddVertices.size() != 2) {
        cout << 0 << endl;
        return 0;
    }

    // Tìm đường đi Euler
    int startVertex = 0;
    if (oddVertices.size() == 2) {
        startVertex = oddVertices[0];
    }

    vector<int> eulerPath = findEulerPath(adj, n, startVertex);

    // Kiểm tra đường đi có đủ cạnh không
    int edgeCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edgeCount += adj[i][j];
        }
    }

    if (eulerPath.size() != edgeCount + 1) {
        cout << 0 << endl;
        return 0;
    }

    cout << 1 << endl;
    for (int i = 0; i < eulerPath.size(); i++) {
        cout << eulerPath[i] + 1 << " ";
    }
    cout << endl;

    return 0;
}