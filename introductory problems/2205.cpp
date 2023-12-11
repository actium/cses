#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    const unsigned k = 1 << n;

    for (unsigned i = 0; i < k; ++i) {
        const unsigned x = i ^ (i >> 1);

        for (unsigned j = 0; j < n; ++j)
            std::cout << "01"[x >> j & 1];

        std::cout << '\n';
    }

    return 0;
}
