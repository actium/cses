#include <iostream>
#include <limits>
#include <set>
#include <vector>

int main()
{
    unsigned n, a, b;
    std::cin >> n >> a >> b;

    std::vector<long long> xs(1 + n);
    for (unsigned i = 1; i <= n; ++i)
        std::cin >> xs[i];

    for (unsigned i = 1; i <= n; ++i)
        xs[i] += xs[i-1];

    long long y = std::numeric_limits<long long>::min();

    std::multiset<long long> s;
    for (unsigned i = 1; i <= n; ++i) {
        if (i >= a)
            s.insert(xs[i-a]);

        if (!s.empty())
            y = std::max(y, xs[i] - *s.begin());

        if (i >= b)
            s.erase(s.find(xs[i-b]));
    }

    std::cout << y;

    return 0;
}
