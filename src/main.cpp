#include "Vector.hpp"
#include "Queue.hpp"
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

int main() {
    // Vector<int> vec1;
    // vec1.push_back(1);
    // vec1.push_back(2);
    // vec1.push_back(3);
    // vec1.push_back(1);
    // vec1.push_back(2);
    // vec1.push_back(3);

    // vec1.print();

    // vec1.pop_back();
    // vec1.pop_back();

    // std::cout << "=======================" << std::endl;
    // vec1.print();

    // Vector<int> vec2{vec1};
    // vec1.print();
    // std::cout << vec1.size() << " " << vec1.capacity() << std::endl;
    // vec2.print();
    // std::cout << vec2.size() << " " << vec2.capacity() << std::endl;

    // vec2 = std::move(vec1);
    // vec2.print();
    // std::cout << vec2.size() << " " << vec2.capacity() << std::endl;

    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.push(6);
    q.push(7);
    q.push(8);
    q.push(9);

    // q.print();
    Queue<int> q1;
    q1.push(11);
    q1 = std::move(q);

    while (!q1.empty()) {
        auto v = q1.front();
        q1.pop();
        std::cout << v << " ";
    }
    std::cout << std::endl;
}