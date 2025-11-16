#include <iostream>
using namespace std;

int main() {
    int n;

    // Nhập số đỉnh
    cout << "Nhap so dinh n: ";
    cin >> n;

    // Khai báo mảng động
    int** a = new int* [n];
    int* bac_vao = new int[n]();
    int* bac_ra = new int[n]();

    for (int i = 0; i < n; i++) {
        a[i] = new int[n];
    }

    // Nhập ma trận kề
    cout << "Nhap ma tran ke " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    // Tính bậc vào và bậc ra
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 1) {
                bac_ra[i]++;    // Bậc ra = số cung đi ra từ i
                bac_vao[j]++;   // Bậc vào = số cung đi vào j
            }
        }
    }

    // Xuất kết quả
    cout << "\nBAC VAO - BAC RA CAC DINH:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Dinh " << i << ": bac vao = " << bac_vao[i]
            << ", bac ra = " << bac_ra[i] << endl;
    }

    // Giải phóng bộ nhớ
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
    delete[] bac_vao;
    delete[] bac_ra;

    return 0;
}