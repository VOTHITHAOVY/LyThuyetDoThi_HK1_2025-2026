#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<int> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

int calculateExponent(int n, int p) {
    int exponent = 0;
    int power = p;
    
    while (power <= n) {
        exponent += n / power;
        power *= p;
    }
    
    return exponent;
}

vector<int> factorizeFactorial(int n) {
    vector<int> primes = sieveOfEratosthenes(n);
    vector<int> exponents;
    
    for (int p : primes) {
        int exp = calculateExponent(n, p);
        exponents.push_back(exp);
    }
    
    return exponents;
}

int main() {
    int N;
    while (cin >> N) {
        vector<int> result = factorizeFactorial(N);
        
        // In kết quả
        for (int i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}