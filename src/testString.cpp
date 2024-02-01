#include "String.hpp"
#include <charconv>
#include <string>

int main() {
    // Testing default constructor
    String s1;
    std::cout << "Default constructed: ";
    s1.print(); // Should print an empty string

    // Testing construction from a C-string
    String s2("Hello");
    std::cout << "Constructed from C-string: ";
    s2.print(); // Should print "Hello"

    // Testing copy constructor
    String s3(s2);
    std::cout << "Copy constructed: ";
    s3.print(); // Should print "Hello"

    // Testing move constructor
    String s4(std::move(s3));
    std::cout << "Move constructed: ";
    s4.print(); // Should print "Hello"
    std::cout << "Original after move: ";
    s3.print(); // Should print an empty string

    // Testing construction from a C-string (implicit conversion)
    String s5 = "World";
    s5 = s2;
    std::cout << "Copy assigned: ";
    s5.print(); // Should print "Hello"

    // Testing move assignment operator
    String s6 = "Temp";
    s6 = std::move(s5);
    std::cout << "Move assigned: ";
    s6.print(); // Should print "Hello"
    std::cout << "Original after move assignment: ";
    s5.print(); // Should print an empty string

    // Testing operator+
    String s7 = s2 + String(" World");
    std::cout << "Operator + : ";
    s7.print(); // Should print "Hello World"

    // Testing operator+=
    s2 += String(" Again");
    std::cout << "Operator += : ";
    s2.print(); // Should print "Hello Again"

    // Testing operator==
    std::cout << "Operator == : ";
    std::cout << (s2 == s6 ? "true" : "false")
              << std::endl; // Should print "false"
    String s8("Hello Again");
    std::cout << "Operator == : ";
    std::cout << (s2 == s8 ? "true" : "false")
              << std::endl; // Should print "true"

    String s9;
    for (int i = 0; i < 1000; ++i) { s9 += String(std::to_string(i).c_str()); }
    std::cout << "Operator += long String : ";
    s9.print();
    return 0;
}
