#include <iostream>
#include <map>
#include <set>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k;
    std::cin >> n >> k;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::map<unsigned, unsigned> f;
    for (unsigned i = 0; i < k; ++i)
        ++f[xs[i]];

    std::set<std::pair<int, unsigned>> s;

    const auto update = [&](unsigned x, int d) {
        s.erase(std::make_pair(-f[x], x));

        f[x] += d;

        if (f[x] != 0)
            s.emplace(-f[x], x);
    };

    for (const auto& e : f)
        update(e.first, 0);

    std::cout << s.begin()->second;

    for (unsigned i = k; i < n; ++i) {
        update(xs[i], 1);
        update(xs[i-k], -1);

        std::cout << ' ' << s.begin()->second;
    }

    return 0;
}
