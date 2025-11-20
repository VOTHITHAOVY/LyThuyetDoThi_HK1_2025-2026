#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    int n, m, xi, yi, xj, yj;
    cin >> n >> m >> xi >> yi >> xj >> yj;
    xi--; yi--; xj--; yj--;

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    // Kiểm tra ô bắt đầu và kết thúc
    if (grid[xi][yi] == 0 || grid[xj][yj] == 0) {
        cout << 0 << endl;
        return 0;
    }

    // 4 hướng di chuyển
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { 1, 0, -1, 0 };

    // Khởi tạo khoảng cách và parent
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, { -1, -1 }));

    dist[xi][yi] = 0;

    // Priority queue: (cost, x, y)
    priority_queue<pair<int, pair<int, int>>,
        vector<pair<int, pair<int, int>>>,
        greater<pair<int, pair<int, int>>>> pq;

    pq.push({ 0, {xi, yi} });

    while (!pq.empty()) {
        int cost = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        if (cost > dist[x][y]) continue;

        if (x == xj && y == yj) break;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (grid[nx][ny] == 0) continue;

            int new_cost = cost;
            // Không tính chi phí cho ô start
            if (!(nx == xi && ny == yi)) {
                new_cost += grid[nx][ny];
            }

            // Nếu là ô end, chỉ cập nhật khoảng cách
            if (nx == xj && ny == yj) {
                if (new_cost < dist[nx][ny]) {
                    dist[nx][ny] = new_cost;
                    parent[nx][ny] = { x, y };
                }
            }
            // Nếu không phải ô end, push vào queue
            else if (new_cost < dist[nx][ny]) {
                dist[nx][ny] = new_cost;
                parent[nx][ny] = { x, y };
                pq.push({ new_cost, {nx, ny} });
            }
        }
    }

    if (dist[xj][yj] == INT_MAX) {
        cout << 0 << endl;
    }
    else {
        cout << 1 << endl;
        cout << dist[xj][yj] << endl;

        // Truy vết đường đi
        vector<pair<int, int>> path;
        int x = xj, y = yj;

        while (x != -1 && y != -1) {
            path.push_back({ x + 1, y + 1 });
            int prev_x = parent[x][y].first;
            int prev_y = parent[x][y].second;
            x = prev_x;
            y = prev_y;
        }
        reverse(path.begin(), path.end());

        for (auto p : path) {
            cout << p.first << " " << p.second << endl;
        }
    }

    return 0;
}