#include <iostream>
#include <vector>
using namespace std;

void nhapMaTranKe(vector<vector<int>>& adjMatrix, int& n) {
    cout << "Nhap so dinh n: ";
    cin >> n;

    adjMatrix.resize(n, vector<int>(n));
    cout << "Nhap ma tran ke " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adjMatrix[i][j];
        }
    }
}

void tinhBacCacDinh(const vector<vector<int>>& adjMatrix, vector<int>& degrees) {
    int n = adjMatrix.size();
    degrees.resize(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            degrees[i] += adjMatrix[i][j];
        }
    }
}

void xuatKetQua(const vector<int>& degrees) {
    int n = degrees.size();
    cout << "\nSo dinh: " << n << endl;
    cout << "Bac cac dinh:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Dinh " << i << ": " << degrees[i] << endl;
    }
}

int main() {
    vector<vector<int>> adjMatrix;
    vector<int> degrees;
    int n;

    // Nhập ma trận kề từ bàn phím
    nhapMaTranKe(adjMatrix, n);

    // Tính bậc các đỉnh
    tinhBacCacDinh(adjMatrix, degrees);

    // Xuất kết quả
    xuatKetQua(degrees);

    return 0;
}