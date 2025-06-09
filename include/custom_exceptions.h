#pragma once
#include <stdexcept>
#include <string>

class array_out_of_range : public std::out_of_range {
public:
    array_out_of_range() : std::out_of_range("Array index out of range") {}
    array_out_of_range(const std::string& msg) : std::out_of_range(msg) {}
};

class list_out_of_range : public std::out_of_range {
public:
    list_out_of_range() : std::out_of_range("List index out of range") {}
    list_out_of_range(const std::string& msg) : std::out_of_range(msg) {}
};

class data_is_null : public std::runtime_error {
public:
    data_is_null() : std::runtime_error("Data is null or empty") {}
    data_is_null(const std::string& msg) : std::runtime_error(msg) {}
};

class invalid_operation : public std::runtime_error {
public:
    invalid_operation() : std::runtime_error("Invalid operation") {}
    invalid_operation(const std::string& msg) : std::runtime_error(msg) {}
};