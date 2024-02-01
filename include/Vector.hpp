#ifndef HL_VECTOR
#define HL_VECTOR

#include <algorithm>
#include <cstddef>
#include <iostream>

template<typename T>
class Vector {
  public:
    Vector() = default;

    ~Vector() { delete[] __data; }

    Vector(const Vector &vec) {
        __size = vec.__size;
        __capacity = vec.__capacity;
        if (__size != 0) {
            __data = new T[__capacity];
            for (size_t i = 0; i < __size; ++i) { __data[i] = vec.__data[i]; }
        }
    }

    Vector &operator=(const Vector &vec) {
        if (this != &vec) {
            delete[] __data;
            __data = nullptr;

            __size = vec.__size;
            __capacity = vec.__capacity;
            if (__size != 0) {
                __data = new T[__capacity];
                for (size_t i = 0; i < __size; ++i) {
                    __data[i] = vec.__data[i];
                }
            }
        }
        return *this;
    }

    Vector(Vector &&vec) noexcept {
        __data = vec.__data;
        __size = vec.__size;
        __capacity = vec.__capacity;
        vec.__data = nullptr;
        vec.__size = 0;
        vec.__capacity = 0;
    }

    Vector &operator=(Vector &&vec) noexcept {
        if (this != &vec) {
            delete[] __data;
            __data = vec.__data;
            __size = vec.__size;
            __capacity = vec.__capacity;
            vec.__data = nullptr;
            vec.__size = 0;
            vec.__capacity = 0;
        }
        return *this;
    }

    [[nodiscard]] size_t size() const noexcept { return __size; }

    [[nodiscard]] size_t capacity() const noexcept { return __capacity; }

    [[nodiscard]] bool empty() const noexcept { return __size == 0; }

    T &operator[](size_t i) noexcept { return __data[i]; }

    const T &operator[](size_t i) const noexcept { return __data[i]; }

    void push_back(const T &v);

    void push_back(T &&v);

    void pop_back() { --__size; }

    // for test
    void print() const noexcept {
        for (size_t i = 0; i < __size; ++i) {
            std::cout << __data[i] << std::endl;
        }
    }

  private:
    T *__data{nullptr};
    size_t __size{0};
    size_t __capacity{0};

    static constexpr size_t MINIMUM_CAPACITY = 4;
};

template<typename T>
void Vector<T>::push_back(const T &v) {
    if (__size >= __capacity) {
        __capacity = std::max(MINIMUM_CAPACITY, __capacity * 2);
        auto new_data = new T[__capacity];
        for (size_t i = 0; i < __size; ++i) { new_data[i] = __data[i]; }
        delete[] __data;
        __data = new_data;
    }
    __data[__size++] = v;
}

template<typename T>
void Vector<T>::push_back(T &&v) {
    if (__size >= __capacity) {
        __capacity = std::max(MINIMUM_CAPACITY, __capacity * 2);
        auto new_data = new T[__capacity];
        for (size_t i = 0; i < __size; ++i) { new_data[i] = __data[i]; }
        delete[] __data;
        __data = new_data;
    }
    __data[__size++] = std::move(v);
}

#endif