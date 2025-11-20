#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;

vector<int> findEulerCycleAdjList(vector<vector<int>>& adjList) {
    int n = adjList.size();
    vector<int> circuit;

    if (n == 0) return circuit;

    // Tạo danh sách kề có thể xóa phần tử
    vector<list<int>> tempAdj(n);
    for (int i = 0; i < n; i++) {
        tempAdj[i] = list<int>(adjList[i].begin(), adjList[i].end());
    }

    stack<int> st;

    // Tìm đỉnh đầu tiên có cạnh
    int start = 0;
    for (int i = 0; i < n; i++) {
        if (!tempAdj[i].empty()) {
            start = i;
            break;
        }
    }

    st.push(start);

    while (!st.empty()) {
        int u = st.top();

        if (!tempAdj[u].empty()) {
            // Lấy đỉnh kề đầu tiên
            int v = tempAdj[u].front();

            // Xóa cạnh u-v
            tempAdj[u].pop_front();
            // Xóa cạnh v-u (cần tìm và xóa)
            for (auto it = tempAdj[v].begin(); it != tempAdj[v].end(); ++it) {
                if (*it == u) {
                    tempAdj[v].erase(it);
                    break;
                }
            }

            st.push(v);
        }
        else {
            // Không còn cạnh từ u
            circuit.push_back(u);
            st.pop();
        }
    }

    reverse(circuit.begin(), circuit.end());
    return circuit;
}

bool isEulerianAdjList(vector<vector<int>>& adjList) {
    int n = adjList.size();

    // Kiểm tra bậc chẵn
    for (int i = 0; i < n; i++) {
        if (adjList[i].size() % 2 != 0) {
            return false;
        }
    }

    // Kiểm tra liên thông (BFS)
    vector<bool> visited(n, false);
    stack<int> st;

    int start = -1;
    for (int i = 0; i < n; i++) {
        if (!adjList[i].empty()) {
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

        for (int v : adjList[u]) {
            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
            }
        }
    }

    // Kiểm tra tất cả đỉnh có cạnh đều được visited
    for (int i = 0; i < n; i++) {
        if (!adjList[i].empty() && !visited[i]) {
            return false;
        }
    }

    return true;
}

// Hàm chuyển từ ma trận kề sang danh sách kề
vector<vector<int>> convertToAdjList(vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> adjList(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] > 0) {
                adjList[i].push_back(j);
            }
        }
    }

    return adjList;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adjMatrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adjMatrix[i][j];
        }
    }

    // Chuyển sang danh sách kề
    vector<vector<int>> adjList = convertToAdjList(adjMatrix);

    if (!isEulerianAdjList(adjList)) {
        cout << "0" << endl;
        return 0;
    }

    vector<int> eulerCycle = findEulerCycleAdjList(adjList);

    cout << "1" << endl;
    for (int vertex : eulerCycle) {
        cout << vertex + 1 << " ";
    }
    cout << endl;

    return 0;
}