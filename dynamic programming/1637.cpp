#include <iostream>
#include <vector>

constexpr unsigned oo = ~1u;

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> counts(1 + n, oo);
    counts[0] = 0;
    for (unsigned x = 0; x <= n; ++x) {
        for (unsigned q = x; q != 0; q /= 10) {
            const unsigned d = q % 10;
            counts[x] = std::min(counts[x], counts[x-d] + 1);
        }
    }

    std::cout << counts[n];

    return 0;
}
