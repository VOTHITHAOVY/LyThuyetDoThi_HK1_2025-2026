#include <iostream>
#include <vector>
using namespace std;

bool hamiltonCycleUtil(vector<vector<int>>& adj, vector<int>& path, vector<bool>& visited, int pos, int n) {
    // Nếu đã đi qua tất cả đỉnh
    if (pos == n) {
        // Kiểm tra có cạnh từ đỉnh cuối về đỉnh đầu không
        if (adj[path[pos - 1]][path[0]] == 1) {
            return true;
        }
        return false;
    }

    // Thử các đỉnh kế tiếp
    for (int v = 0; v < n; v++) {
        // Kiểm tra đỉnh v có kề với đỉnh trước và chưa thăm
        if (adj[path[pos - 1]][v] == 1 && !visited[v]) {
            visited[v] = true;
            path[pos] = v;

            if (hamiltonCycleUtil(adj, path, visited, pos + 1, n)) {
                return true;
            }

            // Quay lui
            visited[v] = false;
            path[pos] = -1;
        }
    }

    return false;
}

bool findHamiltonCycle(vector<vector<int>>& adj, int n, vector<int>& cycle) {
    vector<int> path(n, -1);
    vector<bool> visited(n, false);

    // Bắt đầu từ đỉnh 0
    path[0] = 0;
    visited[0] = true;

    if (!hamiltonCycleUtil(adj, path, visited, 1, n)) {
        return false;
    }

    cycle = path;
    cycle.push_back(0); // Thêm đỉnh đầu để khép kín chu trình
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

    vector<int> hamiltonCycle;
    if (findHamiltonCycle(adj, n, hamiltonCycle)) {
        cout << 1 << endl;
        for (int i = 0; i < hamiltonCycle.size(); i++) {
            cout << hamiltonCycle[i] + 1 << " ";
        }
        cout << endl;
    }
    else {
        cout << 0 << endl;
    }

    return 0;
}