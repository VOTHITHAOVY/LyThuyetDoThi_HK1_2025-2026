#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    cout << "Inputl:" << endl;
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    // Đọc danh sách bạn bè
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> color(n + 1, 0); // 0: chưa tô, 1: đội 1, 2: đội 2
    bool isPossible = true;

    // Duyệt qua tất cả các đỉnh (xử lý đồ thị không liên thông)
    for (int i = 1; i <= n && isPossible; i++) {
        if (color[i] == 0) {
            // BFS từ đỉnh i
            queue<int> q;
            q.push(i);
            color[i] = 1; // Bắt đầu với màu 1

            while (!q.empty() && isPossible) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (color[v] == 0) {
                        // Tô màu đối lập với u
                        color[v] = 3 - color[u];
                        q.push(v);
                    }
                    else if (color[v] == color[u]) {
                        // Xung đột: hai đỉnh kề cùng màu
                        isPossible = false;
                        break;
                    }
                }
            }
        }
    }

    // Xuất kết quả
    cout << "Output:" << endl;
    if (!isPossible) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        for (int i = 1; i <= n; i++) {
            cout << color[i] << " ";
        }
        cout << endl;
    }

    return 0;
}