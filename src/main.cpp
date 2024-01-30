#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    std::vector<int> arr{1, 2, 3, 4, 5};
    arr.push_back(6);
    for (const int x : arr) { std::cout << x << "\n"; }

    std::unordered_map<int, int> hash{{1, 2}, {2, 3}};
    hash[3] = 4;
    for (auto [k, v] : hash) { std::cout << k << ": " << v << "\n"; }
    return 0;
}