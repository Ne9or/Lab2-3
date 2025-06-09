#pragma once
#include <type_traits>
#include <sstream>
#include <iomanip>
#include "LinkedList.h"
#include "Sequence.h"
#include "custom_exceptions.h"

template <typename T>
class ListSequence: public Sequence<T>
{
private:
    LinkedList<T>* items;
public:

    ListSequence();
    ListSequence(T* arr, int count);
    ListSequence(const Sequence<T>& seq);
    ListSequence(const LinkedList<T>& list);
    ~ListSequence() override;

    ListSequence<T>* append(T item) override;
    ListSequence<T>* prepend(T item) override;
    ListSequence<T>* set(int index, T item) override;

    T get(int index) const override;
    T get_first() const override;
    T get_last() const override;
    int get_size() const override;
    ListSequence<T>* get_subsequence(int start_index, int end_index) const override;

    ListSequence<T>* map(double multiplier) override;

    std::string to_string() const override;

};

template <typename T>
ListSequence<T>::ListSequence(){
    items = new LinkedList<T>;
};

template <typename T>
ListSequence<T>::ListSequence(T* arr, int count){
    items = new LinkedList<T>(arr, count);
};

template <typename T>
ListSequence<T>::ListSequence(const Sequence<T>& seq){
    items = new LinkedList<T>();

    for (int i = 0; i < seq.get_size(); i++){
        items->append(seq.get(i));
    }
}

template <typename T>
ListSequence<T>::ListSequence(const LinkedList<T>& list){
    items = new LinkedList<T>(list);
}

template <typename T>
ListSequence<T>::~ListSequence(){
    delete items;
};

template <typename T>
ListSequence<T>* ListSequence<T>::append(T item){
    items->append(item);
    return this;
};

template <typename T>
ListSequence<T>* ListSequence<T>::prepend(T item){
    items->prepend(item);
    return this;
};

template <typename T>
ListSequence<T>* ListSequence<T>::set(int index, T value){
    items->set(index, value);
    return this;
};

template <typename T>
T ListSequence<T>::get(int index) const{
    return items->get(index);
};

template <typename T>
T ListSequence<T>::get_first() const {
    if (items->get_size() == 0)  throw list_out_of_range();
    return items->get_first();
};

template <typename T>
T ListSequence<T>::get_last() const {
    if (items->get_size() == 0)  throw list_out_of_range();
    return items->get_last();
};

template <typename T>
int ListSequence<T>::get_size() const{
    return items->get_size();
};

template <typename T>
ListSequence<T>* ListSequence<T>::get_subsequence(int start_index, int end_index) const {
    LinkedList<T>* sublist = items->get_sublist(start_index, end_index);
    ListSequence<T>* sublist_sequence = new ListSequence<T>(*sublist);
    delete sublist;
    return sublist_sequence;
};

template <typename T>
ListSequence<T>* ListSequence<T>::map(double multiplier) {
    if (get_size() == 0) throw data_is_null();
    for (int i = 0; i < items->get_size(); ++i) {
        T value = items->get(i);
        if constexpr (std::is_same_v<T, std::string>) {
            for (char& c : value) {
                c = std::toupper(static_cast<unsigned char>(c));
            }
            items->set(i, value);
        } else {
            items->set(i, value * multiplier);
        }
    }
    return this;
}


template <typename T>
std::string ListSequence<T>::to_string() const {
    std::string result = "{";

    for (int i = 0; i < items->get_size(); ++i) {
        if constexpr (std::is_same_v<T, std::string>) {
            result += items->get(i);
        } else if constexpr (std::is_same_v<T, double>) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << items->get(i);
            result += oss.str();
        } else {
            result += std::to_string(items->get(i));
        }

        if (i != items->get_size() - 1) {
            result += ", ";
        }
    }

    result += "}";
    return result;
}