#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include "../include/ArraySequence.h"
#include "../include/ListSequence.h"
#include "../include/ImmutableArraySequence.h"
#include "../include/ImmutableListSequence.h"
#include "../include/custom_exceptions.h"
#include "../include/Algorithm.h"

using namespace std;

template <typename T>
void sequenceOperationsMenu(Sequence<T>* sequence, bool isImmutable);

template <typename T>
void printSequenceInfo(const Sequence<T>* sequence);

void AlgorithmMenu() {
    int choice;
    int l, h, target;
    Sequence<int> *seq = new ArraySequence<int>;
    Sequence<int> *result = new ArraySequence<int>;
    
    do {
        cout << "\nAlgorithm Menu:\n";
        cout << "1. Generate range of numbers\n";
        cout << "2. Show numbers containing specific prime factor\n";
        cout << "3. Show prime numbers only\n";
        cout << "4. View current numbers\n";
        cout << "0. Back to main menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        try {
            switch (choice) {
                case 1:
                    cout << "Enter lower bound: ";
                    cin >> l;
                    cout << "Enter upper bound: ";
                    cin >> h;
                    seq = Range(l, h);
                    cout << "Generated numbers: ";
                    printNumbers(*seq);
                    break;
                    
                case 2:
                    cout <<  "webewa";
                    if (!seq->get_size()) {
                        cout << "Please generate numbers first.\n";
                        break;
                    }
                    cout << "Enter prime factor to filter by: ";
                    cin >> target;
                    if (!isPrime(target)) {
                        cout << target << " is not a prime number.\n";
                        break;
                    }
                    cout << "fhus";
                    result = where(*seq, "specific_prime_factors", target);
                    cout << "Numbers containing prime factor " << target << ": ";
                    printNumbers(*result);
                    break;
                    
                case 3:
                    cout << "vawbefaiow";
                    if (!seq->get_size()) {
                        cout << "Please generate numbers first.\n";
                        break;
                    }
                    cout << "2";
                    result = where(*seq, "prime_factors");
                    cout << "Prime numbers: ";
                    printNumbers(*result);
                    break;
                    
                case 4:
                    if (!seq->get_size()) {
                        cout << "No numbers generated yet.\n";
                    } else {
                        cout << "Current numbers: ";
                        printNumbers(*seq);
                    }
                    break;
                    
                case 0:
                    cout << "Returning to main menu...\n";
                    break;
                    
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (choice != 0);
}

template <typename T>
void sequenceOperationsMenu(Sequence<T>* sequence, bool isImmutable) {
    int choice;
    T value;
    int index, startIndex, endIndex;
    double multiplier;

    do {
        cout << "\nSequence Operations Menu:\n";
        cout << "1. Append element\n";
        cout << "2. Prepend element\n";
        cout << "3. Set element at index\n";
        cout << "4. Get element at index\n";
        cout << "5. Get first element\n";
        cout << "6. Get last element\n";
        cout << "7. Get subsequence\n";
        cout << "8. Map (multiply numbers/uppercase strings)\n";
        cout << "9. Print sequence info\n";
        cout << "0. Back to main menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1:
                    cout << "Enter value to append: ";
                    cin >> value;
                    if (isImmutable) {
                        sequence = sequence->append(value);
                    } else {
                        sequence->append(value);
                    }
                    cout << "Element appended.\n";
                    break;

                case 2:
                    cout << "Enter value to prepend: ";
                    cin >> value;
                    if (isImmutable) {
                        sequence = sequence->prepend(value);
                    } else {
                        sequence->prepend(value);
                    }
                    cout << "Element prepended.\n";
                    break;

                case 3:
                    cout << "Enter index: ";
                    cin >> index;
                    cout << "Enter new value: ";
                    cin >> value;
                    if (isImmutable) {
                        sequence = sequence->set(index, value);
                    } else {
                        sequence->set(index, value);
                    }
                    cout << "Element set.\n";
                    break;

                case 4:
                    cout << "Enter index: ";
                    cin >> index;
                    value = sequence->get(index);
                    cout << "Value at index " << index << ": " << value << endl;
                    break;

                case 5:
                    value = sequence->get_first();
                    cout << "First element: " << value << endl;
                    break;

                case 6:
                    value = sequence->get_last();
                    cout << "Last element: " << value << endl;
                    break;

                case 7:
                    cout << "Enter start index: ";
                    cin >> startIndex;
                    cout << "Enter end index: ";
                    cin >> endIndex;
                    {
                        Sequence<T>* subSequence = sequence->get_subsequence(startIndex, endIndex);
                        cout << "Subsequence: " << subSequence->to_string() << endl;
                        delete subSequence;
                    }
                    break;

                case 8:
                    if constexpr (is_same_v<T, string>) {
                        multiplier = 1.0;
                        cout << "Converting strings to uppercase...\n";
                    } else {
                        cout << "Enter multiplier: ";
                        cin >> multiplier;
                    }
                    sequence->map(multiplier);
                    cout << "Sequence after mapping: " << sequence->to_string() << endl;
                    break;

                case 9:
                    printSequenceInfo(sequence);
                    break;

                case 0:
                    cout << "Returning to main menu...\n";
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }

    } while (choice != 0);

    delete sequence;
}

template <typename T>
void printSequenceInfo(const Sequence<T>* sequence) {
    cout << "\nSequence Information:\n";
    cout << "Size: " << sequence->get_size() << endl;
    cout << "Contents: " << sequence->to_string() << endl;
}

void sequenceTypeMenu() {
    int dataTypeChoice, storageTypeChoice, mutabilityChoice;
    bool isImmutable = false;

    cout << "\nChoose Data Type:\n";
    cout << "1. Integer\n";
    cout << "2. Double\n";
    cout << "3. String\n";
    cout << "Enter your choice: ";
    cin >> dataTypeChoice;

    cout << "\nChoose Storage Type:\n";
    cout << "1. Array Sequence\n";
    cout << "2. List Sequence\n";
    cout << "Enter your choice: ";
    cin >> storageTypeChoice;

    cout << "\nChoose Mutability:\n";
    cout << "1. Mutable\n";
    cout << "2. Immutable\n";
    cout << "Enter your choice: ";
    cin >> mutabilityChoice;

    isImmutable = (mutabilityChoice == 2);

    try {
        switch (dataTypeChoice) {
            case 1:
                if (storageTypeChoice == 1) {
                    if (isImmutable) {
                        sequenceOperationsMenu<int>(new ConstArraySequence<int>(), isImmutable);
                    } else {
                        sequenceOperationsMenu<int>(new ArraySequence<int>(), isImmutable);
                    }
                } else {
                    if (isImmutable) {
                        sequenceOperationsMenu<int>(new ConstListSequence<int>(), isImmutable);
                    } else {
                        sequenceOperationsMenu<int>(new ListSequence<int>(), isImmutable);
                    }
                }
                break;

            case 2:
                if (storageTypeChoice == 1) {
                    if (isImmutable) {
                        sequenceOperationsMenu<double>(new ConstArraySequence<double>(), isImmutable);
                    } else {
                        sequenceOperationsMenu<double>(new ArraySequence<double>(), isImmutable);
                    }
                } else {
                    if (isImmutable) {
                        sequenceOperationsMenu<double>(new ConstListSequence<double>(), isImmutable);
                    } else {
                        sequenceOperationsMenu<double>(new ListSequence<double>(), isImmutable);
                    }
                }
                break;

            case 3:
                if (storageTypeChoice == 1) {
                    if (isImmutable) {
                        sequenceOperationsMenu<string>(new ConstArraySequence<string>(), isImmutable);
                    } else {
                        sequenceOperationsMenu<string>(new ArraySequence<string>(), isImmutable);
                    }
                } else {
                    if (isImmutable) {
                        sequenceOperationsMenu<string>(new ConstListSequence<string>(), isImmutable);
                    } else {
                        sequenceOperationsMenu<string>(new ListSequence<string>(), isImmutable);
                    }
                }
                break;

            default:
                cout << "Invalid data type choice.\n";
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void mainMenu() {
    int choice;
    
    do {
        cout << "\nMain Menu:\n";
        cout << "1. Sequence Operations\n";
        cout << "2. Algorithm (Range & Prime Factors)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                sequenceTypeMenu();
                break;
                
            case 2:
                AlgorithmMenu();
                break;
                
            case 3:
                return;
                
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}

int main() {
    cout << "Sequence Collections and Algorithm Program\n";
    mainMenu();
    return 0;
}