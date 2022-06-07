#include "dynamic_array.hpp"

/// Default constructor
/// \tparam T type of objects saved in array
template<class T>
DynamicArray<T>::DynamicArray() {
    count = 0;
    capacity = 5;
    elements = new T[capacity];
}


/// Constructor with parameters
/// \tparam T type of objects saved in array
/// \param _capacity max number of elements to be saved in array
template<class T>
DynamicArray<T>::DynamicArray(int _capacity) {
    count = 0;
    capacity = (_capacity <= 0) ? 5 : _capacity;
    elements = new T[capacity];
}


/// Copy constructor
/// \tparam T type of objects saved in array
/// \param other object to copy
template<class T>
DynamicArray<T>::DynamicArray(DynamicArray<T> const &other) {
    copy(other);
}


/// Copy assignment operator
/// \tparam T type of objects saved in array
/// \param other object to copy
/// \return the updated object
template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T> const &other) {
    if (this != &other) {
        copy(other);
    }
    return *this;
}


/// Destructor
template<class T>
DynamicArray<T>::~DynamicArray() {
    clear();
}


/// Double the capacity of the array
/// \tparam T type of objects saved in array
template<class T>
void DynamicArray<T>::expand() {
    capacity *= 2;
    T* newData = new T[capacity];
    for (int copyIndex = 0; copyIndex < count; copyIndex++) {
        newData[copyIndex] = elements[copyIndex];
    }
    delete[] elements;
    elements = newData;
}


/// Delete elements in array and nullify count
/// \tparam T type of objects saved in array
template<class T>
void DynamicArray<T>::clear() {
    delete[] elements;
    elements = nullptr;
    count = 0;
}


/// Copy elements of array
/// \tparam T type of objects saved in array
/// \param other DynamicArray to copy from
template<class T>
void DynamicArray<T>::copy(DynamicArray<T> const& other) {
    clear();
    count = other.count;
    capacity = other.capacity;
    elements = new T[count];
    for (int i = 0; i < count; i++) {
        elements[i] = other.elements[i];
    }
}


/// Getter for elements
/// \tparam T type of objects saved in array
/// \param index position to get element from
/// \return element at position index
template<class T>
T& DynamicArray<T>::operator[](int index) {
    return elements[index];
}


/// Insert element at position index
/// \tparam T type of objects saved in array
/// \param element element to add
/// \param index position to add element at
template<class T>
void DynamicArray<T>::insert(T element, int index) {
    if (count == capacity) {
        expand();
    }

    for (int i = count - 1; i > index - 1; i--) {
        elements[i + 1] = elements[i];
    }

    elements[index] = element;
    count++;
}


/// Add element at last position of the array
/// \tparam T type of objects saved in array
/// \param element element to add
template<class T>
void DynamicArray<T>::push_back(T element) {
    if (count == capacity) {
        expand();
    }

    elements[count] = element;
    count++;
}


/// Remove element at index
/// \tparam T type of objects saved in array
/// \param index position to remove the element from
template<class T>
void DynamicArray<T>::erase(int index) {
    for (int i = index; i < count - 1; i++) {
        elements[i] = elements[i + 1];
    }
    count--;
}


/// Remove the last element of the array
/// \tparam T type of objects saved in array
template<class T>
void DynamicArray<T>::pop_back() {
    count--;
}


/// Getter for count
/// \tparam T type of objects saved in array
/// \return number of elements currently saved in the array
template<class T>
int DynamicArray<T>::size() {
    return count;
}

template class DynamicArray<char const*>;
