#include <iostream>
#include <vector>

constexpr unsigned M = 1000000007 * 2;

void solve(unsigned n)
{
    const unsigned s = n * (n + 1) / 2;
    if (s % 2 != 0) {
        std::cout << 0;
        return;
    }

    const unsigned b = s / 2;

    std::vector<unsigned> counts(1 + b);
    counts[0] = 1;
    for (unsigned i = 1; i <= n; ++i) {
        for (unsigned j = b; j >= i; --j)
            counts[j] = (counts[j] + counts[j-i]) % M;
    }

    std::cout << counts[b] / 2;
}

int main()
{
    unsigned n;
    std::cin >> n;

    solve(n);

    return 0;
}
