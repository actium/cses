#include <iostream>
#include <vector>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    const auto check = [&](unsigned long long b) {
        unsigned long long r = 0, c = 0;
        for (const unsigned x : xs) {
            if (x > r) {
                ++c;
                r = b;
            }
            if (x > r)
                return true;

            r -= x;
        }
        return c > k;
    };

    unsigned long long lb = 0, ub = ~0ull >> 1;
    while (lb + 1 < ub) {
        const auto mid = (lb + ub) / 2;
        (check(mid) ? lb : ub) = mid;
    }

    std::cout << ub;

    return 0;
}
