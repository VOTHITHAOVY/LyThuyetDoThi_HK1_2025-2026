#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Hàm thực hiện thuật toán Dijkstra
vector<int> dijkstra(int start, int n, const vector<vector<pair<int, int>>>& graph, vector<int>& parent) {
    vector<int> dist(n + 1, INF);
    dist[start] = 0;
    parent[start] = -1;

    // Hàng đợi ưu tiên: (khoảng cách, đỉnh)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Nếu đã có đường đi tốt hơn, bỏ qua
        if (current_dist > dist[u]) continue;

        // Duyệt các đỉnh kề
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Bước relaxation
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    return dist;
}

// Hàm truy vết đường đi
vector<int> reconstructPath(int start, int end, const vector<int>& parent) {
    vector<int> path;

    // Truy vết từ end về start
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }

    // Đảo ngược để có đường đi từ start đến end
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, t, x;
    cin >> n >> m >> s >> t >> x;

    // Danh sách kề: graph[u] = danh sách (v, trọng số)
    vector<vector<pair<int, int>>> graph(n + 1);
    vector<int> parent_s(n + 1, -1);  // parent cho đường từ s
    vector<int> parent_x(n + 1, -1);  // parent cho đường từ x

    // Đọc các cung
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({ v, w });
    }

    // Chạy Dijkstra từ s
    vector<int> dist_from_s = dijkstra(s, n, graph, parent_s);

    // Chạy Dijkstra từ x
    vector<int> dist_from_x = dijkstra(x, n, graph, parent_x);

    // Kiểm tra xem có đường đi từ s đến x và từ x đến t không
    if (dist_from_s[x] == INF || dist_from_x[t] == INF) {
        cout << "Khong co duong di tu " << s << " den " << t << " qua " << x << endl;
    }
    else {
        // Tính tổng độ dài
        int total_distance = dist_from_s[x] + dist_from_x[t];

        // Truy vết đường đi
        vector<int> path_s_to_x = reconstructPath(s, x, parent_s);
        vector<int> path_x_to_t = reconstructPath(x, t, parent_x);

        // Ghép đường đi (bỏ đỉnh x trùng lặp)
        vector<int> full_path = path_s_to_x;
        full_path.insert(full_path.end(), path_x_to_t.begin() + 1, path_x_to_t.end());

        // Xuất kết quả
        cout << full_path.size() << " " << total_distance << endl;
        for (size_t i = 0; i < full_path.size(); i++) {
            cout << full_path[i];
            if (i != full_path.size() - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
