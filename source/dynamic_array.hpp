#ifndef STACK_DYNAMIC_ARRAY_HPP
#define STACK_DYNAMIC_ARRAY_HPP


/// \brief Dynamic size array template
/// \tparam T type of objects saved in array
template<class T>
class DynamicArray {
    /// Number of elements currently saved in the array
    int count;

    /// The max number of elements that can be saved in the array currently
    int capacity;

    /// The elements currently saved in the array
    T *elements = nullptr;

    void expand();
    void clear();
    void copy(DynamicArray<T> const& other);

public:
    DynamicArray();
    DynamicArray(int _capacity);
    DynamicArray(DynamicArray<T> const& other);
    DynamicArray& operator=(DynamicArray<T> const& other);
    ~DynamicArray();

    T& operator[](int index);

    void insert(T element, int index);
    void push_back(T element);

    void erase(int index);
    void pop_back();

    int size();
};


#endif //STACK_DYNAMIC_ARRAY_HPP
