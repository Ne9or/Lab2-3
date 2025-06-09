#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> Range(int l, int h) {
    if (l > h) {
        throw invalid_argument("Lower bound must be less than or equal to upper bound");
    }
    
    vector<int> result;
    for (int i = l; i <= h; ++i) {
        result.push_back(i);
    }
    return result;
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

vector<int> primeFactors(int n) {
    vector<int> factors;
    
    if (n <= 1) return factors;
    
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    
    if (n > 2) {
        factors.push_back(n);
    }
    
    return factors;
}

vector<int> where(const vector<int>& numbers, const string& filterType, int target = 0) {
    vector<int> result;
    
    if (filterType == "prime_factors") {
        for (int num : numbers) {
            vector<int> factors = primeFactors(num);
            if (!factors.empty()) {
                result.push_back(num);
            }
        }
    }
    else if (filterType == "specific_prime_factors" && target > 0) {
        for (int num : numbers) {
            vector<int> factors = primeFactors(num);
            if (find(factors.begin(), factors.end(), target) != factors.end()) {
                result.push_back(num);
            }
        }
    }
    
    return result;
}

void printNumbers(const vector<int>& numbers) {
    cout << "[";
    for (size_t i = 0; i < numbers.size(); ++i) {
        cout << numbers[i];
        if (i != numbers.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}