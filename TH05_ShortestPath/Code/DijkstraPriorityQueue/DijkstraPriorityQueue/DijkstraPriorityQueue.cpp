#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<int> dijkstra(int start, int n, vector<vector<pair<int, int>>>& graph, vector<int>& parent) {
    vector<int> dist(n + 1, INF);
    dist[start] = 0;
    parent[start] = -1;

    // Priority queue: (distance, vertex) - min-heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // If we have already found a better path, skip
        if (current_dist > dist[u]) continue;

        // Check all neighbors
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Relaxation step
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    return dist;
}

vector<int> reconstructPath(int start, int end, vector<int>& parent) {
    vector<int> path;

    // Trace back from end to start
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }

    // Reverse to get path from start to end
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    // Adjacency list: graph[u] = list of (v, weight)
    vector<vector<pair<int, int>>> graph(n + 1);
    vector<int> parent(n + 1, -1);

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({ v, w });
    }

    // Run Dijkstra's algorithm with priority queue
    vector<int> dist = dijkstra(s, n, graph, parent);

    // Check if path exists
    if (dist[t] == INF) {
        cout << "Khong co duong di tu " << s << " den " << t << endl;
    }
    else {
        // Reconstruct path
        vector<int> path = reconstructPath(s, t, parent);

        // Output results
        cout << path.size() << " " << dist[t] << endl;
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
