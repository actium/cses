#include <iostream>

constexpr unsigned M = 1000000007;

unsigned raise(unsigned base, unsigned power, unsigned modulus)
{
    unsigned v = 1;
    for (unsigned long long b = base; power != 0; power /= 2) {
        if (power % 2 == 1)
            v = v * b % modulus;

        b = b * b % modulus;
    }
    return v;
}

int main()
{
    unsigned n;
    std::cin >> n;

    for (unsigned i = 0; i < n; ++i) {
        unsigned a, b, c;
        std::cin >> a >> b >> c;

        std::cout << raise(a, raise(b, c, M - 1), M) << '\n';
    }

    return 0;
}
