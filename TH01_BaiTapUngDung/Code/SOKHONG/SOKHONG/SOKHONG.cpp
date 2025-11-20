#include <iostream>
using namespace std;

int countTrailingZeros(long long n) {
    int count = 0;
    long long divisor = 5;

    while (divisor <= n) {
        count += n / divisor;
        divisor *= 5;
    }

    return count;
}

int main() {
    long long N;
    while (cin >> N) {
        cout << countTrailingZeros(N) << endl;
    }

    return 0;
}