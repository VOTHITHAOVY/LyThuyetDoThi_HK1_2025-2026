#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_VALUE = 10000;

int main() {
    int nx, ny, nz;

    // Đọc dãy x
    cin >> nx;
    vector<int> x(nx);
    vector<bool> countX(MAX_VALUE + 1, false);
    for (int i = 0; i < nx; i++) {
        cin >> x[i];
        countX[x[i]] = true;
    }

    // Đọc dãy y
    cin >> ny;
    vector<int> y(ny);
    vector<bool> countY(MAX_VALUE + 1, false);
    for (int i = 0; i < ny; i++) {
        cin >> y[i];
        countY[y[i]] = true;
    }

    // Đọc dãy z
    cin >> nz;
    vector<int> z(nz);
    vector<bool> countZ(MAX_VALUE + 1, false);
    for (int i = 0; i < nz; i++) {
        cin >> z[i];
        countZ[z[i]] = true;
    }

    // Tìm phần tử chung
    vector<int> common;
    for (int i = 1; i <= MAX_VALUE; i++) {
        if (countX[i] && countY[i] && countZ[i]) {
            common.push_back(i);
        }
    }

    // Sắp xếp kết quả (đã tự động tăng dần do duyệt từ 1->MAX_VALUE)
    // In kết quả
    cout << common.size() << endl;
    for (int i = 0; i < common.size(); i++) {
        cout << common[i];
        if (i < common.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}