#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<int> findEulerCycleNonRecursive(vector<vector<int>>& adj, int n) {
    vector<int> circuit;
    stack<int> st;

    // Tạo bản sao ma trận kề
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
        // Tìm đỉnh kề đầu tiên
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

    // Đảo ngược để có thứ tự đúng
    reverse(circuit.begin(), circuit.end());
    return circuit;
}

bool isEulerian(vector<vector<int>>& adj, int n) {
    vector<int> degree(n, 0);

    // Tính bậc các đỉnh
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            degree[i] += adj[i][j];
        }
    }

    // Kiểm tra tất cả bậc chẵn
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 != 0) {
            return false;
        }
    }

    // Kiểm tra liên thông
    vector<bool> visited(n, false);
    stack<int> st;

    int start = -1;
    for (int i = 0; i < n; i++) {
        if (degree[i] > 0) {
            start = i;
            break;
        }
    }

    if (start == -1) return true; // đồ thị rỗng

    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        for (int v = 0; v < n; v++) {
            if (adj[u][v] > 0 && !visited[v]) {
                visited[v] = true;
                st.push(v);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (degree[i] > 0 && !visited[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    if (!isEulerian(adj, n)) {
        cout << "0" << endl;
        return 0;
    }

    vector<int> eulerCycle = findEulerCycleNonRecursive(adj, n);

    cout << "1" << endl;
    for (int vertex : eulerCycle) {
        cout << vertex + 1 << " ";
    }
    cout << endl;

    return 0;
}