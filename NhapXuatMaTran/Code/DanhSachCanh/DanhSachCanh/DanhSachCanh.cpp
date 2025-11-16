#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;

    // Nhập số đỉnh và số cạnh
    cout << "Nhap so dinh n: ";
    cin >> n;
    cout << "Nhap so canh m: ";
    cin >> m;

    // Khai báo mảng bậc
    vector<int> degree(n, 0);

    // Nhập danh sách cạnh
    cout << "Nhap " << m << " canh (moi canh la 2 dinh u v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        // Kiểm tra tính hợp lệ
        if (u >= 0 && u < n && v >= 0 && v < n) {
            degree[u]++;
            degree[v]++;
        }
    }

    // Xuất kết quả
    cout << "\nBAC CAC DINH:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Dinh " << i << ": bac = " << degree[i] << endl;
    }

    return 0;
}