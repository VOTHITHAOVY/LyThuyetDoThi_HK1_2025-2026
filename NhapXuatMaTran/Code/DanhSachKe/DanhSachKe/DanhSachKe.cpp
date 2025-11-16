#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Nhap so dinh n: ";
    cin >> n;

    vector<vector<int>> adjList(n);
    vector<int> degree(n, 0);

    cout << "Nhap danh sach ke:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Dinh " << i << " ke voi (nhap -1 de ket thuc): ";

        int neighbor;
        while (true) {
            cin >> neighbor;
            if (neighbor == -1) break;
            if (neighbor >= 0 && neighbor < n) {
                adjList[i].push_back(neighbor);
            }
        }
        degree[i] = adjList[i].size();
    }

    cout << "\nBAC CAC DINH:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Dinh " << i << ": " << degree[i] << endl;
    }

    return 0;
}