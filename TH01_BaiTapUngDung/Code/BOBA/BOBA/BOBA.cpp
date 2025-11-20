#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    int T;
    cin >> T;
    cin.ignore(); // Bỏ qua ký tự newline sau số T

    for (int t = 0; t < T; t++) {
        string s;
        getline(cin, s); // Đọc cả dòng

        // Debug: in ra chuỗi vừa đọc được
        // cout << "Debug: Chuoi thu " << t + 1 << ": " << s << endl;

        // Nếu chuỗi ngắn hơn 3 ký tự
        if (s.length() < 3) {
            cout << 0 << endl;
            continue;
        }

        // Dùng unordered_map để đếm tần suất các bộ ba
        unordered_map<string, int> freq;
        int max_count = 0;

        // Duyệt qua tất cả các bộ ba liên tiếp
        for (int i = 0; i <= s.length() - 3; i++) {
            string triple = s.substr(i, 3);
            freq[triple]++;

            // Cập nhật max_count ngay lập tức
            if (freq[triple] > max_count) {
                max_count = freq[triple];
            }
        }

        cout << max_count << endl;
    }

    return 0;
}