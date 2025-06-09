#pragma once

#include "custom_exceptions.h"

template <typename T>
class LinkedList
{
private:
    struct  Node
    {
        T value;
        Node* next;
        Node* prev;
        Node(T new_value, Node* new_next = nullptr, Node* new_prev = nullptr):
        value(new_value), next(new_next), prev(new_prev) {};
    };

    Node* head;
    Node* tail;
    size_t length;
    
public:
    LinkedList();
    LinkedList(T* arr, int count);
    LinkedList (const LinkedList<T>& list);
    ~LinkedList();

    void append(T item);
    void prepend(T item);
    void set(int index, T item);
    T get(int index) const;
    T get_first() const;
    T get_last()const;
    int get_size() const;
    LinkedList<T>* get_sublist(int start_index, int end_index) const;


    void print() {
        Node* node = head;
        int i = 0;
        while (node != nullptr) {
            cout << "{" << i++ << "}: " << node->value << endl;
            node = node->next;
        }
    }
};

template <typename T>
LinkedList<T>::LinkedList(): head(nullptr), tail(nullptr), length(0){}

template <typename T>
LinkedList<T>::LinkedList(T* arr, int count){
    length = 0;
    for (int i = 0; i < count; i++){
        append(arr[i]);
    }
};

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    head = tail = nullptr;
    length = 0;

    Node* current = list.head;
    while (current) {
        append(current->value);
        current = current->next;
    }
}


template <typename T>
LinkedList<T>::~LinkedList(){
    Node* node = head;
    while (node != tail){
        node = node->next;
        delete node->prev;
    }
    delete node;
};

template <typename T>
void LinkedList<T>::append(T item){
    Node* node = new Node(item);

    if (length == 0) {
        head = node;
        tail = node;
        length++;
        return; 
    }

    tail->next = node;
    node->prev = tail;
    tail = node;
    length++;
};

template <typename T>
void LinkedList<T>::prepend(T item){
    if (length == 0){
        append(item);
        return;
    }

    Node* node = new Node(item);
    node->next = head;
    head->prev = node;
    head = node;
    length++;
}

template <typename T>
void LinkedList<T>::set(int index, T item){
    if (index < 0 || index >= length) throw list_out_of_range();

    Node* node = head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }

    node->value = item;
}

template <typename T>
T LinkedList<T>::get(int index) const{
    if (index >= length || index < 0) throw list_out_of_range();

    Node* node = head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }

    return node->value;
}

template <typename T>
T LinkedList<T>::get_first() const {
    return head->value;
}

template <typename T>
T LinkedList<T>::get_last() const {
    return tail->value;
};

template <typename T>
int LinkedList<T>::get_size() const {
    return length;
}

template <typename T>
LinkedList<T>* LinkedList<T>::get_sublist(int start_index, int end_index) const {
    if (!head) throw data_is_null();

    if (start_index < 0 || start_index >= get_size() ||
        end_index < 0 || end_index >= get_size()) {
        throw list_out_of_range();
    }

    if (start_index > end_index){
        int tmp = end_index;
        end_index = start_index;
        start_index = tmp;
    }

    LinkedList<T>* sub_list = new LinkedList<T>;

    int tmp_length = 0;
    Node* node = head;
    while (tmp_length != start_index) {
        node = node->next;
        tmp_length++;
    }

    for (int i = start_index; i < end_index + 1; i++) {
        sub_list->append(node->value);
        node = node->next;
    }

    return sub_list;
};