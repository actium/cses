#include <iostream>
#include <vector>

constexpr unsigned oo = ~0u;

int main()
{
    unsigned n, x;
    std::cin >> n >> x;

    std::vector<unsigned> cs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> cs[i];

    std::vector<unsigned> counts(1+x, oo);
    counts[0] = 0;
    for (unsigned i = 0; i <= x; ++i) {
        for (const unsigned c : cs) {
            if (c <= i && counts[i-c] != oo)
                counts[i] = std::min(counts[i], counts[i-c] + 1);
        }
    }

    std::cout << static_cast<int>(counts[x]);

    return 0;
}
