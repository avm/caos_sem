#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

template <class T>
char* as_bytes(T& i) {
    void* addr = &i;
    return static_cast<char*>(addr);
}

template <typename T>
void Serialize(T pod, std::ostream& out) {
    out.write(as_bytes(pod), sizeof(T));
}

int main() {
    int32_t max;
    std::cin >> max;

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> a(0, 100000);
    for (int32_t i = 0; i < max; ++i) {
        Serialize(a(g), std::cout);
    }

}

