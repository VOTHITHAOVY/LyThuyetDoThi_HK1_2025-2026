#include <iostream>
#include <vector>
#include <stack>
using namespace std;

bool isBipartite(vector<vector<int>>& adj, int n) {
    vector<int> color(n + 1, 0); // 0: chưa tô, 1: màu 1, 2: màu 2

    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            stack<int> st;
            st.push(i);
            color[i] = 1;

            while (!st.empty()) {
                int u = st.top();
                st.pop();

                for (int v : adj[u]) {
                    if (color[v] == 0) {
                        color[v] = 3 - color[u]; // 1->2, 2->1
                        st.push(v);
                    }
                    else if (color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

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

    if (isBipartite(adj, n)) {
        cout << "Do thi phan doi" << endl;
    }
    else {
        cout << "Do thi khong phan doi" << endl;
    }

    return 0;
}