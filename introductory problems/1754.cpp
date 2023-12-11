#include <iostream>

int main()
{
    unsigned t;
    std::cin >> t;

    for (unsigned i = 0; i < t; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        if (a > b)
            std::swap(a, b);

        if ((a + b) % 3 != 0 || 2 * a < b) {
            std::cout << "NO" << '\n';
        } else {
            std::cout << "YES" << '\n';
        }
    }

    return 0;
}
