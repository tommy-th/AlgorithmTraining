#include <iostream>
#include <limits>

int main() {
    uint16_t p = 47111;
    uint16_t q = 64237;

    uint32_t m = (uint32_t) p*q;

    uint32_t a = 1000000007;
    uint32_t b = 1000000007;

    uint64_t mul = (uint64_t)a*b;

    std::cout << std::numeric_limits< std::uint16_t >::max() << std::endl;
    std::cout << std::numeric_limits< std::uint32_t >::max() << std::endl;
    std::cout << std::numeric_limits< std::uint64_t >::max() << std::endl;

    std::cout << p << std::endl;
    std::cout << q << std::endl;
    std::cout << m << std::endl;
}
