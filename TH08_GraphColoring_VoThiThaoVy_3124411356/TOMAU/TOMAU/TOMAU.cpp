#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    cout << "Input:" << endl;
    int n, m;
    cin >> n >> m;

    vector<int> adj[1001];
    int degree[1001] = { 0 };

    // Đọc dữ liệu và xây dựng đồ thị
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    // Tạo danh sách đỉnh và sắp xếp theo bậc giảm dần
    vector<pair<int, int>> nodes;
    for (int i = 1; i <= n; i++) {
        nodes.push_back({ i, degree[i] });
    }

    // Sắp xếp theo bậc giảm dần
    sort(nodes.begin(), nodes.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
        });

    int color[1001] = { 0 };
    int max_color = 0;

    // Tô màu các đỉnh
    for (auto& node : nodes) {
        int u = node.first;
        bool used[1001] = { false };

        // Đánh dấu các màu đã dùng bởi đỉnh kề
        for (int v : adj[u]) {
            if (color[v] != 0) {
                used[color[v]] = true;
            }
        }

        // Tìm màu nhỏ nhất chưa dùng
        int c = 1;
        while (used[c]) {
            c++;
        }

        color[u] = c;
        if (c > max_color) {
            max_color = c;
        }
    }

    // In kết quả
    cout << "Output:" << endl;
    cout << max_color << endl;
    for (int c = 1; c <= max_color; c++) {
        for (int i = 1; i <= n; i++) {
            if (color[i] == c) {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    return 0;
}