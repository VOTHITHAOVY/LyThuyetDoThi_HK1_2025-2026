#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAX_N = 7;

vector<int> findEulerCycle(vector<vector<int>>& adj) {
    vector<int> circuit;
    stack<int> st;

    int start = 0;
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            if (adj[i][j] > 0) {
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
        for (int v = 0; v < MAX_N; v++) {
            if (adj[u][v] > 0) {
                st.push(v);
                adj[u][v]--;
                adj[v][u]--;
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

bool isEulerian(vector<vector<int>>& adj, vector<int>& degree) {
    for (int i = 0; i < MAX_N; i++) {
        if (degree[i] % 2 != 0) {
            return false;
        }
    }

    vector<bool> visited(MAX_N, false);
    stack<int> st;

    int start = -1;
    for (int i = 0; i < MAX_N; i++) {
        if (degree[i] > 0) {
            start = i;
            break;
        }
    }

    if (start == -1) return false;

    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        for (int v = 0; v < MAX_N; v++) {
            if (adj[u][v] > 0 && !visited[v]) {
                visited[v] = true;
                st.push(v);
            }
        }
    }

    for (int i = 0; i < MAX_N; i++) {
        if (degree[i] > 0 && !visited[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(MAX_N, vector<int>(MAX_N, 0));
    vector<int> degree(MAX_N, 0);

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x][y]++;
        adj[y][x]++;
        degree[x]++;
        degree[y]++;
    }

    // Kiểm tra điều kiện Euler
    if (!isEulerian(adj, degree)) {
        cout << 0 << endl;
        return 0;
    }

    // Tìm chu trình Euler
    vector<int> eulerCycle = findEulerCycle(adj);

    // In kết quả
    cout << 1 << endl;
    for (int i = 0; i < eulerCycle.size() - 1; i++) {
        cout << eulerCycle[i] << " " << eulerCycle[i + 1] << endl;
    }

    return 0;
}