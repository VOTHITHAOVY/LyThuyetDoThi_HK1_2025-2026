#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = 1e9; // Giá trị vô cùng

void floydWarshall(int n, vector<vector<int>>& dist) {
    // Thuật toán Floyd-Warshall
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // Nếu cả hai đường i->k và k->j đều tồn tại
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Khởi tạo ma trận khoảng cách
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

    // Khoảng cách từ đỉnh tới chính nó = 0
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }

    // Đọc các cạnh
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // Đồ thị vô hướng nên cạnh hai chiều
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    // Chạy thuật toán Floyd-Warshall
    floydWarshall(n, dist);

    // In kết quả
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << dist[i][j];
            if (j < n) cout << " ";
        }
        cout << endl;
    }

    return 0;
}