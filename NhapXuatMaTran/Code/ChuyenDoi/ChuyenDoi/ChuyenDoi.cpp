#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v;
    Edge(int u, int v) : u(u), v(v) {}
};

// 1. Ma trận kề → Danh sách kề
vector<vector<int>> matrixToAdjList(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> adjList(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                adjList[i].push_back(j);
            }
        }
    }
    return adjList;
}

// 2. Ma trận kề → Danh sách cạnh
vector<Edge> matrixToEdgeList(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<Edge> edgeList;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) { // Chỉ xét i < j để tránh trùng
            if (matrix[i][j] == 1) {
                edgeList.push_back(Edge(i, j));
            }
        }
    }
    return edgeList;
}

// 3. Danh sách kề → Ma trận kề
vector<vector<int>> adjListToMatrix(const vector<vector<int>>& adjList) {
    int n = adjList.size();
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j : adjList[i]) {
            matrix[i][j] = 1;
        }
    }
    return matrix;
}

// 4. Danh sách kề → Danh sách cạnh
vector<Edge> adjListToEdgeList(const vector<vector<int>>& adjList) {
    int n = adjList.size();
    vector<Edge> edgeList;

    for (int i = 0; i < n; i++) {
        for (int j : adjList[i]) {
            if (i < j) { // Chỉ thêm khi i < j để tránh trùng
                edgeList.push_back(Edge(i, j));
            }
        }
    }
    return edgeList;
}

// 5. Danh sách cạnh → Ma trận kề
vector<vector<int>> edgeListToMatrix(const vector<Edge>& edgeList, int n) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (const Edge& edge : edgeList) {
        matrix[edge.u][edge.v] = 1;
        matrix[edge.v][edge.u] = 1; // Đồ thị vô hướng
    }
    return matrix;
}

// 6. Danh sách cạnh → Danh sách kề
vector<vector<int>> edgeListToAdjList(const vector<Edge>& edgeList, int n) {
    vector<vector<int>> adjList(n);

    for (const Edge& edge : edgeList) {
        adjList[edge.u].push_back(edge.v);
        adjList[edge.v].push_back(edge.u); // Đồ thị vô hướng
    }

    // Sắp xếp danh sách kề cho đẹp
    for (int i = 0; i < n; i++) {
        sort(adjList[i].begin(), adjList[i].end());
    }
    return adjList;
}

// Hàm in ma trận kề
void printMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    cout << "Ma tran ke " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Hàm in danh sách kề
void printAdjList(const vector<vector<int>>& adjList) {
    int n = adjList.size();
    cout << "Danh sach ke:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Dinh " << i << ": ";
        for (int j : adjList[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}

// Hàm in danh sách cạnh
void printEdgeList(const vector<Edge>& edgeList) {
    cout << "Danh sach canh:" << endl;
    for (const Edge& edge : edgeList) {
        cout << "(" << edge.u << ", " << edge.v << ")" << endl;
    }
}

int main() {
    // Ví dụ đồ thị 4 đỉnh
    int n = 4;

    // Ma trận kề mẫu
    vector<vector<int>> matrix = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };

    cout << "=== CHUYEN DOI CAC CACH BIEU DIEN DO THI ===" << endl;

    // 1. Ma trận kề → Danh sách kề
    cout << "\n1. Ma tran ke -> Danh sach ke:" << endl;
    vector<vector<int>> adjList1 = matrixToAdjList(matrix);
    printAdjList(adjList1);

    // 2. Ma trận kề → Danh sách cạnh
    cout << "\n2. Ma tran ke -> Danh sach canh:" << endl;
    vector<Edge> edgeList1 = matrixToEdgeList(matrix);
    printEdgeList(edgeList1);

    // 3. Danh sách kề → Ma trận kề
    cout << "\n3. Danh sach ke -> Ma tran ke:" << endl;
    vector<vector<int>> matrix1 = adjListToMatrix(adjList1);
    printMatrix(matrix1);

    // 4. Danh sách kề → Danh sách cạnh
    cout << "\n4. Danh sach ke -> Danh sach canh:" << endl;
    vector<Edge> edgeList2 = adjListToEdgeList(adjList1);
    printEdgeList(edgeList2);

    // 5. Danh sách cạnh → Ma trận kề
    cout << "\n5. Danh sach canh -> Ma tran ke:" << endl;
    vector<vector<int>> matrix2 = edgeListToMatrix(edgeList1, n);
    printMatrix(matrix2);

    // 6. Danh sách cạnh → Danh sách kề
    cout << "\n6. Danh sach canh -> Danh sach ke:" << endl;
    vector<vector<int>> adjList2 = edgeListToAdjList(edgeList1, n);
    printAdjList(adjList2);

    return 0;
}