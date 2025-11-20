#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Circle {
    double x, y, r;
};

struct Edge {
    int to;
    int jumps;
    int circles;
};

struct State {
    int node;
    int total_jumps;
    int total_circles;

    bool operator>(const State& other) const {
        if (total_jumps != other.total_jumps)
            return total_jumps > other.total_jumps;
        return total_circles > other.total_circles;
    }
};

double circleDistance(const Circle& c1, const Circle& c2) {
    double dx = c2.x - c1.x;
    double dy = c2.y - c1.y;
    double d = sqrt(dx * dx + dy * dy);
    return max(0.0, d - c1.r - c2.r);
}

void solveCircleProblem() {
    int n, s, t;
    cin >> n >> s >> t;
    s--; t--;

    vector<Circle> circles(n);
    for (int i = 0; i < n; i++) {
        cin >> circles[i].x >> circles[i].y >> circles[i].r;
    }

    // Xây dựng đồ thị
    vector<vector<Edge>> graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = circleDistance(circles[i], circles[j]);

            if (dist <= 60.0) {
                int jumps = (dist > 50.0) ? 1 : 0;
                int circle_count = 1;

                graph[i].push_back({ j, jumps, circle_count });
                graph[j].push_back({ i, jumps, circle_count });
            }
        }
    }

    // Dijkstra với trọng số kép
    const int INF = 1e9;
    vector<pair<int, int>> dist(n, { INF, INF });
    vector<int> parent(n, -1);

    dist[s] = { 0, 0 };
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({ s, 0, 0 });

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int u = current.node;
        int jumps_u = current.total_jumps;
        int circles_u = current.total_circles;

        if (jumps_u != dist[u].first || circles_u != dist[u].second)
            continue;

        if (u == t) break;

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int new_jumps = jumps_u + edge.jumps;
            int new_circles = circles_u + edge.circles;

            if (make_pair(new_jumps, new_circles) < dist[v]) {
                dist[v] = { new_jumps, new_circles };
                parent[v] = u;
                pq.push({ v, new_jumps, new_circles });
            }
        }
    }

    // Kiểm tra kết quả
    if (dist[t].first == INF) {
        cout << 0 << endl;
    }
    else {
        cout << 1 << endl;
        cout << dist[t].first << " " << dist[t].second + 1 << endl;

        // Truy vết đường đi
        vector<int> path;
        int current = t;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());

        // In đường đi với loại bước
        for (int i = 0; i < path.size(); i++) {
            int node = path[i] + 1;
            if (i == 0) {
                cout << node << " 0" << endl;
            }
            else {
                int u = path[i - 1], v = path[i];
                double dist_uv = circleDistance(circles[u], circles[v]);
                int step_type = (dist_uv > 50.0) ? 1 : 0;
                cout << node << " " << step_type << endl;
            }
        }
    }
}

int main() {
    solveCircleProblem();
    return 0;
}