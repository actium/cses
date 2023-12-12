#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    for (unsigned i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        unsigned k = 0;
        for (unsigned i = 1; i * i <= x; ++i) {
            if (x % i == 0)
                k += 1 + (x / i != i);
        }

        std::cout << k << '\n';
    }

    return 0;
}
