#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include "ArraySequence.h"

using namespace std;

                                                                                     

Sequence<int>* Range(int l, int h) {
    Sequence<int>  *seq = new ArraySequence<int>();
    if (l > h) {
        throw invalid_argument("Lower bound must be less than or equal to upper bound");
    }

    for (int i = l; i <= h; ++i) {
        seq->append(i);
    }
    return seq;
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

Sequence<int>* primeFactors(int n) {
    Sequence<int> *factors  =  new ArraySequence<int>();
    
    if (n <= 1) return factors;
    
    while (n % 2 == 0) {
        factors->append(2);
        n /= 2;
    }
    
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            factors->append(i);
            n /= i;
        }
    }
    
    if (n > 2) {
        factors->append(n);
    }
    
    return factors;
}

Sequence<int>* where(const Sequence<int>& seq, const string& filterType, int target = 0) {
    Sequence<int> *result = new ArraySequence<int>;

    cout << "0";
    
    if (filterType == "prime_factors") {
        for (int i = 0; i < seq.get_size(); i ++){
            Sequence<int>* factors = primeFactors(seq.get(i));
            if (factors->get_size() == 1) {
                result->append(seq.get(i));
            }
        }
    }
    else if (filterType == "specific_prime_factors" && target > 0) {
        for (int i = 0; i < seq.get_size(); i ++) {
            Sequence<int>* factors = primeFactors(seq.get(i));
            for (int g =  0; g < factors->get_size(); g++){
                if (factors->get(g) == target){
                    result->append(seq.get(i));
                    break;
                }
            }
        }
    }
    return result;
}

void printNumbers(const Sequence<int>& numbers) {
    cout << "[";
    for (size_t i = 0; i < numbers.get_size(); ++i) {
        cout << numbers.get(i);
        if (i != numbers.get_size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}