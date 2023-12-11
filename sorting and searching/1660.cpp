#include <iostream>
#include <vector>

int main()
{
    unsigned n, x;
    std::cin >> n >> x;

    std::vector<unsigned> as(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> as[i];

    unsigned s = 0, k = 0;
    for (unsigned i = 0, j = 0; i < n; ++i) {
        for (s += as[i]; s > x; s -= as[j++]);

        if (s == x)
            ++k;
    }

    std::cout << k;

    return 0;
}
