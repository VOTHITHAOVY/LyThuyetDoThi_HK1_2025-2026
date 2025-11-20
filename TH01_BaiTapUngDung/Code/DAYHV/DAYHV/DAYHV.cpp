#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    // Mảng đánh dấu, chỉ số từ 1 đến N
    vector<bool> visited(N + 1, false);
    bool isPermutation = true;

    for (int i = 0; i < N; i++) {
        // Kiểm tra phần tử có nằm trong khoảng [1, N]
        if (arr[i] < 1 || arr[i] > N) {
            isPermutation = false;
            break;
        }

        // Kiểm tra phần tử đã xuất hiện chưa
        if (visited[arr[i]]) {
            isPermutation = false;
            break;
        }

        // Đánh dấu phần tử đã xuất hiện
        visited[arr[i]] = true;
    }

    // Kiểm tra tất cả phần tử từ 1 đến N đều xuất hiện
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            isPermutation = false;
            break;
        }
    }

    if (isPermutation) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}