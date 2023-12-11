#include <iostream>

int main()
{
    unsigned t;
    std::cin >> t;

    for (unsigned i = 0; i < t; ++i) {
        unsigned x, y;
        std::cin >> y >> x;

        if (x <= y) {
            const auto n = 1 + y * (y - 1ull);
            std::cout << (y % 2 == 0 ? n + (y - x) : n - (y - x)) << '\n';
        } else {
            const auto n = 1 + x * (x - 1ull);
            std::cout << (x % 2 == 0 ? n - (x - y) : n + (x - y)) << '\n';
        }
    }

    return 0;
}
