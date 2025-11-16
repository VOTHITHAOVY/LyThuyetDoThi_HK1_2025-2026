#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

class MapColoring {
private:
    map<string, vector<string>> adj;
    map<string, int> color;
    vector<string> states;

public:
    void addState(const string& state) {
        states.push_back(state);
        color[state] = 0;
    }

    void addBorder(const string& state1, const string& state2) {
        adj[state1].push_back(state2);
        adj[state2].push_back(state1);
    }

    // Thuật toán tham lam
    void greedyColoring() {
        // Sắp xếp các bang theo số bang kề giảm dần
        vector<pair<string, int>> state_degree;
        for (const auto& state : states) {
            state_degree.push_back({ state, (int)adj[state].size() });
        }

        sort(state_degree.begin(), state_degree.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second > b.second;
            });

        int max_color = 0;

        // Tô màu từng bang
        for (const auto& state_pair : state_degree) {
            string state = state_pair.first;
            set<int> used_colors;

            // Tìm màu đã dùng bởi các bang kề
            for (const auto& neighbor : adj[state]) {
                if (color[neighbor] != 0) {
                    used_colors.insert(color[neighbor]);
                }
            }

            // Tìm màu nhỏ nhất chưa dùng
            int current_color = 1;
            while (used_colors.find(current_color) != used_colors.end()) {
                current_color++;
            }

            color[state] = current_color;
            if (current_color > max_color) {
                max_color = current_color;
            }
        }

        cout << "So mau su dung: " << max_color << endl;
    }

    void printColoring() {
        // Nhóm các bang theo màu
        map<int, vector<string>> color_groups;
        for (const auto& state : states) {
            color_groups[color[state]].push_back(state);
        }

        // In kết quả
        for (const auto& group : color_groups) {
            cout << "Màu " << group.first << ": ";
            for (const auto& state : group.second) {
                cout << state << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    MapColoring usa;

    // Thêm các bang từ đề bài
    vector<string> states = {
        "NEVADA", "UTAH", "COLORADO", "CALIFORNIA", "ARIZONA",
        "NEBRASKA", "KANSAS", "OKLAHOMA", "ARKANSAS", "MISSISSIPI",
        "GEORGIA", "TEXAS", "LOUISIANA", "FLORIDA"
    };

    for (const auto& state : states) {
        usa.addState(state);
    }

    // Thêm các đường biên giới giữa các bang
    // Miền Tây
    usa.addBorder("NEVADA", "UTAH");
    usa.addBorder("NEVADA", "CALIFORNIA");
    usa.addBorder("NEVADA", "ARIZONA");

    usa.addBorder("UTAH", "COLORADO");
    usa.addBorder("UTAH", "ARIZONA");

    usa.addBorder("CALIFORNIA", "ARIZONA");

    usa.addBorder("ARIZONA", "COLORADO");

    usa.addBorder("COLORADO", "NEBRASKA");
    usa.addBorder("COLORADO", "KANSAS");
    usa.addBorder("COLORADO", "OKLAHOMA");

    // Miền Trung
    usa.addBorder("NEBRASKA", "KANSAS");

    usa.addBorder("KANSAS", "OKLAHOMA");

    usa.addBorder("OKLAHOMA", "TEXAS");
    usa.addBorder("OKLAHOMA", "ARKANSAS");

    usa.addBorder("TEXAS", "LOUISIANA");
    usa.addBorder("TEXAS", "ARKANSAS");

    usa.addBorder("ARKANSAS", "LOUISIANA");
    usa.addBorder("ARKANSAS", "MISSISSIPI");

    usa.addBorder("LOUISIANA", "MISSISSIPI");

    usa.addBorder("MISSISSIPI", "GEORGIA");
    usa.addBorder("MISSISSIPI", "ALABAMA");

    usa.addBorder("GEORGIA", "FLORIDA");
    usa.addBorder("GEORGIA", "ALABAMA");

    usa.addBorder("FLORIDA", "ALABAMA");

    cout << "=== To mau ban do cac Bang MIEN TAY & NAM NUOC MY ===" << endl;
    usa.greedyColoring();
    cout << "\nKET QUA TO MAU:" << endl;
    usa.printColoring();

    return 0;
}