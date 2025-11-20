#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> findEulerCycle(vector<vector<int>>& adj, int n) {
    vector<int> circuit;
    stack<int> st;

    // Tạo bản sao ma trận kề để thao tác
    vector<vector<int>> tempAdj = adj;

    // Tìm đỉnh đầu tiên có cạnh
    int start = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tempAdj[i][j] > 0) {
                start = i;
                break;
            }
        }
        if (start != 0) break;
    }

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
            circuit.push_back(u);
            st.pop();
        }
    }

    return circuit;
}

bool isConnected(vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false);
    int start = -1;

    // Tìm đỉnh đầu tiên có cạnh
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] > 0) {
                start = i;
                break;
            }
        }
        if (start != -1) break;
    }

    if (start == -1) return true; // đồ thị rỗng

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

    // Kiểm tra tất cả đỉnh có cạnh đều được visited
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

    // Đọc ma trận kề và tính bậc
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
            degree[i] += adj[i][j];
        }
    }

    // Kiểm tra bậc chẵn
    bool allEven = true;
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 != 0) {
            allEven = false;
            break;
        }
    }

    // Kiểm tra liên thông
    bool connected = isConnected(adj, n);

    if (!allEven || !connected) {
        cout << 0 << endl;
        return 0;
    }

    // Tìm chu trình Euler
    vector<int> eulerCycle = findEulerCycle(adj, n);

    // Kiểm tra chu trình có hợp lệ (số đỉnh = số cạnh + 1)
    int edgeCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edgeCount += adj[i][j];
        }
    }

    if (eulerCycle.size() != edgeCount + 1) {
        cout << 0 << endl;
        return 0;
    }

    // In kết quả
    cout << 1 << endl;
    for (int i = 0; i < eulerCycle.size(); i++) {
        cout << eulerCycle[i] + 1 << " ";
    }
    cout << endl;

    return 0;
}