#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned z;
    std::cin >> z;

    unsigned long long d = 0;
    for (unsigned i = 1; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        if (x < z)
            d += z - x;
        else
            z = x;
    }

    std::cout << d;

    return 0;
}
