#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned fs[1+1000000] = {};
    for (unsigned i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        for (unsigned j = 1; j * j <= x; ++j) {
            if (x % j == 0) {
                ++fs[j];

                if (x / j != j)
                    ++fs[x/j];
            }
        }
    }

    unsigned x = 1000000;
    while (x > 0 && fs[x] < 2)
        --x;

    std::cout << x;

    return 0;
}
