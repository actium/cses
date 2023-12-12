#include <algorithm>
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

    std::sort(cs.begin(), cs.end());

    std::vector<unsigned> counts(1 + x);
    counts[0] = 1;
    for (unsigned i = 1; i <= x; ++i) {
        for (unsigned j = 0; j < n && cs[j] <= i; ++j)
            counts[i] = (counts[i] + counts[i - cs[j]]) % M;
    }

    std::cout << counts[x];

    return 0;
}
