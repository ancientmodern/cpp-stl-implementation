#ifndef HL_QUEUE
#define HL_QUEUE

#include <algorithm>
#include <cstddef>
#include <iostream>

template<typename T>
class Queue {
  public:
    Queue() = default;

    ~Queue() { delete[] __data; }

    Queue(const Queue &q) {
        __front = 0;
        __capacity = __back = q.__back - q.__front;
        if (__capacity > 0) {
            __data = new T[__capacity];
            for (size_t i = 0; i < __back; ++i) {
                __data[i] = q.__data[i + q.__front];
            }
        }
    }

    Queue &operator=(const Queue &q) {
        if (this != &q) {
            delete[] __data;
            __data = nullptr;

            __front = 0;
            __capacity = __back = q.__back - q.__front;
            if (__capacity > 0) {
                __data = new T[__capacity];
                for (size_t i = 0; i < __back; ++i) {
                    __data[i] = q.__data[i + q.__front];
                }
            }
        }
        return *this;
    }

    Queue(Queue &&q) noexcept {
        __data = q.__data;
        __front = q.__front;
        __back = q.__back;
        __capacity = q.__capacity;
        q.__data = nullptr;
        q.__front = 0;
        q.__back = 0;
        q.__capacity = 0;
    }

    Queue &operator=(Queue &&q) noexcept {
        if (this != &q) {
            delete[] __data;

            __data = q.__data;
            __front = q.__front;
            __back = q.__back;
            __capacity = q.__capacity;
            q.__data = nullptr;
            q.__front = 0;
            q.__back = 0;
            q.__capacity = 0;
        }
        return *this;
    }

    [[nodiscard]] size_t size() const noexcept { return __back - __front; }

    [[nodiscard]] size_t capacity() const noexcept { return __capacity; }

    [[nodiscard]] bool empty() const noexcept { return __back == __front; }

    T &operator[](size_t i) noexcept { return __data[i]; }

    const T &operator[](size_t i) const noexcept { return __data[i]; }

    T &front() { return __data[__front]; }

    const T &front() const { return __data[__front]; }

    T &back() { return __data[__back - 1]; }

    const T &back() const { return __data[__back - 1]; }

    void push(const T &v);

    void push(T &&v);

    void pop() { ++__front; }

    // for test
    void print() const noexcept {
        for (size_t i = __front; i < __back; ++i) {
            std::cout << __data[i] << std::endl;
        }
    }

  private:
    T *__data{nullptr};
    size_t __front{0};
    size_t __back{0};
    size_t __capacity{0};

    static constexpr size_t MINIMUM_CAPACITY = 4;
};

template<typename T>
void Queue<T>::push(const T &v) {
    if (__back >= __capacity) {
        __capacity = std::max(MINIMUM_CAPACITY, 2 * (__back - __front));
        auto old_data = __data;
        __data = new T[__capacity];
        for (size_t i = __front; i < __back; ++i) {
            __data[i - __front] = old_data[i];
        }
        delete[] old_data;
        __back -= __front;
        __front = 0;
    }
    __data[__back++] = v;
}

template<typename T>
void Queue<T>::push(T &&v) {
    if (__back >= __capacity) {
        __capacity = std::max(MINIMUM_CAPACITY, 2 * (__back - __front));
        auto old_data = __data;
        __data = new T[__capacity];
        for (size_t i = __front; i < __back; ++i) {
            __data[i - __front] = old_data[i];
        }
        delete[] old_data;
        __back -= __front;
        __front = 0;
    }
    __data[__back++] = std::move(v);
}

#endif