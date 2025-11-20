#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);

    for (int i = 1; i <= n; i++) {
        int j;
        while (cin >> j && j != -1) {
            adj[i].push_back(j);
        }
    }

    vector<bool> visited(n + 1, false);
    vector<vector<int>> components;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            vector<int> component;
            queue<int> q;

            visited[i] = true;
            q.push(i);
            component.push_back(i);

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                        component.push_back(v);
                    }
                }
            }

            sort(component.begin(), component.end());
            components.push_back(component);
        }
    }

    cout << components.size() << endl;
    for (auto comp : components) {
        for (int i = 0; i < comp.size(); i++) {
            cout << comp[i];
            if (i < comp.size() - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}