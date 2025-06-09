#pragma once

#include "ArraySequence.h"
#include "custom_exceptions.h"

template <typename T>
class ConstArraySequence : public ArraySequence<T> 
{
public:

    ConstArraySequence();
    ConstArraySequence(T* arr, int count);
    ConstArraySequence(Sequence<T>& seq);

    ConstArraySequence<T>* append(T item) override;
    ConstArraySequence<T>* prepend(T item) override;
    ConstArraySequence<T>* set(int index, T item) override;
    ConstArraySequence<T>* get_subsequence(int start_index, int end_index) const override;

};

template <typename T>
ConstArraySequence<T>::ConstArraySequence() 
: ArraySequence<T>(){};

template <typename T>
ConstArraySequence<T>::ConstArraySequence(T* arr, int count) 
: ArraySequence<T>(arr, count){};

template <typename T>
ConstArraySequence<T>::ConstArraySequence(Sequence<T>& seq) 
: ArraySequence<T>(seq){};

template <typename T>
ConstArraySequence<T>* ConstArraySequence<T>::append(T item){
    int new_size = this->get_size() + 1;
    T* new_data = new T[new_size];

    for (int i = 0; i < new_size - 1; i++) {
        new_data[i] = this->get(i); 
    }
    new_data[new_size - 1] = item;

    ConstArraySequence<T>* result = new ConstArraySequence<T>(new_data, new_size);
    delete[] new_data;
    return result;
}

template <typename T>
ConstArraySequence<T>* ConstArraySequence<T>::prepend(T item){
    int new_size = this->get_size() + 1;
    T* new_data = new T[new_size];

    for (int i = new_size - 1; i > 0; i--) {
        new_data[i] = this->get(i - 1); 
    }
    new_data[0] = item;

    ConstArraySequence<T>* result = new ConstArraySequence<T>(new_data, new_size);
    delete[] new_data;
    return result;
}

template <typename T>
ConstArraySequence<T>* ConstArraySequence<T>::set(int index, T item){
    int size = this->get_size();

    if (index >= size || index < 0) throw array_out_of_range();
    T* new_data = new T[size];

    for (int i = 0; i < size; i++) {
        new_data[i] = this->get(i); 
    }
    new_data[index] = item;

    ConstArraySequence<T>* result = new ConstArraySequence<T>(new_data, size);
    delete[] new_data;
    return result;
}

template <typename T>
ConstArraySequence<T>* ConstArraySequence<T>::get_subsequence(int start_index, int end_index) const {
    ArraySequence<T>* sub = ArraySequence<T>::get_subsequence(start_index, end_index);

    int size = sub->get_size();
    T* temp_array = new T[size];

    for (int i = 0; i < size; i++) {
        temp_array[i] = sub->get(i);
    }

    delete sub;
    ConstArraySequence<T>* result = new ConstArraySequence<T>(temp_array, size);
    delete[] temp_array;
    return result;
}