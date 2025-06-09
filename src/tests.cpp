#include <cassert>
#include <iostream>
#include "../include/ArraySequence.h"
#include "../include/ListSequence.h"
#include "../include/ImmutableArraySequence.h"
#include "../include/ImmutableListSequence.h"
#include "../include/custom_exceptions.h"
#include "../include/Algorithm.h"
#include "../include/Sequence.h"
#include "../include/DynamicArray.h"
#include "../include/LinkedList.h"


using namespace std;

template <typename T>
void test_sequence_basic_operations(Sequence<T>* seq) {
    
    assert(seq->get_size() == 0);

    seq->append(1);
    assert(seq->get_size() == 1);
    assert(seq->get(0) == 1);

    seq->prepend(0);
    assert(seq->get_size() == 2);
    assert(seq->get(0) == 0);
    assert(seq->get(1) == 1);

    seq->set(1, 2);
    assert(seq->get(1) == 2);

    assert(seq->get_first() == 0);
    assert(seq->get_last() == 2);

    Sequence<T>* sub = seq->get_subsequence(0, 1);
    assert(sub->get_size() == 2);
    assert(sub->get(0) == 0);
    assert(sub->get(1) == 2);
    delete sub;

    seq->map(2);
    assert(seq->get(0) == 0);
    assert(seq->get(1) == 4);

    string str = seq->to_string();
    assert(str.find("0") != string::npos);
    assert(str.find("4") != string::npos);
}

void test_dynamic_array() {
    
    DynamicArray<int> arr1;
    assert(arr1.get_size() == 0);

    DynamicArray<int> arr2(5);
    assert(arr2.get_size() == 5);

    int data[] = {1, 2, 3};
    DynamicArray<int> arr3(data, 3);
    assert(arr3.get_size() == 3);
    assert(arr3.get(0) == 1);
    assert(arr3.get(1) == 2);
    assert(arr3.get(2) == 3);

    arr3.set(1, 5);
    assert(arr3.get(1) == 5);

    arr3.resize(5);
    assert(arr3.get_size() == 5);
    arr3.resize(2);
    assert(arr3.get_size() == 2);

    cout << "DynamicArray tests passed!\n";
}

void test_linked_list() {
    
    LinkedList<int> list1;
    assert(list1.get_size() == 0);

    int data[] = {1, 2, 3};
    LinkedList<int> list2(data, 3);
    assert(list2.get_size() == 3);
    assert(list2.get(0) == 1);
    assert(list2.get(1) == 2);
    assert(list2.get(2) == 3);

    LinkedList<int> list3(list2);
    assert(list3.get_size() == 3);
    assert(list3.get(0) == 1);

    list1.append(1);
    assert(list1.get_size() == 1);
    assert(list1.get(0) == 1);

    list1.prepend(0);
    assert(list1.get_size() == 2);
    assert(list1.get(0) == 0);
    assert(list1.get(1) == 1);

    list1.set(1, 2);
    assert(list1.get(1) == 2);

    assert(list1.get_first() == 0);
    assert(list1.get_last() == 2);

    LinkedList<int>* sub = list1.get_sublist(0, 1);
    assert(sub->get_size() == 2);
    assert(sub->get(0) == 0);
    assert(sub->get(1) == 2);
    delete sub;

    cout << "LinkedList tests passed!\n";
}

void test_array_sequence() {
    ArraySequence<int> seq;
    test_sequence_basic_operations(&seq);

    int data[] = {1, 2, 3};
    ArraySequence<int> seq2(data, 3);
    assert(seq2.get_size() == 3);
    assert(seq2.get(0) == 1);

    ArraySequence<int> seq3(seq2);
    assert(seq3.get_size() == 3);
    assert(seq3.get(0) == 1);

    cout << "ArraySequence tests passed!\n";
}

// void test_list_sequence() {
//     ListSequence<int> seq;
//     test_sequence_basic_operations(&seq);

//     int data[] = {1, 2, 3};
//     ListSequence<int> seq2(data, 3);
//     assert(seq2.get_size() == 3);
//     assert(seq2.get(0) == 1);

//     ListSequence<int> seq3(seq2);
//     assert(seq3.get_size() == 3);
//     assert(seq3.get(0) == 1);

//     cout << "ListSequence tests passed!\n";
// }

void test_immutable_array_sequence() {

    ConstArraySequence<int> seq1;
    assert(seq1.get_size() == 0);

    ConstArraySequence<int>* seq2 = seq1.append(1);
    assert(seq1.get_size() == 0); 
    assert(seq2->get_size() == 1);
    assert(seq2->get(0) == 1);

    ConstArraySequence<int>* seq3 = seq2->prepend(0);
    assert(seq2->get_size() == 1); 
    assert(seq3->get_size() == 2);
    assert(seq3->get(0) == 0);
    assert(seq3->get(1) == 1);

    ConstArraySequence<int>* seq4 = seq3->set(1, 2);
    assert(seq3->get(1) == 1); 
    assert(seq4->get(1) == 2);

    delete seq2;
    delete seq3;
    delete seq4;

    cout << "ImmutableArraySequence tests passed!\n";
}

void test_immutable_list_sequence() {
    
    ConstListSequence<int> seq1;
    assert(seq1.get_size() == 0);

    ConstListSequence<int>* seq2 = seq1.append(1);
    assert(seq1.get_size() == 0); 
    assert(seq2->get_size() == 1);
    assert(seq2->get(0) == 1);

    ConstListSequence<int>* seq3 = seq2->prepend(0);
    assert(seq2->get_size() == 1);
    assert(seq3->get_size() == 2);
    assert(seq3->get(0) == 0);
    assert(seq3->get(1) == 1);

    ConstListSequence<int>* seq4 = seq3->set(1, 2);
    assert(seq3->get(1) == 1);
    assert(seq4->get(1) == 2);

    
    delete seq2;
    delete seq3;
    delete seq4;

    cout << "ImmutableListSequence tests passed!\n";
}

void test_exceptions() {
   
    DynamicArray<int> arr(3);
    try {
        arr.get(3); 
        assert(false); 
    } catch (const array_out_of_range&) {
        assert(true);
    }

    LinkedList<int> list;
    try {
        list.get(0); 
        assert(false); 
    } catch (const list_out_of_range&) {
        assert(true);
    }

    ArraySequence<int> seq;
    try {
        seq.get_first(); 
        assert(false); 
    } catch (const array_out_of_range&) {
        assert(true);
    }

    cout << "Exception tests passed!\n";
}


int main() {
    cout << "Running tests...\n";

    test_dynamic_array();
    test_linked_list();
    test_array_sequence();
    //test_list_sequence();
    test_immutable_array_sequence();
    test_immutable_list_sequence();
    test_exceptions();

    cout << "All tests passed successfully!\n";
    return 0;
}