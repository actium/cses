#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    for (unsigned k = 1; k <= n; ++k)
        std::cout << (k - 1ull) * (k + 4) * (k * k - 3 * k + 4) / 2 << '\n';

    return 0;
}
