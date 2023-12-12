#include <iostream>

constexpr unsigned M = 1000000007;

unsigned raise(unsigned base, unsigned power)
{
    unsigned v = 1;
    for (unsigned long long b = base; power != 0; power /= 2) {
        if (power % 2 == 1)
            v = v * b % M;

        b = b * b % M;
    }
    return v;
}

int main()
{
    unsigned n;
    std::cin >> n;

    for (unsigned i = 0; i < n; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        std::cout << raise(a, b) << '\n';
    }

    return 0;
}
