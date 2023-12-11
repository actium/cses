#include <iostream>
#include <vector>

int main()
{
    unsigned n, t;
    std::cin >> n >> t;

    std::vector<unsigned> ks(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ks[i];

    const auto check = [&](unsigned long long x) {
        unsigned long long c = 0;
        for (const unsigned k : ks)
            c += x / k;

        return c < t;
    };

    unsigned long long lb = 0, ub = ~0ull >> 1;
    while (lb + 1 < ub) {
        const auto mid = (lb + ub) / 2;
        (check(mid) ? lb : ub) = mid;
    }

    std::cout << ub;

    return 0;
}
