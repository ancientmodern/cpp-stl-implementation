#ifndef HL_STRING
#define HL_STRING

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>

class String {
  public:
    String() = default;

    ~String() { delete[] __data; }

    String(const char *s) {
        if (s) {
            __size = strlen(s);
            __capacity = __size + 1;
            __data = new char[__capacity];
            strcpy(__data, s);
            __data[__size] = '\0';
        }
    }

    String &operator=(const char *s) {
        delete[] __data;
        if (s) {
            __size = strlen(s);
            __capacity = __size + 1;
            __data = new char[__capacity];
            strcpy(__data, s);
        } else {
            __data = nullptr;
            __size = 0;
            __capacity = 0;
        }
        return *this;
    }

    String(const String &s) {
        __size = s.__size;
        __capacity = s.__capacity;
        if (__size != 0) {
            __data = new char[__capacity];
            for (size_t i = 0; i < __size; ++i) { __data[i] = s.__data[i]; }
        }
    }

    String &operator=(const String &s) {
        if (this != &s) {
            delete[] __data;
            __data = nullptr;

            __size = s.__size;
            __capacity = s.__capacity;
            if (__size != 0) {
                __data = new char[__capacity];
                for (size_t i = 0; i < __size; ++i) { __data[i] = s.__data[i]; }
            }
        }
        return *this;
    }

    String(String &&s) noexcept {
        __data = s.__data;
        __size = s.__size;
        __capacity = s.__capacity;
        s.__data = nullptr;
        s.__size = 0;
        s.__capacity = 0;
    }

    String &operator=(String &&s) noexcept {
        if (this != &s) {
            delete[] __data;

            __data = s.__data;
            __size = s.__size;
            __capacity = s.__capacity;
            s.__data = nullptr;
            s.__size = 0;
            s.__capacity = 0;
        }
        return *this;
    }

    String operator+(const String &rhs) {
        if (__data == nullptr) { return rhs; }
        if (rhs.__data == nullptr) { return *this; }

        auto new_size = __size + rhs.__size;
        String result;
        result.__size = new_size;
        result.__capacity = new_size + 1;
        result.__data = new char[result.__capacity];

        strcpy(result.__data, __data);
        strcat(result.__data, rhs.__data);
        result.__data[result.__size] = '\0';
        return result;
    }

    String &operator+=(const String &rhs) {
        if (__size == 0) {
            *this = rhs;
        } else if (rhs.__size != 0) {
            __size += rhs.__size;
            if (__size + 1 <= __capacity) {
                strcat(__data, rhs.__data);
            } else {
                char *old_data = __data;
                __capacity = std::max(MINIMUM_CAPACITY, (__size + 1) * 2);
                __data = new char[__capacity];
                strcpy(__data, old_data);
                strcat(__data, rhs.__data);
                __data[__size] = '\0';
                delete[] old_data;
            }
        }
        return *this;
    }

    bool operator==(const String &rhs) {
        if (__size != rhs.__size) { return false; }
        for (size_t i = 0; i < __size; ++i) {
            if (__data[i] != rhs.__data[i]) { return false; }
        }
        return true;
    }

    char &operator[](size_t i) { return __data[i]; }

    const char &operator[](size_t i) const { return __data[i]; }

    [[nodiscard]] size_t size() const noexcept { return __size; }

    [[nodiscard]] size_t length() const noexcept { return __size; }

    [[nodiscard]] size_t capacity() const noexcept { return __capacity; }

    [[nodiscard]] bool empty() const noexcept { return __size == 0; }

    // for test
    void print() const {
        if (__size != 0) { std::cout << __data; }
        std::cout << std::endl;
    }

  private:
    char *__data{nullptr};
    size_t __size{0};
    size_t __capacity{0};

    static constexpr size_t MINIMUM_CAPACITY = 4;
};

#endif