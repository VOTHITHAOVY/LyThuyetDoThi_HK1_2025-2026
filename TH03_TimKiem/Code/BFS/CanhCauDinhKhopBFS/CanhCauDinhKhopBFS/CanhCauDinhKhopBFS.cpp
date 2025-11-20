#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int countComponents(vector<vector<int>> adj, int n) {
    vector<bool> visited(n + 1, false);
    int count = 0;

    for (int i = 1; i <= n; i++) {
        if (!visited[i] && !adj[i].empty()) {
            queue<int> q;
            visited[i] = true;
            q.push(i);
            count++;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    int n, x, y, z;
    cin >> n >> x >> y >> z;

    vector<vector<int>> original_adj(n + 1);

    for (int i = 1; i <= n; i++) {
        int j;
        while (cin >> j && j != -1) {
            original_adj[i].push_back(j);
        }
    }

    // Kiểm tra cạnh cầu
    vector<vector<int>> temp_adj = original_adj;

    // Xóa cạnh (x,y)
    auto it1 = find(temp_adj[x].begin(), temp_adj[x].end(), y);
    if (it1 != temp_adj[x].end()) temp_adj[x].erase(it1);

    auto it2 = find(temp_adj[y].begin(), temp_adj[y].end(), x);
    if (it2 != temp_adj[y].end()) temp_adj[y].erase(it2);

    int original_components = countComponents(original_adj, n);
    int new_components = countComponents(temp_adj, n);

    if (new_components > original_components) {
        cout << "canh cau" << endl;
    }
    else {
        cout << "khong la canh cau" << endl;
    }

    // Kiểm tra đỉnh khớp
    temp_adj = original_adj;

    // Xóa đỉnh z
    temp_adj[z].clear();
    for (int i = 1; i <= n; i++) {
        if (i != z) {
            auto it = find(temp_adj[i].begin(), temp_adj[i].end(), z);
            if (it != temp_adj[i].end()) temp_adj[i].erase(it);
        }
    }

    new_components = countComponents(temp_adj, n);

    if (new_components > original_components) {
        cout << "dinh khop" << endl;
    }
    else {
        cout << "khong la dinh khop" << endl;
    }

    return 0;
}