#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> a[i];

    const unsigned k = 1 << n;

    auto b = ~0ull;
    for (unsigned i = 0; i < k; ++i) {
        auto d = 0ll;
        for (unsigned j = 0; j < n; ++j) {
            if ((i & 1 << j) != 0)
                d += a[j];
            else
                d -= a[j];
        }

        b = std::min<unsigned long long>(b, std::abs(d));
    }

    std::cout << b;

    return 0;
}
