#include <iostream>
#include <vector>

constexpr unsigned M = 1000000007;

int main()
{
    unsigned n, x;
    std::cin >> n >> x;

    std::vector<unsigned> cs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> cs[i];

    std::vector<unsigned> counts(1 + x);
    counts[0] = 1;
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = cs[i]; j <= x; ++j)
            counts[j] = (counts[j] + counts[j - cs[i]]) % M;
    }

    std::cout << counts[x];

    return 0;
}
