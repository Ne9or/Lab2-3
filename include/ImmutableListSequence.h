#pragma once

#include "ListSequence.h"
#include "custom_exceptions.h"

template <typename T>
class ConstListSequence : public ListSequence<T>
{
public:

    ConstListSequence();
    ConstListSequence(T* arr, int count);
    ConstListSequence(Sequence<T>& seq);

    ConstListSequence<T>* append(T item) override;
    ConstListSequence<T>* prepend(T item) override;
    ConstListSequence<T>* set(int index, T item) override;
    ConstListSequence<T>* get_subsequence(int start_index, int end_index) const override;
    
};

template <typename T>
ConstListSequence<T>::ConstListSequence()
: ListSequence<T>() {}

template <typename T>
ConstListSequence<T>::ConstListSequence(T* arr, int count)
: ListSequence<T>(arr, count) {}

template <typename T>
ConstListSequence<T>::ConstListSequence(Sequence<T>& seq)
: ListSequence<T>(seq) {}

template <typename T>
ConstListSequence<T>* ConstListSequence<T>::append(T item) {
    int new_size = this->get_size() + 1;
    T* new_data = new T[new_size];

    for (int i = 0; i < new_size - 1; i++) {
        new_data[i] = this->get(i);
    }
    new_data[new_size - 1] = item;

    ConstListSequence<T>* result = new ConstListSequence<T>(new_data, new_size);
    delete[] new_data;
    return result;
}

template <typename T>
ConstListSequence<T>* ConstListSequence<T>::prepend(T item) {
    int new_size = this->get_size() + 1;
    T* new_data = new T[new_size];

    for (int i = new_size - 1; i > 0; i--) {
        new_data[i] = this->get(i - 1);
    }
    new_data[0] = item;

    ConstListSequence<T>* result = new ConstListSequence<T>(new_data, new_size);
    delete[] new_data;
    return result;
}

template <typename T>
ConstListSequence<T>* ConstListSequence<T>::set(int index, T item) {
    int size = this->get_size();

    if (index >= size || index < 0) throw array_out_of_range();
    T* new_data = new T[size];

    for (int i = 0; i < size; i++) {
        new_data[i] = this->get(i);
    }
    new_data[index] = item;

    ConstListSequence<T>* result = new ConstListSequence<T>(new_data, size);
    delete[] new_data;
    return result;
}

template <typename T>
ConstListSequence<T>* ConstListSequence<T>::get_subsequence(int start_index, int end_index) const {
    ListSequence<T>* sub = ListSequence<T>::get_subsequence(start_index, end_index);

    int size = sub->get_size();
    T* temp_array = new T[size];

    for (int i = 0; i < size; i++) {
        temp_array[i] = sub->get(i);
    }

    delete sub;
    ConstListSequence<T>* result = new ConstListSequence<T>(temp_array, size);
    delete[] temp_array;
    return result;
}